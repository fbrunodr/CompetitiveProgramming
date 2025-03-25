// see https://codeforces.com/contest/52/problem/C
// latest submission: https://codeforces.com/contest/52/submission/312269164

#include "../dataStructures/SegTree.hpp"

int32_t main(){
    fastIO();

    int n; cin >> n;
    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;
 
    auto conquerer = [](int a, int b){ return min(a, b); };
    auto updateNode = [](int& node, int update, int L, int R){ return node += update; };
    auto updateUpdate = [](int& update1, int update2){ return update1 += update2; };
 
    LazySegTree<int, int> segTree(a, conquerer, updateNode, updateUpdate);

    int m; cin >> m;
    string garbage; getline(cin, garbage);
    while(m--){
        string line;
        getline(cin, line);
        std::stringstream lineStream(line);
        int a, b, inc;
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