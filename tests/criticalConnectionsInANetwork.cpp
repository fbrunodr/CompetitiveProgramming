// see https://leetcode.com/problems/critical-connections-in-a-network/

#include "../algorithms/ArticulationPointsAndBridges.cpp"

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        using vi = vector<int>;
        vector<vi> AL(n);
        for(auto& connection : connections){
            int u = connection[0];
            int v = connection[1];
            AL[u].push_back(v);
            AL[v].push_back(u);
        }

        ArticulationPointsAndBridges solve(AL);
        auto [articulationPoints, bridges] = solve.get();

        vector<vi> ans;
        for(auto& [u, v] : bridges)
            ans.push_back( vi{u, v} );

        return ans;
    }
};
