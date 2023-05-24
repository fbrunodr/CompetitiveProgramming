// see https://codeforces.com/contest/498/problem/C

#include "../algorithms/MCBM.cpp"

using vi = vector<int>;

vi primes;

vi getFactors(int x){
    vi ans;
    for(auto& prime : primes)
        while(x%prime == 0){
            ans.push_back(prime);
            x /= prime;
        }

    if(x != 1)
        ans.push_back(x);

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int MAX_VAL = (1<<15);
    vector<bool> isPrime(MAX_VAL+1, true);
    isPrime[0] = isPrime[1] = false;
    for(int i = 2; i <= MAX_VAL; i++)
        if(isPrime[i])
            for(int k = i*i; k <= MAX_VAL; k += i)
                isPrime[k] = false;

    for(int i = 2; i <= MAX_VAL; i++)
        if(isPrime[i])
            primes.push_back(i);

    int n, m; cin >> n >> m;

    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;

    vector<vi> factors(n);

    int Vleft = 0;
    int Vright = 0;
    for(int i = 0; i < n; i++){
        factors[i] = getFactors(a[i]);
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
