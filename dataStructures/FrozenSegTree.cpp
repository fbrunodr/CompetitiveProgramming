#include <bits/stdc++.h>
using namespace std;

template<typename T>
class FrozenSegTree{

    using vT = vector<T>;
    using opT = function<T(T,T)>;

private:
    opT conquerer;
    T RANGE_ERROR;

    int n;             // n = (int)A.size()
    vT A, st;          // the arrays

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    T conquer(const T a, const T b){
        if(a == RANGE_ERROR) return b;
        if(b == RANGE_ERROR) return a;
        return conquerer(a, b);
    }

    void build(int p, int L, int R){  // O(n)
        if (L == R)
            st[p] = A[L];  // base case
        else{
            int m = (L + R) / 2;
            build(l(p), L, m);
            build(r(p), m + 1, R);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

    T RQ(int p, int L, int R, int i, int j){  // O(log n)
        if (i > j)
            return RANGE_ERROR;  // infeasible
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        return conquer(RQ(l(p), L, m, i, min(j, m)),
                       RQ(r(p), m + 1, R, max(m + 1, i), j));
    }

public:
    FrozenSegTree() {}

    FrozenSegTree(const vT &initialA, opT _conquerer, T _RANGE_ERROR) :
    n(initialA.size()), conquerer(_conquerer), RANGE_ERROR(_RANGE_ERROR){
        A = initialA;
        st = vT(4*n);
        build(1, 0, n - 1);
    }

    T RQ(int i, int j) { return RQ(1, 0, n - 1, i, j); }
};
