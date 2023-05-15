// see https://codeforces.com/problemset/problem/61/E
// runs in a little more than 1000 ms

#include "../dataStructures/FenwickTree.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    
    using vi = vector<int>;
    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;
    
    auto aux = a;
    sort(aux.begin(), aux.end());
    unordered_map<int, int> pos;
    for(int i = 0; i < n; i++)
        pos[aux[i]] = i+1;
 
    for(auto& a_i : a)
        a_i = pos[a_i];
 
    FenwickTree<int> ft(vi(n+2, 0), plus<int>(), minus<int>());
    vi l(n);
    for(int i = 0; i < n; i++){
        l[i] = ft.cumulative(a[i]);
        ft.increment(1, 1);
        ft.increment(a[i]+1, -1);
    }
 
    ft = FenwickTree<int>(vi(n+2, 0), plus<int>(), minus<int>());
    vi r(n);
    for(int i = n-1; i >= 0; i--){
        r[i] = (n-1) - i - ft.cumulative(a[i]);
        ft.increment(1, 1);
        ft.increment(a[i]+1, -1);
    }
 
    using i64 = long long;
    i64 ans = 0;
    for(int i = 0; i < n; i++)
        ans += (i64)l[i] * r[i];
 
    cout << ans << endl;
 
    return 0;
}
