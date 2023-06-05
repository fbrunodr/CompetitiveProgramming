#include<bits/stdc++.h>
using namespace std;

class HashString{
    using vi = vector<int>;
    using i64 = long long;

    int p;
    int MOD;

    string T;

    int n;
    vi pPow;
    vi pPowInv;
    vi h;

    int extEuclid(int a, int b, int &x, int &y){ // pass x and y by ref
        int xx = y = 0;
        int yy = x = 1;
        while (b){ // repeats until b == 0
            int q = a / b;
            tie(a, b) = tuple(b, a % b);
            tie(x, xx) = tuple(xx, x - q * xx);
            tie(y, yy) = tuple(yy, y - q * yy);
        }
        return a; // returns gcd(a, b)
    }

    int modInverse(int b){               // returns b^(-1) (mod MOD)
        int x, y;
        int d = extEuclid(b, MOD, x, y); // to get b*x + MOD*y == d
        if (d != 1)
            exit(1809);            // to indicate failure
        return (x + MOD) % MOD; // this is the answer
    }

    void computeRollingHash(){
        pPow[0] = 1;
        for(int i = 1; i < n; i++)
            pPow[i] = ((i64)pPow[i-1] * p) % MOD;
        pPowInv[n-1] = modInverse(pPow[n-1]);
        for(int i = n-2; i >= 0; i--)   // taking advantage of Fermat's Little Theorem
            pPowInv[i] = ((i64)pPowInv[i+1] * p) % MOD;
        h[0] = 0;
        for (int i = 0; i < n; ++i) {                  // O(n)
            if (i != 0) h[i] = h[i-1];                 // rolling hash
            h[i] += ((i64)T[i] * pPow[i]) % MOD;
            h[i] %= MOD;
        }
    }

    public:
    HashString(string& _T, int _p, int _MOD) : T(_T), p(_p), MOD(_MOD) {
        n = T.size();
        pPow = vi(n);
        pPowInv = vi(n);
        h = vi(n);
        computeRollingHash();
    }

    HashString(string& _T) : HashString(_T, 131, 1e9+7) {}

    int getHash(int L, int R){
        if(L == 0) return h[R];
        int ans = 0;
        ans = (h[R] - h[L-1] + MOD) % MOD;    // compute differences
        ans = ((i64)ans * pPowInv[L]) % MOD;  // remove P[L]^-1 (mod M)
        return ans;
    }
};
