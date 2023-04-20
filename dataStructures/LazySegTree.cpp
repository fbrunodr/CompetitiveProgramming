#include <bits/stdc++.h>
using namespace std;

template<typename T>
class LazySegTree{

    using vT = vector<T>;
    using opT = function<T(T,T)>;

private:
    opT conquerer;
    opT updator;

    T RANGE_ERROR;
    T LAZY_OFF;

    int n;             // n = (int)A.size()
    vT A, st, lazy;    // the arrays

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

    void propagate(int p, int L, int R){
        if (lazy[p] != LAZY_OFF){                // has a lazy flag
            st[p] = updator(st[p], lazy[p]);     // update [L..R] value
            if (L != R){                         // not a leaf
                lazy[l(p)] = (lazy[l(p)] != LAZY_OFF) ? updator(lazy[l(p)], lazy[p]) : lazy[p];
                lazy[r(p)] = (lazy[r(p)] != LAZY_OFF) ? updator(lazy[r(p)], lazy[p]) : lazy[p];
            }
            else                                 // L == R, a single index
                A[L] = updator(A[L], lazy[p]);   // time to update this
            lazy[p] = LAZY_OFF;                  // erase lazy flag
        }
    }

    T RQ(int p, int L, int R, int i, int j){  // O(log n)
        propagate(p, L, R);  // lazy propagation
        if (i > j)
            return RANGE_ERROR;  // infeasible
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        return conquer(RQ(l(p), L, m, i, min(j, m)),
                       RQ(r(p), m + 1, R, max(m + 1, i), j));
    }

    void update(int p, int L, int R, int i, int j, T val){ // O(log n)
        propagate(p, L, R);
        if (i > j)
            return;
        if ((i <= L) && (R <= j)){  // found the segment
            lazy[p] = val;      // update this
            propagate(p, L, R);
        }
        else{
            int m = (L + R) / 2;
            update(l(p), L, m, i, min(j, m), val);
            update(r(p), m + 1, R, max(m + 1, i), j, val);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

public:
    LazySegTree() {}

    LazySegTree(const vT &initialA, opT _conquerer, opT _updator, T _RANGE_ERROR, T _LAZY_OFF) :
    conquerer(_conquerer), updator(_updator), RANGE_ERROR(_RANGE_ERROR), LAZY_OFF(_LAZY_OFF) {
        n = initialA.size();
        st = vT(4*n);
        lazy = vT(4*n, LAZY_OFF);
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, T val) { update(1, 0, n - 1, i, j, val); }

    T RQ(int i, int j) { return RQ(1, 0, n - 1, i, j); }
};
