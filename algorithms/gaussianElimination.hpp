#ifndef FBRUNODR_GAUSSIAN_ELIMINATION
#define FBRUNODR_GAUSSIAN_ELIMINATION

#include "../header.hpp"

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
