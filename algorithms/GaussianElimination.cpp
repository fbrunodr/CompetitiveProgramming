#include <bits/stdc++.h>
using namespace std;

struct AugmentedMatrix {
    vector<vector<double>> mat;
    AugmentedMatrix(int N){
        mat = vector<vector<double>>(N, vector<double>(N+1, 0.0));
    }
};

struct ColumnVector {
    vector<double> vec;
    ColumnVector(int N){
        vec =  vector<double>(N);
    }
};

ColumnVector GaussianElimination(AugmentedMatrix Aug) {
    int N = Aug.mat.size();

    // input: N, Augmented Matrix Aug, output: Column vector X, the answer
    for(int i = 0; i < N - 1; ++i){ // forward elimination
        int l = i;
        for(int j = i + 1; j < N; ++j) // row with max col value
            if(fabs(Aug.mat[j][i]) > fabs(Aug.mat[l][i]))
                l = j; // remember this row l
        // swap this pivot row, reason: minimize floating point error
        for(int k = i; k <= N; ++k)
            swap(Aug.mat[i][k], Aug.mat[l][k]);
        for(int j = i + 1; j < N; ++j) // actual fwd elimination
            for(int k = N; k >= i; --k)
                Aug.mat[j][k] -= Aug.mat[i][k] * Aug.mat[j][i] / Aug.mat[i][i];
    }

    ColumnVector Ans(N); // back substitution phase
    for(int j = N - 1; j >= 0; --j){ // start from back
        double t = 0.0;
        for(int k = j + 1; k < N; ++k)
            t += Aug.mat[j][k] * Ans.vec[k];
        Ans.vec[j] = (Aug.mat[j][N] - t) / Aug.mat[j][j]; // the answer is here
    }

    return Ans;
}
