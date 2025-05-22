#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../header.hpp"
#include "../algorithms/numberTheory.hpp"

int solve(){
    fastIO();
    setPrimes(1e9);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        auto factors = getFactors(n);
        int k = 0;
        for(auto [p, alpha] : factors)
            k += alpha;
        cout << k << ' ';
        for(auto [p, alpha] : factors)
            while(alpha--)
                cout << p << ' ';
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
