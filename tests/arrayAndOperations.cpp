// see https://codeforces.com/contest/498/problem/C
// latest submission: https://codeforces.com/contest/498/submission/312267640

#include "../algorithms/MCBM.cpp"
#include "../algorithms/numberTheory.cpp"


int32_t main(){
    fastIO();
    setPrimes(1e5);

    int n, m; cin >> n >> m;

    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;

    vector<vi> factors(n);

    int Vleft = 0;
    int Vright = 0;
    for(int i = 0; i < n; i++){
        for(auto [p, alpha] : getFactors(a[i]))
            while(alpha--)
                factors[i].push_back(p);
        if(i%2 == 0)
            Vleft += factors[i].size();
        else
            Vright += factors[i].size();
    }

    vi initialPos(n, 0);
    for(int i = 2; i < n; i += 2){
        initialPos[i] = initialPos[i-2];
        initialPos[i] += factors[i-2].size();
    }

    initialPos[1] = Vleft;
    for(int i = 3; i < n; i += 2){
        initialPos[i] = initialPos[i-2];
        initialPos[i] += factors[i-2].size();
    }

    int V = Vleft + Vright;
    vector<vi> AL(V);

    for(int i = 0; i < m; i++){
        int l, r; cin >> l >> r;
        l--; r--;

        for(int i = 0; i < factors[l].size(); i++)
            for(int j = 0; j < factors[r].size(); j++){
                int u = initialPos[l] + i;
                int v = initialPos[r] + j;

                if(factors[l][i] == factors[r][j]){
                    AL[u].push_back(v);
                    AL[v].push_back(u);
                }
            }
    }

    cout << MCBM(AL, Vleft).get().first << endl;

    return 0;
}
