// see https://codeforces.com/contest/598/problem/C
// latest submission: https://codeforces.com/contest/598/submission/312370062

#include "../algorithms/integerGeometry.hpp"

int32_t main(){
    fastIO();

    int n; cin >> n;

    vector<pair<Vec, int>> vecs(n);
    for(int i = 0; i < n; i++){
        int x, y; cin >> x >> y;
        vecs[i] = {Vec(x,y), i+1};
    }

    sort(vecs.begin(), vecs.end());

    pair<int, int> best{n-1, 0};
    for(int i = 1; i < n; i++)
        if(Angle(vecs[i-1].first, vecs[i].first) < Angle(vecs[best.first].first, vecs[best.second].first))
            best = {i-1, i};

    cout << vecs[best.first].second << ' ' << vecs[best.second].second << endl;
 
    return 0;
}
