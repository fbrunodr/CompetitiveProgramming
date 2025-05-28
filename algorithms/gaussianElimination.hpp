#ifndef FBRUNODR_GAUSSIAN_ELIMINATION
#define FBRUNODR_GAUSSIAN_ELIMINATION

#include "numberTheory.hpp"

template<auto MOD>
void gaussianEliminationOnField(
    vec<vi> a,
    vi& ans,
    vec<vi>& basis
){
    const int n = (int)a.size();
    const int m = (int)a[0].size() - 1;

    vi where(m,-1);          // where[col] = row of pivot or -1
    int row = 0;

    for(int col=0; col<m && row<n; ++col){
        /* find pivot */
        int sel = -1;
        for(int i=row;i<n;++i) if(a[i][col]) { sel=i; break; }
        if(sel==-1) continue;

        swap(a[sel],a[row]);
        where[col] = row;

        /* scale pivot row to 1 */
        int inv = modInverse<MOD>(a[row][col]);
        for(int j=col;j<=m;++j)
            a[row][j] = a[row][j]*inv % MOD;

        /* eliminate from other rows */
        for(int i=0;i<n;++i) if(i!=row && a[i][col]){
            int factor = a[i][col];
            for(int j=col;j<=m;++j)
                a[i][j] = mod<MOD>(a[i][j] - factor*a[row][j]);
        }
        ++row;
    }

    /* check consistency */
    for(int i=row;i<n;++i){
        if(a[i][m]){            // 0 … 0 | non-zero
            ans.clear(); basis.clear();
            return;             // no solution
        }
    }

    /* one particular solution (free vars = 0) */
    ans.assign(m,0);
    for(int j=0;j<m;++j)
        if(where[j]!=-1)
            ans[j] = a[where[j]][m];

    /* basis for the kernel */
    basis.clear();
    for(int j=0;j<m;++j) if(where[j]==-1){
        vi vec(m,0);
        vec[j] = 1;
        for(int k=0;k<m;++k)
            if(where[k]!=-1){
                int r = where[k];
                vec[k] = (MOD - a[r][j]) % MOD; // move to other side
            }
        basis.push_back(std::move(vec));
    }
}

template<auto EPS = 1e-9>
void gaussianEliminationOnR (
    vec<vec<double>> a,
    vec<double>& ans,
    vec<vec<double>>& basis
){
    using std::fabs;
    const int n = (int)a.size();
    const int m = (int)a[0].size() - 1;

    vi where(m, -1);   // pivot row for each column
    int row = 0;

    for (int col = 0; col < m && row < n; ++col) {
        /* ------ choose pivot (partial pivoting) ------ */
        int sel = row;
        for (int i = row; i < n; ++i)
            if (fabs(a[i][col]) > fabs(a[sel][col]))
                sel = i;
        if(fabs(a[sel][col]) < EPS) continue;   // no pivot in this col

        swap(a[sel], a[row]);
        where[col] = row;

        /* ------ scale pivot row to 1 ------ */
        const double inv = 1.0 / a[row][col];
        for (int j = col; j <= m; ++j) a[row][j] *= inv;

        /* ------ eliminate current column from all other rows ------ */
        for (int i = 0; i < n; ++i) if (i != row && fabs(a[i][col]) > EPS) {
            const double factor = a[i][col];
            for (int j = col; j <= m; ++j)
                a[i][j] -= factor * a[row][j];
        }
        ++row;
    }

    /* ------ check consistency: 0 … 0 | b  with  b ≠ 0 ------ */
    for (int i = row; i < n; ++i)
        if (fabs(a[i][m]) > EPS) {        // inconsistent
            ans.clear();
            basis.clear();
            return;
        }

    /* ------ one particular solution (free vars = 0) ------ */
    ans.assign(m, 0.0);
    for (int j = 0; j < m; ++j)
        if (where[j] != -1)
            ans[j] = a[where[j]][m];

    /* ------ kernel basis vectors (one per free variable) ------ */
    basis.clear();
    for (int j = 0; j < m; ++j) if (where[j] == -1) {
        vec<double> v(m, 0.0);
        v[j] = 1.0;                      // free variable = 1
        for (int k = 0; k < m; ++k)
            if (where[k] != -1)
                v[k] = -a[where[k]][j];  // move terms to LHS
        basis.push_back(std::move(v));
    }
}

#endif
