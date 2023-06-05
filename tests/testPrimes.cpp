#include "../algorithms/numberTheory.cpp"

int main(){
    int max = 2e6;
    setPrimes(max);

    assert(isPrime(1e9+7));
    assert(isPrime(1e9+9));
    assert(isPrime(137));
    assert(isPrime(999983));
    assert(isPrime(2));

    assert(!isPrime(0));
    assert(!isPrime(1));
    assert(!isPrime(4));
    assert(!isPrime(1e9));
    assert(!isPrime(2e5));

    vector<map<int, int>> factors(500'001);

    for(int i = 1; i <= 500'000; i++)
        factors[i] = getFactors(i);

    return 0;
}
