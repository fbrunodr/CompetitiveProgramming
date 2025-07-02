// problem source:
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4549

#include "../dataStructures/HeavyLightDecomposition.hpp"

int32_t main(){
    fastIO();

    int testCases; cin >> testCases;
    for(int testCase = 1; testCase <= testCases; testCase++){
        int n; cin >> n;
        vec<vi> al(n);
        for(int i = 0; i < n-1; i++){
            int u, v; cin >> u >> v;
            al[u].push_back(v);
            al[v].push_back(u);
        }

        auto merge = [](int a, int b) { return a + b; };
        auto nodeUpdator = [](int& a, int up, int l, int r) { a += up * (r - l + 1); };
        auto lazyUpdator = [](int& a, int b) { a += b; };

        int root = (rng_32() % n);
        LazyHLD<int, int, f<void(int&,int,int,int)>> hld(al, vi(n, 0), root, merge, nodeUpdator, lazyUpdator);

        int q; cin >> q;
        while(q--){
            int a, b, c; cin >> a >> b >> c;
            hld.updatePath(a, b, c);
        }

        cout << "Case #" << testCase << ":\n";
        for(int i = 0; i < n; i++)
            cout << hld.queryPath(i, i) << "\n";
    }

    return 0;
}

#include "../footer.hpp"