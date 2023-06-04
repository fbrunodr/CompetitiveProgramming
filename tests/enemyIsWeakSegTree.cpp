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
 
    struct conquerer { int operator()(int a, int b) {return a;} };
    struct updateNode { void operator()(int& a, int up, int L, int R) { a += up; } };
    struct updateUpdate { void operator()(int& up1, int up2) { up1 += up2; } };

    LazySegTree<int, int> segTree(vi(n, 0), conquerer(), updateNode(), updateUpdate());
    vi l(n);
    for(int i = 0; i < n; i++){
        l[i] = segTree.RQ(a[i], a[i]);
        segTree.rangeUpdate(0, a[i], 1);
    }
 
    segTree = LazySegTree<int, int>(vi(n, 0), conquerer(), updateNode(), updateUpdate());
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
