#ifndef FBRUNODR_ROLLING_HASH
#define FBRUNODR_ROLLING_HASH

#include "../header.hpp"

const int MOD = 1e9 + 7;
const vi p{131, 167, 173, 199};
vec<vi> pPow;
vec<vi> pPowInv;

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

int modInverse(int b){
    int x, y;
    int d = extEuclid(b, MOD, x, y);
    if (d != 1)
        exit(1809);
    return (x + MOD) % MOD;
}

void setRollingHashPowers(int maxN){
    pPow = vec<vi>(4, vi(maxN));
    pPowInv = vec<vi>(4, vi(maxN));

    for(int idx = 0; idx < 4; idx++){
        pPow[idx][0] = 1;
        for(int i = 1; i < maxN; i++)
            pPow[idx][i] = (pPow[idx][i-1] * p[idx]) % MOD;
        pPowInv[idx][maxN-1] = modInverse(pPow[idx][maxN-1]);
        for(int i = maxN-2; i >= 0; i--)
            pPowInv[idx][i] = (pPowInv[idx][i+1] * p[idx]) % MOD;
    }
}


bitset<128> moveRight(bitset<128> str_hashed, int move_size){
    bitset<128> ans;
    constexpr bitset<128> lowest_32(0xFFFFFFFF);
    for(int idx = 0; idx < 4; idx++){
        int curr = ((str_hashed >> (idx*32)) & lowest_32).to_ullong();
        curr = (curr * pPow[idx][move_size]) % MOD;
        bitset<128> piece(curr);
        piece <<= 32 * idx;
        ans |= piece;
    }
    return ans;
}


bitset<128> moveLeft(bitset<128> str_hashed, int move_size){
    bitset<128> ans;
    constexpr bitset<128> lowest_32(0xFFFFFFFF);
    for(int idx = 0; idx < 4; idx++){
        int curr = ((str_hashed >> (idx*32)) & lowest_32).to_ullong();
        curr = (curr * pPowInv[idx][move_size]) % MOD;
        bitset<128> piece(curr);
        piece <<= 32 * idx;
        ans |= piece;
    }
    return ans;
}


bitset<128> sum(bitset<128> str_hashed_1, bitset<128> str_hashed_2){
    bitset<128> ans;
    constexpr bitset<128> lowest_32(0xFFFFFFFF);
    for(int idx = 0; idx < 4; idx++){
        int curr_1 = ((str_hashed_1 >> (idx*32)) & lowest_32).to_ullong();
        int curr_2 = ((str_hashed_2 >> (idx*32)) & lowest_32).to_ullong();
        int curr = (curr_1 + curr_2) % MOD;
        bitset<128> piece(curr);
        piece <<= 32 * idx;
        ans |= piece;
    }
    return ans;
}


class RollingHash{
    int n;
    string T;
    vec<vi> h;

    void computeRollingHash(){
        for(int idx = 0; idx < 4; idx++){
            h[idx][0] = 0;
            for (int i = 0; i < n; ++i) {
                if (i != 0) h[idx][i] = h[idx][i-1];
                h[idx][i] += (T[i] * pPow[idx][i]) % MOD;
                h[idx][i] %= MOD;
            }
        }
    }

    public:
    RollingHash(string& _T) : T(_T) {
        n = T.size();
        h = vec<vi>(4, vi(n));
        computeRollingHash();
    }

    bitset<128> getHash(int L, int R){
        bitset<128> ans;
        for(int idx = 0; idx < 4; idx++){
            int current = 0;
            if(L == 0){
                current = h[idx][R];
            }
            else{
                current = (h[idx][R] - h[idx][L-1] + MOD) % MOD;
                current = (current * pPowInv[idx][L]) % MOD;
            }
            bitset<128> piece(current);
            piece <<= 32 * idx;
            ans |= piece;
        }
        return ans;
    }
};


// For debugging purposes
bitset<128> get_bitset(string& s){
    return RollingHash(s).getHash(0, s.size() - 1);
}


#endif
