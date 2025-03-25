// see https://open.kattis.com/problems/flippingcards
// latest submission: https://open.kattis.com/submissions/16966379

#include "../algorithms/MCBM.cpp"

int32_t main(){
    fastIO();

    int T; cin >> T;

    using vi = vector<int>;
    vector<vi> AL;

    while(T--){
        int n; cin >> n;
        int V = 3*n;
        int VLeft = n;
        AL = vector<vi>(V);

        for(int card = 0; card < n; card++){
            int numFront, numBack; cin >> numFront >> numBack;
            numFront--;
            numBack--;
            AL[card].push_back(n+numFront);
            AL[card].push_back(n+numBack);
        }

        MCBM solve(AL, VLeft);
        auto [nMacthes, matches] = solve.get();

        nMacthes == n ? cout << "possible" << endl : cout << "impossible" << endl;
    }
}
