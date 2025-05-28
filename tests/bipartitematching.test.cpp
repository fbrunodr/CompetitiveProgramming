#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include "../header.hpp"
#include "../algorithms/MCBM.hpp"

int solve(){
    fastIO();
    int L, R, M; cin >> L >> R >> M;
    vec<vi> adj(L + R);
    for(int i = 0; i < M; i++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v + L);
    }

    auto [cardinality, match] = MCBM(adj, L);
    cout << cardinality << '\n';
    for(int i = 0; i < L; i++)
        if(match[i] != -1)
            cout << i << ' ' << match[i] - L << '\n';

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
