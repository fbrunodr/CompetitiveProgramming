#ifndef FBRUNODR_GAUSSIAN_ELIMINATION
#define FBRUNODR_GAUSSIAN_ELIMINATION

#include "numberTheory.hpp"

const int    ONE  = 1;   // unique solution
const int    INF  = 1e9; // infinitely many solutions
const int    NONE = 0;   // no solution

/*
    returns number of solutions (either 0, 1 or INF)
    a -> augmented matrix, of size n_equations x (n_vars + 1)
    ans -> one of the answers, if there is one

    fixed[i] = 1  ->  x_i has the same value in *every* solution
    fixed[i] = 0  ->  x_i is a free parameter (or depends on one)
*/
template<auto MOD>
int gaussianEliminationOnRing(
    vec<vi> a,
    vi& ans,
    vi& fixed
){
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;
    vi where(m, -1);

    /* ------- Gaussian elimination triangularization ------- */
    for(int var = 0, row = 0; var < m && row < n; ++var){
        for(int i = row; i < n; ++i)
            if(a[i][var]){
                if(i != row)
                    swap(a[i], a[row]);
                break;
            }
        if(a[row][var] == 0)
            continue;

        where[var] = row;

        int currModInverse = modInverse<MOD>(a[row][var]);
        for(int j = var; j <= m; ++j)
            a[row][j] = (a[row][j] * currModInverse) % MOD;

        for(int i = row + 1; i < n; ++i){
            for(int j = var + 1; j <= m; ++j)
                a[i][j] = mod<MOD>(a[i][j] - a[row][j] * a[i][var]);
            a[i][var] = 0;
        }
        ++row;
    }

    /* ------- Diagonalization of non-zero values ------- */
    for(int var = m-1; var >= 0; var--){
        if(where[var] == -1) continue;
        int row = where[var];
        for(int i = 0; i < row; i++){
            a[i][m] = mod<MOD>(a[i][m] - a[row][m] * a[i][var]);
            a[i][var] = 0;
        }
    }

    /* ---------- consistency check ---------- */
    ans.assign(m, 0);
    for(int i = 0; i < m; ++i)
        if(where[i] != -1)
            ans[i] = (a[where[i]][m] * modInverse<MOD>(a[where[i]][i])) % MOD;

    for(int i = 0; i < n; ++i){
        int sum = 0;
        for(int j = 0; j < m; ++j)
            sum += ans[j] * a[i][j];
        if((sum - a[i][m]) % MOD != 0) return NONE;     // no solution
    }

    /* ---------- classify variables ---------- */
    fixed.assign(m, 0);                                 // default: not fixed

    bool unique = true;
    vi freeCols;
    for(int i = 0; i < m; ++i)
        if(where[i] == -1) { freeCols.push_back(i); unique = false; }

    if(unique){                                         // the usual “unique solution” case
        fill(fixed.begin(), fixed.end(), 1);
        return ONE;
    }

    /* we have ≥1 free columns — check the pivot columns */
    for(int i = 0; i < m; ++i)
        if(where[i] != -1){
            int r = where[i];
            bool depends = false;
            for(int j : freeCols)
                if(a[r][j] != 0)
                    { depends = true; break; }
            if(!depends) fixed[i] = 1;                  // truly fixed
        }

    return INF;                                         // many solutions, info in 'fixed'
}

/*
    returns number of solutions (either 0, 1 or INF)
    a -> augmented matrix, of size n_equations x (n_vars + 1)
    ans -> one of the answers, if there is one

    fixed[i] = 1  ->  x_i has the same value in *every* solution
    fixed[i] = 0  ->  x_i is a free parameter (or depends on one)
*/
int gaussianEliminationOnR (
    vector<vector<double>> a,
    vector<double>& ans,
    vector<int>& fixed,
    double EPS = 1e-9
){
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vector<int> where(m, -1);

    /* ---------- standard Gaussian elimination ---------- */
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (fabs(a[i][col]) > fabs(a[sel][col])) sel = i;

        if (fabs(a[sel][col]) <= EPS) continue;
        for (int i = col; i <= m; ++i) swap(a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = 0; i < n; ++i) if (i != row) {
            double c = a[i][col] / a[row][col];
            for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
        }
        row++;
    }

    /* ---------- consistency check ---------- */
    ans.assign(m, 0.0);
    for (int i = 0; i < m; ++i)
        if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];

    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
        if (fabs(sum - a[i][m]) >= EPS) return NONE;        // no solution
    }

    /* ---------- classify variables ---------- */
    fixed.assign(m, 0);                      // default: not fixed

    bool unique = true;
    vector<int> freeCols;
    for (int i = 0; i < m; ++i)
        if (where[i] == -1) { freeCols.push_back(i); unique = false; }

    if (unique) {                            // the usual “unique solution” case
        fill(fixed.begin(), fixed.end(), 1);
        return ONE;
    }

    /* we have ≥1 free columns — check the pivot columns */
    for (int i = 0; i < m; ++i) if (where[i] != -1) {
        int r = where[i];
        bool depends = false;
        for (int j : freeCols)
            if (fabs(a[r][j]) >= EPS) { depends = true; break; }
        if (!depends) fixed[i] = 1;          // truly fixed
    }

    return INF;                              // many solutions, info in 'fixed'
}

/*
    You have a system of equations that you KNOW has
    an unique solution? Use this function.
*/
void uniqueSolutionGaussianEliminationOnR(
    vector<vector<double>> a,
    vector<double>& ans
){
    vi fixed; // dummy
    gaussianEliminationOnR(a, ans, fixed, 0.0);
}

#endif
