#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"

#include "../header.hpp"
#include "../algorithms/numberTheory.hpp"

int solve(){
    fastIO();
    int t, m; cin >> t >> m;
    setFacts(min((int)1e7, m-1), m);
    while(t--){
        int n, k; cin >> n >> k;
        cout << C(n, k, m) << '\n';
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
