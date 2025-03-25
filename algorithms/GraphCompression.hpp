#ifndef FBRUNODR_GRAPH_COMPRESSION
#define FBRUNODR_GRAPH_COMPRESSION

#include "../header.hpp"

class GraphCompressor{

private:

    const int UNVISITED = -1;

    int n;
    int dfsNumberCounter, numSCC;
    vi dfs_num, dfs_low, visited;
    stack<int> St;

    vi compressedNode;
    vec<vi> compressedGraph;

    vec<vi>& AL;

    void tarjanSCC(int u){
        dfs_low[u] = dfs_num[u] = dfsNumberCounter;
        dfsNumberCounter++;
        St.push(u);
        visited[u] = 1;
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
                visited[v] = 0;
                if(u == v) break;
            }
        }
    }

public:
    GraphCompressor(vec<vi>& _AL) :  AL(_AL) {}

    pair<vi, vec<vi>> compress(){
        n = AL.size();
        dfs_num = vi(n, UNVISITED);
        dfs_low = vi(n, 0);
        visited = vi(n, 0);
        while(!St.empty()) St.pop();
        dfsNumberCounter = numSCC = 0;

        compressedNode = vi(n, -1);

        for(int u = 0; u < n; u++)
            if(dfs_num[u] == UNVISITED)
                tarjanSCC(u);

        compressedGraph = vec<vi>(numSCC);
        for(int u = 0; u < n; u++)
            for(int& v : AL[u]){
                int u_ = compressedNode[u];
                int v_ = compressedNode[v];
                if(u_ == v_) continue;
                compressedGraph[u_].push_back(v_);
            }

        return {compressedNode, compressedGraph};
    }
};


#endif
