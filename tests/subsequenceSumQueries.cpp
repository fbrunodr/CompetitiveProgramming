// see https://codeforces.com/gym/101741/problem/J
// latest submission: https://codeforces.com/gym/101741/submission/312404808
// The geniuses from codeforces reduced memory requirements and bumped time by 5x
// Not it is a completly distinct problem :smh:

#include "../algorithms/DivideAndConquerDP.hpp"
#define MOD (int)(1e9 + 7)

int32_t main(){
    fastIO();

    int n, m;
    cin >> n >> m;

    using vi = vector<int>;
    vi a(n);
    for(auto& a_i : a){
        cin >> a_i;
        a_i %= m;
    }


    auto element = [&](int i){
        vi ans(m, 0);
        ans[0]++;
        ans[a[i]]++;
        return ans;
    };

    auto mergeElement = [&](vi& range, int i){
        vi dontTake = range;
        vi take = dontTake;
        std::rotate(take.begin(), take.begin() + (m - a[i]), take.end());
        for(int i = 0; i < m; i++)
            take[i] = (dontTake[i] + take[i]) % MOD;
        return take;
    };

    vi empty;

    DivideAndConquerDP<vi> solver(n, element, mergeElement);

    int queries; cin >> queries;
    while(queries--){
        int i, j; cin >> i >> j;
        i--; j--;
        auto [left, right] = solver.RQ(i, j);
        if(right == nullopt){
            cout << (*left)[0] << '\n';
        }
        else{
            int ans = 0;
            for(int i = 0; i < m; i++){
                ans += ((long long)(*left)[i] * (*right)[(m-i)%m]) % MOD;
                ans %= MOD;
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
