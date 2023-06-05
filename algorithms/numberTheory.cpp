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
        exit(1809);            // to indicate failure
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

using vi = vector<int>;

vi primes;
vector<bool> _isPrime;
int maxTestable;

void setPrimes(int maxNum){
    _isPrime = vector<bool>(maxNum + 1, true);
    _isPrime[0] = _isPrime[1] = false;
    for(int i = 2; i <= maxNum; i++){
        if(!_isPrime[i]) continue;
        if((i64)i*i > maxNum) continue;
        for(int k = i*i; k <= maxNum; k += i)
            _isPrime[k] = false;
    }

    for(int i = 2; i <= maxNum; i++)
        if(_isPrime[i])
            primes.push_back(i);

    maxTestable = min((i64)INT_MAX, (i64)maxNum*maxNum);
}

bool isPrime(int x){
    if(x < 0)
        exit(1765);
    if(x > maxTestable)
        exit(8011);

    // O(1)
    if(x < _isPrime.size())
        return _isPrime[x];
    // O(sqrt(n/log(n)))
    else{
        for(auto& prime : primes){
            if((i64)prime*prime > x)
                return true;
            if(x%prime == 0)
                return false;
        }
    }

    return true;
}
