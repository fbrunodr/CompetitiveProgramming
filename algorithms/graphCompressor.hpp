#ifndef FBRUNODR_GRAPH_COMPRESSION
#define FBRUNODR_GRAPH_COMPRESSION

#include "../header.hpp"


pair<vi, vec<vi>> graphCompressor(vec<vi>& AL){
    const int UNVISITED = -1;

    int n = AL.size();
    vi dfs_num(n, UNVISITED);
    vi dfs_low(n, 0);
    vec<bool> visited(n, 0);
    stack<int> St;
    int dfsNumberCounter = 0, numSCC = 0;
    vi compressedNode(n, -1);

    f<void(int)> tarjanSCC = [&](int u){
        dfs_low[u] = dfs_num[u] = dfsNumberCounter;
        dfsNumberCounter++;
        St.push(u);
        visited[u] = true;
        for(auto& v : AL[u]){
            if(dfs_num[v] == UNVISITED)
                tarjanSCC(v);
            if(visited[v])
                dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }

        if(dfs_low[u] == dfs_num[u]){
            compressedNode[u] = numSCC++;
            while(1){
                int v = St.top(); St.pop();
                compressedNode[v] = compressedNode[u];
                visited[v] = false;
                if(u == v) break;
            }
        }
    };

    for(int u = 0; u < n; u++)
        if(dfs_num[u] == UNVISITED)
            tarjanSCC(u);

    vec<vi> compressedGraph(numSCC);
    for(int u = 0; u < n; u++)
        for(int& v : AL[u]){
            int u_ = compressedNode[u];
            int v_ = compressedNode[v];
            if(u_ == v_) continue;
            compressedGraph[u_].push_back(v_);
        }

    return {compressedNode, compressedGraph};
}


#endif
