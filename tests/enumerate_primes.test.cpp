#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include "../header.hpp"
#include "../algorithms/numberTheory.hpp"

int solve(){
    fastIO();
    int n, a, b;
    cin >> n >> a >> b;
    setPrimes(n);
    vi ans;
    for(int i = b; i < primes.size() && primes[i] <= n; i += a)
        ans.push_back(primes[i]);
    cout << primes.size() << ' ' << ans.size() << '\n';
    for(int val : ans)
        cout << val << ' ';
    cout << '\n';

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
