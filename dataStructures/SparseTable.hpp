#ifndef FBRUNODR_SPARSE_TABLE
#define FBRUNODR_SPARSE_TABLE

#include "../header.hpp"

template<typename T>
class SparseTable{

    using vT = vec<T>;
    using opT = function<T(T,T)>;

private:
    vT A;
    vi P2, L2;
    vec<vT> SpT; // the Sparse Table

    opT conquerer;

public:
    SparseTable() {} // default constructor

    SparseTable(vT &initialA, opT _conquerer) : conquerer(_conquerer) {
        A = initialA;
        int n = (int)A.size();
        int L2_n = (int)log2(n) + 1;
        P2.assign(L2_n + 1, 0);
        L2.assign((1 << L2_n) + 1, 0);
        for (int i = 0; i <= L2_n; ++i){
            P2[i] = (1 << i); // to speed up 2^i
            L2[(1 << i)] = i; // to speed up log_2(i)
        }
        for (int i = 2; i < P2[L2_n]; ++i)
            if (L2[i] == 0)
                L2[i] = L2[i - 1]; // to fill in the blanks

        // the initialization phase
        SpT = vec<vT>(L2[n]+1, vT(n));
        for (int j = 0; j < n; ++j)
            SpT[0][j] = A[j]; // RQ of sub array [j..j]

        // the two nested loops below have overall time complexity = O(n log n)
        for (int i = 1; P2[i] <= n; ++i) // for all i s.t. 2^i <= n
            for (int j = 0; j + P2[i] - 1 < n; ++j){
                T x = SpT[i - 1][j];             // [j..j+2^(i-1)-1]
                T y = SpT[i - 1][j + P2[i - 1]]; // [j+2^(i-1)..j+2^i-1]
                SpT[i][j] = conquerer(x, y);
            }
    }

    T RQ(int i, int j){
        int k = L2[j - i + 1];         // 2^k <= (j-i+1)
        T x = SpT[k][i];               // covers [i..i+2^k-1]
        T y = SpT[k][j - P2[k] + 1];   // covers [j-2^k+1..j]
        return conquerer(x, y);
    }
};


#endif
