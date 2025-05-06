#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "../dataStructures/UnionFind.hpp"

int solve(){
    fastIO();
    int n, q; cin >> n >> q;
    UnionFind uf(n);
    while(q--){
        int type, u, v; cin >> type >> u >> v;
        if(type == 0)
            uf.unionSet(u,v);
        else
            cout << (uf.isSameSet(u, v) ? 1 : 0) << '\n';
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
