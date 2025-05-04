#define PROBLEM "https://judge.yosupo.jp/problem/associative_array"

#include "../header.hpp"

int solve(){
    fastIO();
    int q; cin >> q;
    hash_map<int,int> a;
    while(q--){
        int type; cin >> type;
        if(type == 0){
            int k, v; cin >> k >> v;
            a[k] = v;
        }
        else if(type == 1){
            int k; cin >> k;
            cout << a[k] << '\n';
        }
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
