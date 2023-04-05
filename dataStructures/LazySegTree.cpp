#include <bits/stdc++.h>
using namespace std;

/**
 * T is the type of the data stored in the segTree.
 * 
 * Conquerer must be a functor with an associative operator over two T.
 * It does not need to be commutative.
 * 
 * Updator must be a functor that takes the current value, the update value
 * and returns the new value. It does not change the current value in place.
 * It must be distributive over the conquerer result.
 * 
 * ConquererIdentity is a value such that
 * Conquerer(val, ConquererIdentity) = Conquerer(ConquererIdentity, val) = val
 * 
 * UpdatorIdentity is used as OFF flag for lazy update. We must have
 * Update(UpdatorIdentity, val) = val
*/
template<typename T, typename Conquerer, typename Updator>
class LazySegTree{

    using vT = vector<T>;

private:
    int n;             // n = (int)A.size()
    vT A, st, lazy;    // the arrays
    T ConquererIdentity, UpdatorIdentity; // special values

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    void build(int p, int L, int R){  // O(n)
        if (L == R)
            st[p] = A[L];  // base case
        else{
            int m = (L + R) / 2;
            build(l(p), L, m);
            build(r(p), m + 1, R);
            st[p] = Conquerer{}(st[l(p)], st[r(p)]);
        }
    }

    void propagate(int p, int L, int R){
        if (lazy[p] != UpdatorIdentity){           // has a lazy flag
            st[p] = Updator{}(st[p], lazy[p]);     // update [L..R] value
            if (L != R){                           // not a leaf
                lazy[l(p)] = Updator{}(lazy[l(p)], lazy[p]);
                lazy[r(p)] = Updator{}(lazy[r(p)], lazy[p]);
            }
            else                                   // L == R, a single index
                A[L] = Updator{}(A[L], lazy[p]);   // time to update this
            lazy[p] = UpdatorIdentity;             // erase lazy flag
        }
    }

    T RQ(int p, int L, int R, int i, int j){  // O(log n)
        propagate(p, L, R);  // lazy propagation
        if (i > j)
            return ConquererIdentity;  // infeasible
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        return Conquerer{}(RQ(l(p), L, m, i, min(m, j)),
                       RQ(r(p), m + 1, R, max(i, m + 1), j));
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
            update(l(p), L, m, i, min(m, j), val);
            update(r(p), m + 1, R, max(i, m + 1), j, val);
            T lsubtree = Updator{}(st[l(p)], lazy[l(p)]);
            T rsubtree = Updator{}(st[r(p)], lazy[r(p)]);
            st[p] = Conquerer{}(lsubtree, rsubtree);
        }
    }

public:
    LazySegTree() {}

    LazySegTree(int sz, T _ConquererIdentity, T _UpdatorIdentity) : n(sz), st(4 * n) {
        ConquererIdentity = _ConquererIdentity;
        UpdatorIdentity = _UpdatorIdentity;
        lazy = vT(4*n, UpdatorIdentity);
    }

    LazySegTree(const vT &initialA, T _ConquererIdentity, T _UpdatorIdentity) :
    LazySegTree((int)initialA.size(), _ConquererIdentity, _UpdatorIdentity){
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, T val) { update(1, 0, n - 1, i, j, val); }

    T RQ(int i, int j) { return RQ(1, 0, n - 1, i, j); }
};
