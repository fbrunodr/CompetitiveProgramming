// see https://open.kattis.com/problems/flippingcards

#include "../algorithms/MCBM.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

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
