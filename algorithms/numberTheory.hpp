#ifndef FBRUNODR_NUMBER_THEORY
#define FBRUNODR_NUMBER_THEORY

#include "../header.hpp"

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
            ans =  ans * base % m;
        power >>= 1;
        base =  base * base % m;
    }
    return ans;
}


vi primes;
vec<bool> _isPrime;
int maxTestable;

void setPrimes(int maxNum){
    _isPrime = vec<bool>(maxNum + 1, true);
    _isPrime[0] = _isPrime[1] = false;
    for(int i = 2; i <= maxNum; i++){
        if(!_isPrime[i]) continue;
        if(i*i > maxNum) continue;
        for(int k = i*i; k <= maxNum; k += i)
            _isPrime[k] = false;
    }

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

void setFacts(int maxNum){
    fact = vi(maxNum + 1);
    factInv = vi(maxNum + 1);
    fact[0] = 1;
    for(int i = 1; i <= maxNum; i++)
        fact[i] = (  fact[i-1] * i ) % MOD;
    factInv[maxNum] = modInverse(fact[maxNum]);
    for(int i = maxNum - 1; i >= 0; i--)
        factInv[i] = ( factInv[i+1] * (i+1) ) % MOD;
}

int C(int n, int k){
    if (n < k) return 0;
    if (n >= MOD) return ( C(n%MOD, k%MOD) * C(n/MOD, k/MOD)) % MOD;
    return (fact[n]*factInv[k]%MOD * factInv[n-k]) % MOD;
}


vec<vi> chooses_memo;
int C_dp(int n, int k){
    if(n < k) return 0;
    int& ans = chooses_memo[n][k];
    if(ans != -1) return ans;
    return (C_dp(n-1, k-1) + C_dp(n-1, k)) % MOD;
}


// Use this only if up and down are needed at the output
// otherwise use only get_frac below this class
struct Frac{
    private:
    int up, down;

    public:
    Frac(){}

    Frac(int num){
        up = num;
        down = 1;
    }

    Frac(int _up, int _down){
        if(_down == 0)
            exit(1010);
        if(_up == 0){
            up = 0; down = 1;
        }
        else{
            int common = gcd(_up, _down);
            up = _up / common;
            down = _down / common;
        }
    }

    Frac operator+(Frac other){
        return Frac(
            mod(up * other.down + other.up * down),
            mod(down * other.down)
        );
    }

    Frac operator-(Frac other){
        return Frac(
            mod(up * other.down - other.up * down),
            mod(down * other.down)
        );
    }

    Frac operator*(Frac other){
        return Frac(
            mod(up * other.up),
            mod(down * other.down)
        );
    }

    Frac operator/(Frac other){
        if(other.up == 0)
            exit(1011);
        return Frac(
            mod(up * other.down),
            mod(down * other.up)
        );
    }

    Frac operator+(int num) const {
        return Frac(mod( num * down + up ), down);
    }

    friend Frac operator+(int num, const Frac& obj) {
        return Frac(mod( num * obj.down + obj.up ), obj.down);
    }

    Frac operator-(int num) const {
        return Frac(mod( -num * down + up ), down);
    }

    friend Frac operator-(int num, const Frac& obj) {
        return Frac(mod( num * obj.down - obj.up ), obj.down);
    }

    Frac operator*(int num) const {
        return Frac(mod(num*up), down);
    }

    friend Frac operator*(int num, const Frac& obj) {
        return Frac(mod(num*obj.up), obj.down);
    }

    Frac operator/(int num) const {
        return Frac(up, mod(num*down));
    }

    friend Frac operator/(int num, const Frac& obj) {
        return Frac(obj.up, mod(num*obj.down));
    }

    Frac& operator=(int num) {
        up = num;
        down = 1;
        return *this;
    }

    ii get_up_down(){
        return make_pair(up, down);
    }

    int get(){
        return mod(up * modInverse(down));
    }
};


int get_frac(int up, int down){
    return mod(  up * modInverse(down) );
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
