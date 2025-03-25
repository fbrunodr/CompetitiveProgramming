// see https://www.spoj.com/problems/HORRIBLE/

#include "../algorithms/RURQ.cpp"

int32_t main(){
    ios_base::sync_with_stdio(false);
    using i64 = long long;

    int testCases; cin >> testCases;

    while(testCases--){
        int N, C; cin >> N >> C;
        RURQ cumulative(N);

        while(C--){
            int type; cin >> type;
            if(type == 0){
                int p, q; i64 v;
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
