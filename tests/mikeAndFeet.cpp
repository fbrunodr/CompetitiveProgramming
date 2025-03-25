// see https://codeforces.com/problemset/problem/547/B

#include "../algorithms/firstElementToLeft.cpp"

int32_t main(){
    ios_base::sync_with_stdio(false);
    int n; cin >> n;

    using vi = vector<int>;
    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;

    vi l = firstElementToLeft<int>(a, less<int>());
    vi r = firstElementToRight<int>(a, less<int>());

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
