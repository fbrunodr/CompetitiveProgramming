#include <bits/stdc++.h>
using namespace std;

template<typename T>
class SegmentTree{

using vT = vector<T>;

private:
    /**
     * Function that receives two positional T arguments (T left, T right).
     * THIS FUNCTION SHOULD BE ASSOCIATIVE OTHERWISE THIS SEGTREE WON'T WORK.
     * It does not need to be commutative.
     * Let p be a node in this segTree. Let a and b be its two children with
     * values left and right respectively. This should return the value of p.
    */
    T (*conquerer)(const T&, const T&);
    /**
     * Function that receives two positional T arguments (T currVal, T update).
     * THIS FUNCTION SHOULD BE DISTRIBUTIVE OVER CONQUERER RESULT.
     * Returns what should be the new value of currVal. (notice it does not change currVal).
     * Ex.:
     * If this is a increment update, it should return currVal + update
     * It this is a segTree that sets the value of a interval, this should return update 
    */
    T (*updator)(const T&, const T&);

    T OFF;

    int n;           // n = (int)A.size()
    vT A, st, lazy;  // the arrays

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    T conquer(const T& a, const T& b){
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

    T RQ(int p, int L, int R, int i, int j){  // O(log n)
        if(updator != nullptr) // if you don't update you should consider using another solution
            propagate(p, L, R); // lazy propagation
        if (i > j)
            return OFF; // infeasible
        if ((i <= L) && (R <= j))
            return st[p]; // found the segment
        int m = (L + R) / 2;
        return conquer(RQ(l(p), L, m, i, min(m, j)),
                       RQ(r(p), m + 1, R, max(i, m + 1), j));
    }

    void update(int p, int L, int R, int i, int j, const T& val){ // O(log n)
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
            T lsubtree = (lazy[l(p)] != OFF) ? updator(st[l(p)], lazy[l(p)]) : st[l(p)];
            T rsubtree = (lazy[r(p)] != OFF) ? updator(st[r(p)], lazy[r(p)]) : st[r(p)];
            st[p] = conquer(lsubtree, rsubtree);
        }
    }

public:
    SegmentTree(int sz, T (*conquerer)(const T&, const T&), T (*updator)(const T&, const T&), T offVal) :
        n(sz), st(4 * n), conquerer(conquerer), updator(updator), OFF(offVal) {
            lazy = vT(4*n, OFF);
        }

    SegmentTree(const vT &initialA, T (*conquerer)(const T&, const T&), T (*updator)(const T&, const T&), T offVal) :
        SegmentTree((int)initialA.size(), conquerer, updator, offVal){
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, const T& val) { update(1, 0, n - 1, i, j, val); }

    T RQ(int i, int j) { return RQ(1, 0, n - 1, i, j); }
};
