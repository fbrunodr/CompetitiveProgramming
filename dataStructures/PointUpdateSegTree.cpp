#include <bits/stdc++.h>
using namespace std;

template<typename T>
class PointUpdateSegTree{

    using vT = vector<T>;
    using opT = function<T(T,T)>;

private:
    opT conquerer;
    opT updator;

    T RANGE_ERROR;

    int n;             // n = (int)A.size()
    vT st;             // the array

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    T conquer(const T a, const T b){
        if(a == RANGE_ERROR) return b;
        if(b == RANGE_ERROR) return a;
        return conquerer(a, b);
    }

    void build(const vT& A, int p, int L, int R){  // O(n)
        if (L == R)
            st[p] = A[L];  // base case
        else{
            int m = (L + R) / 2;
            build(A, l(p), L, m);
            build(A, r(p), m + 1, R);
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

    void update(int p, int L, int R, int i, T val){ // O(log n)
        if ((L == R) && (L == i))  // found the segment
            st[p] = updator(st[p], val);
        else{
            int m = (L + R) / 2;
            if(i <= m)
                update(l(p), L, m, i, val);
            else
                update(r(p), m + 1, R, i, val);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

public:
    PointUpdateSegTree() {}

    PointUpdateSegTree(const vT &initialA, opT _conquerer, opT _updator, T _RANGE_ERROR) :
    conquerer(_conquerer), updator(_updator), RANGE_ERROR(_RANGE_ERROR) {
        n = initialA.size();
        st = vT(4*n);
        build(initialA, 1, 0, n - 1);
    }

    void update(int i, T val) { update(1, 0, n - 1, i, val); }

    T RQ(int i, int j) { return RQ(1, 0, n - 1, i, j); }
};
