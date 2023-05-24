#include<bits/stdc++.h>
using namespace std;
using i64 = long long;
int MOD = 1e9 + 7;

int mod(int x, int m = MOD){
    return ((x%m) + m) % m;
}

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

int modInverse(int b, int m = MOD){  // returns b^(-1) (mod m)
    int x, y;
    int d = extEuclid(b, m, x, y);   // to get b*x + m*y == d
    if (d != 1)
        exit(1);            // to indicate failure
    return (x + m) % m;
}

int modPow(int base, int power, int m = MOD){
    int ans = 1;
    while(power > 0){
        if(power&1)
            ans = (i64) ans * base % m;
        power >>= 1;
        base = (i64) base * base % m;
    }
    return ans;
}
