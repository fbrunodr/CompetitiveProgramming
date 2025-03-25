// see https://codeforces.com/problemset/problem/482/B
// latest submission: https://codeforces.com/contest/482/submission/312356792

#include "../dataStructures/SegTree.hpp"

int32_t main(){
    fastIO();

    int n, m; cin >> n >> m;

    // note that (a&b)|c = (a|c) & (b|c), that is, bitwise 'or' is
    // distributive over bitwise 'and', so we can use lazy segtree
    auto conquerer = [](int a, int b){
        return a & b;
    };
    auto nodeUpdator = [](int& a, int update, int L, int R){
        a |= update;
    };
    auto updateUpdator = [](int& update1, int update2){
        update1 |= update2;
    };
    LazySegTree<int, int> lazySegTree(vector<int>(n + 1, 0), conquerer, nodeUpdator, updateUpdator);

    viii queries(m);
    for(auto& query : queries){
        int l, r, x;
        cin >> l >> r >> x;
        lazySegTree.rangeUpdate(l, r, x);
        query = {l, r, x};
    }

    for(auto& [l, r, x] : queries)
        if(lazySegTree.RQ(l, r) != x){
            cout << "NO" << '\n';
            return 0;
        }

    cout << "YES" << '\n';
    for(int i = 1; i <= n; i++)
        cout << lazySegTree.RQ(i, i) << ' ';
    cout << '\n';

    return 0;
}
