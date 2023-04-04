#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using vi64 = vector<i64>;

class SegmentTree{
private:
    /**
     * Function that receives two positional i64 arguments (i64 left, i64 right).
     * THIS FUNCTION SHOULD BE ASSOCIATIVE OTHERWISE THIS SEGTREE WON'T WORK.
     * It does not need to be commutative.
     * Let p be a node in this segTree. Let a and b be its two children with
     * values left and right respectively. This should return the value of p.
    */
    i64 (*conquerer)(i64, i64);
    /**
     * Function that receives two positional i64 arguments (i64 currVal, i64 update).
     * THIS FUNCTION SHOULD BE DISTRIBUTIVE OVER CONQUERER RESULT.
     * Returns what should be the new value of currVal. (notice it does not change currVal).
     * Ex.:
     * If this is a increment update, it should return currVal + update
     * It this is a segTree that sets the value of a interval, this should return update 
    */
    i64 (*updator)(i64, i64);

    const i64 OFF = LONG_MIN;

    int n;             // n = (int)A.size()
    vi64 A, st, lazy;  // the arrays

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    i64 conquer(i64 a, i64 b){
        if (a == OFF)
            return b;  // corner case
        if (b == OFF)
            return a;
        return conquerer(a, b);  // prefer min or max
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
        if (lazy[p] != OFF){                       // has a lazy flag
            st[p] = updator(st[p], lazy[p]);       // update [L..R] value
            if (L != R){                           // not a leaf
                lazy[l(p)] != OFF ? lazy[l(p)] = updator(lazy[l(p)], lazy[p]) : lazy[l(p)] = lazy[p];
                lazy[r(p)] != OFF ? lazy[r(p)] = updator(lazy[r(p)], lazy[p]) : lazy[r(p)] = lazy[p];
            }
            else                                   // L == R, a single index
                A[L] = updator(A[L], lazy[p]);     // time to update this
            lazy[p] = OFF;                         // erase lazy flag
        }
    }

    i64 RQ(int p, int L, int R, int i, int j){  // O(log n)
        propagate(p, L, R); // lazy propagation
        if (i > j)
            return OFF; // infeasible
        if ((i <= L) && (R <= j))
            return st[p]; // found the segment
        int m = (L + R) / 2;
        return conquer(RQ(l(p), L, m, i, min(m, j)),
                       RQ(r(p), m + 1, R, max(i, m + 1), j));
    }

    void update(int p, int L, int R, int i, int j, i64 val){ // O(log n)
        propagate(p, L, R);
        if (i > j)
            return;
        if ((i <= L) && (R <= j)){  // found the segment
            lazy[p] = val;      // update this
            propagate(p, L, R);
        }
        else{
            int m = (L + R) / 2;
            update(l(p), L, m, i, min(m, j), val);
            update(r(p), m + 1, R, max(i, m + 1), j, val);
            i64 lsubtree = (lazy[l(p)] != OFF) ? updator(st[l(p)], lazy[l(p)]) : st[l(p)];
            i64 rsubtree = (lazy[r(p)] != OFF) ? updator(st[r(p)], lazy[r(p)]) : st[r(p)];
            st[p] = conquer(lsubtree, rsubtree);
        }
    }

public:
    SegmentTree(int sz, i64 (*conquerer)(i64, i64), i64 (*updator)(i64, i64)) :
        n(sz), st(4 * n), lazy(4 * n, OFF), conquerer(conquerer), updator(updator) {}

    SegmentTree(const vi64 &initialA, i64 (*conquerer)(i64, i64), i64 (*updator)(i64, i64)) :
        SegmentTree((int)initialA.size(), conquerer, updator){
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, i64 val) { update(1, 0, n - 1, i, j, val); }

    i64 RQ(int i, int j) { return RQ(1, 0, n - 1, i, j); }
};
