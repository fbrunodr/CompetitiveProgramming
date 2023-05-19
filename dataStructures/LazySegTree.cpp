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
    vT st, lazy;       // the arrays

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

    void propagate(int p, int L, int R){
        if (lazy[p] == LAZY_OFF) // lazy flag off
            return;
        st[p] = updator(st[p], lazy[p]);     // update [L..R] value
        if (L != R){                         // not a leaf
            lazy[l(p)] = (lazy[l(p)] == LAZY_OFF) ? lazy[p] : updator(lazy[l(p)], lazy[p]);
            lazy[r(p)] = (lazy[r(p)] == LAZY_OFF) ? lazy[p] : updator(lazy[r(p)], lazy[p]);
        }
        lazy[p] = LAZY_OFF;                 // erase lazy flag
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

    void rangeUpdate(int p, int L, int R, int i, int j, T val){ // O(log n)
        propagate(p, L, R);
        if (i > j)
            return;
        if ((i <= L) && (R <= j)){  // found the segment
            lazy[p] = val;          // update this
            propagate(p, L, R);
        }
        else{
            int m = (L + R) / 2;
            rangeUpdate(l(p), L, m, i, min(j, m), val);
            rangeUpdate(r(p), m + 1, R, max(m + 1, i), j, val);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

public:
    LazySegTree() {}

    LazySegTree(const vT& _A, opT _conquerer, opT _updator, T _RANGE_ERROR, T _LAZY_OFF) :
    conquerer(_conquerer), updator(_updator), RANGE_ERROR(_RANGE_ERROR), LAZY_OFF(_LAZY_OFF) {
        n = _A.size();
        st = vT(4*n);
        lazy = vT(4*n, LAZY_OFF);
        build(_A, 1, 0, n - 1);
    }

    void rangeUpdate(int i, int j, T val) {
        rangeUpdate(1, 0, n - 1, i, j, val);
    }

    T RQ(int i, int j) {
        return RQ(1, 0, n - 1, i, j);
    }
};
