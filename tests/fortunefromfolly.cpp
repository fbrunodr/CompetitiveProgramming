// see https://open.kattis.com/problems/fortunefromfolly
// latest submission: https://open.kattis.com/submissions/16966390

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

    AugmentedMatrix M(N);

    for(int mask = 0; mask < N; mask++){
        if(countOnBits(mask) >= k){
            M.mat[mask][mask] = 1;
        }
        else{
            int didntGetRareMask = (mask << 1) & (N-1);
            int gotRareMask = didntGetRareMask | 1;
            M.mat[mask][mask] += 1;
            M.mat[mask][gotRareMask] -= p;
            M.mat[mask][didntGetRareMask] -= (1-p);
            M.mat[mask][N] = 1;
        }
    }

    auto ans = GaussianElimination(M);
    cout << std::fixed << std::setprecision(10) << ans.Vec[0] << endl;

    return 0;
}
