// see https://codeforces.com/problemset/problem/547/B
// latest submission: https://codeforces.com/contest/547/submission/312366718

#include "../algorithms/firstElementToLeft.hpp"

int32_t main(){
    fastIO();
    int n; cin >> n;

    using vi = vector<int>;
    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;

    vi l = firstElementToLeft<int>(a, std::less<int>());
    vi r = firstElementToRight<int>(a, std::less<int>());

    vi ans(n+1, 0);

    for(int i = 0; i < n; i++){
        int size = r[i] - l[i] - 1;
        ans[size] = max(ans[size], a[i]);
    }

    for(int size = n-1; size >= 0; size--)
        ans[size] = max(ans[size], ans[size+1]);

    for(int size = 1; size <= n; size++)
        cout << ans[size] << ' ';
    cout << endl;

    return 0;
}
