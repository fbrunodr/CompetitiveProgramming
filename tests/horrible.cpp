// see https://www.spoj.com/problems/HORRIBLE/
// The above site doesn't have modern C++ :(

#include "../algorithms/RURQ.hpp"

int32_t main(){
    fastIO();

    int testCases; cin >> testCases;

    while(testCases--){
        int N, C; cin >> N >> C;
        RURQ cumulative(N);

        while(C--){
            int type; cin >> type;
            if(type == 0){
                int p, q, v;
                cin >> p >> q >> v;
                cumulative.rangeUpdate(p, q, v);
            }
            else{
                int p, q; cin >> p >> q;
                cout << cumulative.rsq(p, q) << endl;
            }
        }
    }

    return 0;
}
