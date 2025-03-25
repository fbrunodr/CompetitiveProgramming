// see https://leetcode.com/problems/critical-connections-in-a-network/
// latest submission: https://leetcode.com/problems/critical-connections-in-a-network/submissions/1585118261/

#include "../algorithms/ArticulationPointsAndBridges.hpp"

class Solution {
public:
    vector<vi> criticalConnections(int n, vector<vi>& connections) {
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
