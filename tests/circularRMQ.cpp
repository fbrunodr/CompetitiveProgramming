// see https://codeforces.com/contest/52/problem/C

#include "../dataStructures/LazySegTree.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    using i64 = long long;
    using vi64 = vector<i64>;

    int n; cin >> n;
    vi64 a(n);
    for(auto& a_i : a)
        cin >> a_i;
 
    auto mergeNode = [](i64 a, i64 b){ return min(a, b); };
    auto updateNode = [](i64& node, i64 update, int L, int R){ return node += update; };
    auto updateUpdate = [](i64& update1, i64 update2){ return update1 += update2; };
 
    LazySegTree<i64, i64> segTree(a, mergeNode, updateNode, updateUpdate, LONG_LONG_MAX, LONG_MAX);

    int m; cin >> m;
    string garbage; getline(cin, garbage);
    while(m--){
        string line;
        getline(cin, line);
        stringstream lineStream(line);
        i64 a, b, inc;
        lineStream >> a >> b;
        if(lineStream >> inc){
            if(a <= b)
                segTree.rangeUpdate(a, b, inc);
            else{
                segTree.rangeUpdate(a, n-1, inc);
                segTree.rangeUpdate(0, b, inc);
            }
        }
        else{
            if(a <= b)
                cout << segTree.RQ(a, b) << '\n';
            else
                cout << min(
                    segTree.RQ(a, n-1), segTree.RQ(0, b)
                ) << '\n';
        }
    }
 
    return 0;
}