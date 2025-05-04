#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../algorithms/LCA.hpp"

int solve(){
    fastIO();

    int n, q; cin >> n >> q;

    vec<vi> tree(n);
    for(int i = 1; i < n; i++){
        int p_i; cin >> p_i;
        tree[p_i].push_back(i);
    }

    SpTLCA lca(tree, 0);

    while(q--){
        int u, v; cin >> u >> v;
        cout << lca.lca(u, v) << '\n';
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
