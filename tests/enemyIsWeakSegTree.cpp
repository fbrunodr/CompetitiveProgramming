// see https://codeforces.com/problemset/problem/61/E
// latest submission: https://codeforces.com/contest/61/submission/314308069

#include "../dataStructures/SegTree.hpp"

int32_t main(){
    fastIO();
    int n; cin >> n;

    vec<int32_t> a(n);
    for(auto& a_i : a)
        cin >> a_i;

    auto aux = a;
    sort(aux.begin(), aux.end());
    for(auto& a_i : a)
        a_i = lower_bound(aux.begin(), aux.end(), a_i) - aux.begin();

    struct conquerer { int32_t operator()(int32_t a, int32_t b) {return a;} };
    struct updateNode { void operator()(int32_t& a, int32_t up) { a += up; } };
    struct updateUpdate { void operator()(int32_t& up1, int32_t up2) { up1 += up2; } };

    LazySegTree<int32_t, int32_t> segTree(vec<int32_t>(n, 0), conquerer(), updateNode(), updateUpdate());
    vi l(n);
    for(int i = 0; i < n; i++){
        l[i] = segTree.RQ(a[i], a[i]);
        segTree.rangeUpdate(0, a[i], 1);
    }

    segTree = LazySegTree<int32_t, int32_t>(vec<int32_t>(n, 0), conquerer(), updateNode(), updateUpdate());
    vi r(n);
    for(int i = n-1; i >= 0; i--){
        r[i] = (n-1) - i - segTree.RQ(a[i], a[i]);
        segTree.rangeUpdate(0, a[i], 1);
    }

    int ans = 0;
    for(int i = 0; i < n; i++)
        ans += l[i] * r[i];

    cout << ans << endl;

    return 0;
}
