// see https://codeforces.com/problemset/problem/61/E
// runs in a little less than 3000 ms

#include "../dataStructures/LazySegTree.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    
    using vi = vector<int>;
    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;
    
    auto aux = a;
    sort(aux.begin(), aux.end());
    for(auto& a_i : a)
        a_i = lower_bound(aux.begin(), aux.end(), a_i) - aux.begin();
 
    auto mergeNode = [](int a, int b){ return a; };
    auto updateNode = [](int& a, int up, int L, int R) { a += up; };
    auto updateUpdate = [](int& a, int up) { a += up; };

    LazySegTree<int, int> segTree(vi(n, 0), mergeNode, updateNode, updateUpdate, INT_MAX, INT_MAX);
    vi l(n);
    for(int i = 0; i < n; i++){
        l[i] = segTree.RQ(a[i], a[i]);
        segTree.rangeUpdate(0, a[i], 1);
    }
 
    segTree = LazySegTree<int, int>(vi(n, 0), mergeNode, updateNode, updateUpdate, INT_MAX, INT_MAX);
    vi r(n);
    for(int i = n-1; i >= 0; i--){
        r[i] = (n-1) - i - segTree.RQ(a[i], a[i]);
        segTree.rangeUpdate(0, a[i], 1);
    }
 
    using i64 = long long;
    i64 ans = 0;
    for(int i = 0; i < n; i++)
        ans += (i64)l[i] * r[i];
 
    cout << ans << endl;
 
    return 0;
}
