// see https://open.kattis.com/problems/birthday
// latest submission: https://open.kattis.com/submissions/16966168

#include "../algorithms/ArticulationPointsAndBridges.hpp"

int32_t main(){
    int p, c; cin >> p >> c;

    while(!(p == 0 && c == 0)){
        using vi = vector<int>;
        vector<vi> AL(p);

        while(c--){
            int a, b; cin >> a >> b;
            AL[a].push_back(b);
            AL[b].push_back(a);
        }

        ArticulationPointsAndBridges solve(AL);

        auto [articulationPoints, bridges] = solve.get();

        if(bridges.empty())
            cout << "No" << endl;
        else
            cout << "Yes" << endl;

        cin >> p >> c;
    }

    return 0;
}
