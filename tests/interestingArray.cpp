// see https://codeforces.com/problemset/problem/482/B

#include "../dataStructures/LazySegTree.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    int n, m; cin >> n >> m;

    // note that (a&b)|c = (a|c) & (b|c), that is, bitwise 'or' is
    // distributive over bitwise 'and', so we can use lazy segtree
    auto conquerer = [](int a, int b){
        return a & b;
    };
    auto updator = [](int a, int update){
        return a | update;
    };
    LazySegTree<int> lazySegTree(vector<int>(n + 1, 0), conquerer, updator, INT_MAX, INT_MAX);

    using iii = tuple<int, int, int>;
    using viii = vector<iii>;

    viii queries(m);
    for(auto& query : queries){
        int l, r, x;
        cin >> l >> r >> x;
        lazySegTree.rangeUpdate(l, r, x);
        query = {l, r, x};
    }

    for(auto& [l, r, x] : queries)
        if(lazySegTree.RQ(l, r) != x){
            cout << "NO" << endl;
            return 0;
        }

    cout << "YES" << endl;
    for(int i = 1; i <= n; i++)
        cout << lazySegTree.RQ(i, i) << ' ';
    cout << endl;

    return 0;
}
