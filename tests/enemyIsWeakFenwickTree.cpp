// see https://codeforces.com/problemset/problem/61/E
// latest submission: https://codeforces.com/contest/61/submission/312269879

#include "../dataStructures/FenwickTree.cpp"

int32_t main(){
    fastIO();
    int n; cin >> n;

    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;

    auto aux = a;
    sort(aux.begin(), aux.end());
    hash_map<int, int> pos;
    for(int i = 0; i < n; i++)
        pos[aux[i]] = i+1;

    for(auto& a_i : a)
        a_i = pos[a_i];

    FenwickTree<int> ft(vi(n+2, 0), std::plus<int>(), std::minus<int>());
    vi l(n);
    for(int i = 0; i < n; i++){
        l[i] = ft.cumulative(a[i]);
        ft.increment(1, 1);
        ft.increment(a[i]+1, -1);
    }

    ft = FenwickTree<int>(vi(n+2, 0), std::plus<int>(), std::minus<int>());
    vi r(n);
    for(int i = n-1; i >= 0; i--){
        r[i] = (n-1) - i - ft.cumulative(a[i]);
        ft.increment(1, 1);
        ft.increment(a[i]+1, -1);
    }

    int ans = 0;
    for(int i = 0; i < n; i++)
        ans += l[i] * r[i];

    cout << ans << endl;

    return 0;
}
