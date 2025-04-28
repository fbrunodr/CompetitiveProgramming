// see https://open.kattis.com/problems/fortunefromfolly
// latest submission: https://open.kattis.com/submissions/17280375

#include "../algorithms/GaussianElimination.hpp"

int countOnBits(int mask){
    int ans = 0;
    while(mask){
        mask -= LSOne(mask);
        ans++;
    }
    return ans;
}

int32_t main(){
    int n, k; cin >> n >> k;
    double p; cin >> p;

    int N = (1<<n);

    vec<vec<double>> mat(N, vec<double>(N+1, 0.0));

    for(int mask = 0; mask < N; mask++){
        if(countOnBits(mask) >= k){
            mat[mask][mask] = 1;
        }
        else{
            int didntGetRareMask = (mask << 1) & (N-1);
            int gotRareMask = didntGetRareMask | 1;
            mat[mask][mask] += 1;
            mat[mask][gotRareMask] -= p;
            mat[mask][didntGetRareMask] -= (1-p);
            mat[mask][N] = 1;
        }
    }

    vec<double> ans;
    UniqueSolutionGaussianEliminationOnR(mat, ans);
    cout << std::fixed << std::setprecision(10) << ans[0] << endl;

    return 0;
}
