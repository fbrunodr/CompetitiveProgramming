#ifndef FBRUNODR_NUMBER_THEORY
#define FBRUNODR_NUMBER_THEORY

#include "../header.hpp"

template<auto MOD>
int mod(int x){
    return ((x%MOD) + MOD) % MOD;
}

int mod(int x, int MOD){
    return ((x%MOD) + MOD) % MOD;
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

int modInverse(int b, int m){       // returns b^(-1) (mod m)
    int x, y;
    int d = extEuclid(b, m, x, y);  // to get b*x + m*y == d
    if (d != 1)
        exit(1809);                 // to indicate failure
    return (x + m) % m;
}

template<auto MOD>
int modInverse(int x){
	return x == 1 ? 1 : modInverse<MOD>(x - MOD % x) * (MOD / x + 1) % MOD;
}

template<auto MOD>
int modPow(int base, int power){
    int ans = 1;
    while(power > 0){
        if(power&1)
            ans =  ans * base % MOD;
        power >>= 1;
        base =  base * base % MOD;
    }
    return ans;
}

int modPow(int base, int power, int MOD){
    int ans = 1;
    while(power > 0){
        if(power&1)
            ans =  ans * base % MOD;
        power >>= 1;
        base =  base * base % MOD;
    }
    return ans;
}


vi primes;
vec<bool> _isPrime;
int maxTestable;

void setPrimes(int maxNum){
    _isPrime = vec<bool>(maxNum + 1, true);
    _isPrime[0] = _isPrime[1] = false;
    int primeCount = 0;
    for(int i = 2; i*i <= maxNum; i++){
        if(!_isPrime[i]) continue;
        ++primeCount;
        for(int j = i*i; j <= maxNum; j += i)
            _isPrime[j] = false;
    }

    primes.reserve(primeCount + 1);

    for(int i = 2; i <= maxNum; i++)
        if(_isPrime[i])
            primes.push_back(i);

    maxTestable = maxNum*maxNum;
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
            if(prime*prime > x)
                return true;
            if(x%prime == 0)
                return false;
        }
    }

    return true;
}

map<int, int> getFactors(int x){
    if(x < 0)
        exit(1765);
    if(x > maxTestable)
        exit(8011);

    // btw this is faster than unordered, as all INT have at most
    // 9 different prime factors (2 * 3 * 7 * ... * 29 > INT_MAX)
    map<int, int> ans;

    // O(sqrt(n/log(n)))
    for(auto& prime : primes){
        if(prime*prime > x)
            break;
        while(x % prime == 0){
            x /= prime;
            ans[prime]++;
        }
    }

    if(x != 1)
        ans[x]++;

    return ans;
}

vi getPrimeDivisors(int x){
    auto factors = getFactors(x);
    vi ans;
    for(auto& [p, alpha] : factors)
        ans.push_back(p);
    return ans;
}

vi getDivisors(int x){
    auto factors = getFactors(x);
    vi ans{1};

    // the number with most divisors up to 1e7
    // is 8648640 with only 448 divisors, so this
    // here should run just fine.
    for(auto& [p, alpha] : factors){
        int k = ans.size();
        int curr = 1;
        for(int i = 0; i < alpha; i++){
            curr *= p;
            for(int i = 0; i < k; i++)
                ans.push_back(ans[i]*curr);
        }
    }

    sort(ans.begin(), ans.end());
    return ans;
}

vi fact;
vi factInv;

void setFacts(int maxNum, int MOD){
    fact = vi(maxNum + 1);
    factInv = vi(maxNum + 1);
    fact[0] = 1;
    for(int i = 1; i <= maxNum; i++)
        fact[i] = (  fact[i-1] * i ) % MOD;
    factInv[maxNum] = modInverse(fact[maxNum], MOD);
    for(int i = maxNum - 1; i >= 0; i--)
        factInv[i] = ( factInv[i+1] * (i+1) ) % MOD;
}

int C(int n, int k, int MOD){
    if (n < k) return 0;
    if (n >= MOD) return ( C(n%MOD, k%MOD, MOD) * C(n/MOD, k/MOD, MOD)) % MOD;
    return (fact[n]*factInv[k]%MOD * factInv[n-k]) % MOD;
}


vec<vi> chooses_memo;
int C_dp(int n, int k, int MOD){
    if(n < k) return 0;
    int& ans = chooses_memo[n][k];
    if(ans != -1) return ans;
    return (C_dp(n-1, k-1, MOD) + C_dp(n-1, k, MOD)) % MOD;
}


template<auto MOD>
int get_frac(int up, int down){
    return mod<MOD>(up * modInverse(down, MOD));
}

int get_frac(int up, int down, int MOD){
    return mod(up * modInverse(down, MOD), MOD);
}

/*
    Same as running:
    ans = 0;
    for(int i = a; i <= b; i++)
        ans += x / i;
    0 < x,
    0 < a <= b

    Runs in O(sqrt(x))
*/
int sum_x_over_i(int x, int a, int b) {
    int ans = 0;
    int i = a;
    while (i <= b) {
        int v = x / i;
        if(v == 0) return ans;
        int j = x / v;
        j = min(j, b);
        ans += v * (j - i + 1);
        i = j + 1;
    }
    return ans;
}

#endif
