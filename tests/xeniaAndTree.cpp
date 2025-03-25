#include "../algorithms/CentroidDecomposition.cpp"
#include "../algorithms/lca.cpp"


int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    vec<vi> al;
    cin >> n >> m;
    al = vec<vi>(n+1);
    for(int i = 0; i < n - 1; i++){
        int u, v; cin >> u >> v;
        al[u].push_back(v);
        al[v].push_back(u);
    }

    CentroidDecomposition centroidTree(al, 1);
    SpTLCA lca(al, 1);

    auto get_dist = [&lca](int u, int v){
        return lca.depth(u) + lca.depth(v) - 2*lca.depth(lca.lca(u,v));
    };

    vi dist(n+1, 1e9);
    dist[1] = 0;
    for(int v : centroidTree.get_ancestors(1))
        dist[v] = get_dist(1, v);

    for(int i = 0; i < m; i++){
        int type, u; cin >> type >> u;
        if(type == 1){
            dist[u] = 0;
            for(int v : centroidTree.get_ancestors(u))
                dist[v] = min(dist[v], get_dist(u,v));
        }
        else if(type == 2){
            int ans = dist[u];
            for(int v : centroidTree.get_ancestors(u))
                ans = min(ans, dist[v] + get_dist(u,v));
            cout << ans << endl;
        }
    }

    return 0;
}