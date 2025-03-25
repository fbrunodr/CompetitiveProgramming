#include "../algorithms/numberTheory.hpp"

int32_t main(){
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

    int MAX_N = 1e6;
    vector<map<int, int>> factors(MAX_N + 1);
    vi nDivisors(MAX_N+1, 1);

    int numberMostDivisors = 0, mostDivisors = 0;

    for(int i = 1; i <= MAX_N + 1; i++){
        for(auto [p_i, alpha] : getFactors(i))
            nDivisors[i] *= alpha + 1;
        if(nDivisors[i] > mostDivisors){
            mostDivisors = nDivisors[i];
            numberMostDivisors = i;
        }
    }

    printf("The positive integer < %lld with the most divisors is %lld, with %lld divisors!\n", MAX_N, numberMostDivisors, mostDivisors);

    return 0;
}
