#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../header.hpp"
#include "../algorithms/graphCompressor.hpp"

int solve(){
    fastIO();
    int n, m; cin >> n >> m;
    vec<vi> al(n);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        al[u].push_back(v);
    }

    auto [compressedNode, compressedGraph] = graphCompressor(al);
    int numSCC = compressedGraph.size();
    vec<vi> connectedComponents(numSCC);
    for(int i = 0; i < n; i++)
        connectedComponents[compressedNode[i]].push_back(i);

    vi componentsTopo;
    vec<bool> visited(numSCC, false);
    f<void(int)> dfs = [&](int u){
        if(visited[u]) return;
        visited[u] = true;
        for(int v : compressedGraph[u])
            dfs(v);
        componentsTopo.push_back(u); // post-order
    };
    for(int i = 0; i < numSCC; i++)
        dfs(i);
    reverse(componentsTopo.begin(), componentsTopo.end());

    cout << numSCC << '\n';
    for(int i = 0; i < numSCC; i++){
        cout << connectedComponents[componentsTopo[i]].size() << ' ';
        for(int u : connectedComponents[componentsTopo[i]])
            cout << u << ' ';
        cout << '\n';
    }

    return 0;
}

static void* run(void*){
    exit(solve());
}

int32_t main(){
    const size_t STACK_SIZE = 512ull * 1024 * 1024;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, STACK_SIZE);

    pthread_t thread;
    pthread_create(&thread, &attr, &run, nullptr);
    pthread_join(thread, nullptr);

    return 0;
}

#include "../footer.hpp"
