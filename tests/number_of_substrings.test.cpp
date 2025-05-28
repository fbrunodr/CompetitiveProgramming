#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../header.hpp"
#include "../algorithms/stringUtils.hpp"

int solve(){
    fastIO();
    str s; cin >> s;
    vi sa = suffixArray(s);
    vi lcp = kasai(s, sa);
    int ans = 0;
    for(int i = 0; i < s.size(); i++)
        ans += s.size() - sa[i] - lcp[i];
    cout << ans << '\n';

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
