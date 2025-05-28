#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_undirected"

#include "../header.hpp"
#include "../algorithms/eulerianTrail.hpp"

void solveCase(){
    int n, m; cin >> n >> m;
    vec<hash_multiset<int>> al(n);
    set<iii> edges;
    vi deg(n, 0);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        al[u].insert(v);
        al[v].insert(u);
        if(u > v)
            swap(u, v);
        edges.emplace(u, v, i);
        deg[u]++;
        deg[v]++;
    }

    {
        int n_odd = 0;
        for(int d : deg)
            if(d & 1)
                n_odd++;
        if(n_odd > 2){
            cout << "No\n";
            return;
        }
    }

    int start = 0;
    for(int u = 0; u < n; u++)
        if(al[u].size()){
            start = u;
            break;
        }
    for(int u = 0; u < n; u++)
        if(deg[u] & 1){
            start = u;
            break;
        }

    vi ans = getEulerianTrail<true>(al, start);
    if(ans.size() != m+1){
        cout << "No\n";
        return;
    }

    f<iii(int,int)> aux = [&](int u, int v){
        if(u > v) swap(u, v);
        return make_tuple(u, v, 0);
    };

    cout << "Yes\n";
    vi edgesAns;
    for(int i = 1; i < ans.size(); i++){
        auto it = edges.lower_bound(aux(ans[i-1], ans[i]));
        assert(it != edges.end());
        auto [u, v, idx] = *it;
        edgesAns.push_back(idx);
        edges.erase(it);
    }
    for(int u : ans)
        cout << u << ' ';
    cout << '\n';
    for(int e : edgesAns)
        cout << e << ' ';
    cout << '\n';
}

int solve(){
    fastIO();
    int t; cin >> t;
    while(t--)
        solveCase();

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
