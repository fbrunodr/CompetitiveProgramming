// see https://codeforces.com/problemset/problem/427/C

#include "../algorithms/GraphCompression.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    using vi = vector<int>;

    vi cost(n);
    for(auto& cost_i : cost)
        cin >> cost_i;

    int m; cin >> m;

    vector<vi> AL(n);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        u--; v--;
        AL[u].push_back(v);
    }

    GraphCompressor graphCompressor(AL);
    auto [compressedNode, compressedGraph] = graphCompressor.compress();

    int numSCC = compressedGraph.size();

    vector<vi> components(numSCC);
    for(int u = 0; u < n; u++){
        int compressedU = compressedNode[u];
        components[compressedU].push_back(u);
    }

    for(auto& component : components){
        for(auto& u : component)
            u = cost[u];
        sort(component.begin(), component.end());
    }

    using i64 = long long;
    i64 totalCost = 0;
    for(auto& component : components)
        totalCost += component.front();

    cout << totalCost << ' ';

    i64 count = 1;
    i64 MOD = 1e9 + 7;
    for(auto& component : components){
        int cheaper = component.front();
        int repeats = 1;
        for(int i = 1; i < component.size(); i++)
            if(component[i] == cheaper)
                repeats++;
            else
                break;
        count *= repeats;
        count %= MOD;
    }

    cout << count << endl;

    return 0;
}
