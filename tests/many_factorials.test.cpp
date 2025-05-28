#define PROBLEM "https://judge.yosupo.jp/problem/many_factorials"

#include "../header.hpp"
#include "../algorithms/numberTheory.hpp"

int solve(){
    fastIO();
    const int MOD = 998244353;
    setFacts<MOD>(998244353-1);

    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        cout << fact[n] << '\n';
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
