#ifndef FBRUNODR_ARTICULATION_POINTS_AND_BRIDGES
#define FBRUNODR_ARTICULATION_POINTS_AND_BRIDGES

#include "../header.hpp"

class ArticulationPointsAndBridges{
private:

    const int UNVISITED = -1;
    int n;
    vec<vi>& AL;
    vi dfs_num, dfs_low, dfs_parent, articulationVertexes;
    vii bridges;
    int dfsNumberCounter, dfsRoot, rootChildren;

    void articulationPointAndBridge(int u) {
        dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
        for (auto& v : AL[u]){
            if (dfs_num[v] == UNVISITED){ // a tree edge
                dfs_parent[v] = u;
                if (u == dfsRoot)
                    ++rootChildren; // special case, root

                articulationPointAndBridge(v);

                if (dfs_low[v] >= dfs_num[u])   // for articulation point
                    articulationVertexes.push_back(u); // store this info first
                if (dfs_low[v] > dfs_num[u])    // for bridge
                    bridges.emplace_back( min(u,v), max(u, v) );
                dfs_low[u] = min(dfs_low[u], dfs_low[v]); // subtree, always update
            }
            else if (v != dfs_parent[u])                  // if a non-trivial cycle
                dfs_low[u] = min(dfs_low[u], dfs_num[v]); // then can update
        }
    }

public:

    ArticulationPointsAndBridges(vec<vi>& _AL) : AL(_AL) {}

    pair<vi, vii> get(){
        n = AL.size();
        dfs_num = vi(n, UNVISITED);
        dfs_low = vi(n, 0);
        dfs_parent = vi(n, -1);
        articulationVertexes = vi();
        bridges = vii();
        dfsNumberCounter = 0;
        for (int u = 0; u < n; ++u)
            if (dfs_num[u] == UNVISITED) {
                dfsRoot = u; rootChildren = 0;
                articulationPointAndBridge(u);
                if(rootChildren > 1){ // special case
                    articulationVertexes.push_back(u);
                }
            }

        return {articulationVertexes, bridges};
    }
};


#endif
