#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"

#include "../header.hpp"
#include "../algorithms/gaussianElimination.hpp"

int solve(){
    fastIO();
    int n, m; cin >> n >> m;
    vec<vi> a(n, vi(m+1));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> a[i][j];
    for(int i = 0; i < n; i++)
        cin >> a[i][m];

    vi ans;
    vec<vi> basis;
    const int MOD = 998244353;
    gaussianEliminationOnField<MOD>(a, ans, basis);
    if(ans.empty()){
        cout << "-1\n";
        return 0;
    }

    cout << basis.size() << '\n';

    for(int i = 0; i < m; i++)
        cout << ans[i] << ' ';
    cout << '\n';

    for(auto& v : basis){
        for(int i = 0; i < m; i++)
            cout << v[i] << ' ';
        cout << "\n";
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
