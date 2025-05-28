#define PROBLEM "https://judge.yosupo.jp/problem/eulerian_trail_directed"

#include "../header.hpp"
#include "../algorithms/eulerianTrail.hpp"

void solveCase(){
    int n, m; cin >> n >> m;
    vec<vi> al(n);
    set<iii> edges;
    vi out_in(n, 0);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        al[u].push_back(v);
        out_in[u]++;
        out_in[v]--;
        edges.emplace(u, v, i);
    }

    {
        map<int,int> freq;
        for(int u = 0; u < n; u++)
            if(out_in[u] > 1 || out_in[u] < -1){
                cout << "No\n";
                return;
            }
            else
                freq[out_in[u]]++;

        if(freq[1] > 1){
            cout << "No\n";
            return;
        }
    }

    int start = 0;
    for(int u = 0; u < n; u++)
        if(al[u].size()){
            start = u;
            break;
        }
    for(int u = 0; u < n; u++)
        if(out_in[u] == 1){
            start = u;
            break;
        }

    vi ans = getEulerianTrail(al, start);
    if(ans.size() != m+1){
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    vi edgesAns;
    for(int i = 1; i < ans.size(); i++){
        auto it = edges.lower_bound(make_tuple(ans[i-1], ans[i], 0));
        assert(it != edges.end());
        auto [u, v, idx] = *it;
        assert(make_pair(u, v) == make_pair(ans[i-1], ans[i]));
        edgesAns.push_back(idx);
        edges.erase(it);
    }
    for(int u : ans)
        cout << u << ' ';
    cout << '\n';
    for(int e : edgesAns)
        cout << e << ' ';
    cout << '\n';
}

int solve(){
    fastIO();
    int t; cin >> t;
    while(t--)
        solveCase();

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
