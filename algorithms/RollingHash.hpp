#ifndef FBRUNODR_ROLLING_HASH
#define FBRUNODR_ROLLING_HASH

#include "numberTheory.hpp"

const vi hashPrimes{131, 167, 173, 199};
vec<vi> hashPrimePow;
vec<vi> hashPrimePowInv;

void setRollingHashPowers(int maxN){
    hashPrimePow = vec<vi>(4, vi(maxN));
    hashPrimePowInv = vec<vi>(4, vi(maxN));

    for(int idx = 0; idx < 4; idx++){
        hashPrimePow[idx][0] = 1;
        for(int i = 1; i < maxN; i++)
            hashPrimePow[idx][i] = (hashPrimePow[idx][i-1] * hashPrimes[idx]) % MOD;
        hashPrimePowInv[idx][maxN-1] = modInverse(hashPrimePow[idx][maxN-1]);
        for(int i = maxN-2; i >= 0; i--)
            hashPrimePowInv[idx][i] = (hashPrimePowInv[idx][i+1] * hashPrimes[idx]) % MOD;
    }
}


bitset<128> moveRight(bitset<128> str_hashed, int move_size){
    bitset<128> ans;
    constexpr bitset<128> lowest_32(0xFFFFFFFF);
    for(int idx = 0; idx < 4; idx++){
        int curr = ((str_hashed >> (idx*32)) & lowest_32).to_ullong();
        curr = (curr * hashPrimePow[idx][move_size]) % MOD;
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
        curr = (curr * hashPrimePowInv[idx][move_size]) % MOD;
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
                h[idx][i] += (T[i] * hashPrimePow[idx][i]) % MOD;
                h[idx][i] %= MOD;
            }
        }
    }

    public:
    RollingHash(const string& _T) : T(_T) {
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
                current = (current * hashPrimePowInv[idx][L]) % MOD;
            }
            bitset<128> piece(current);
            piece <<= 32 * idx;
            ans |= piece;
        }
        return ans;
    }
};


bitset<128> get_bitset(const string& s){
    return RollingHash(s).getHash(0, s.size() - 1);
}


#endif
