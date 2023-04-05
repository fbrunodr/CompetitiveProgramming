#include <bits/stdc++.h>
using namespace std;

/**
 * T is the type of the data stored in the segTree.
 * 
 * Conquerer must be a functor with an associative operator over two T.
 * It does not need to be commutative.
 * 
 * ConquererIdentity is a value such that
 * Conquerer(val, ConquererIdentity) = Conquerer(ConquererIdentity, val) = val
*/
template<typename T, typename Conquerer>
class FrozenSegTree{

    using vT = vector<T>;

private:
    int n;               // n = (int)A.size()
    vT A, st;            // the arrays
    T ConquererIdentity; // special values

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

    T RQ(int p, int L, int R, int i, int j){  // O(log n)
        if (i > j)
            return ConquererIdentity;  // infeasible
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        return Conquerer{}(RQ(l(p), L, m, i, min(m, j)),
                       RQ(r(p), m + 1, R, max(i, m + 1), j));
    }

public:
    FrozenSegTree() {}

    FrozenSegTree(int sz, T _ConquererIdentity) : n(sz), st(4 * n) {
        ConquererIdentity = _ConquererIdentity;
    }

    FrozenSegTree(const vT &initialA, T _ConquererIdentity) :
    FrozenSegTree((int)initialA.size(), _ConquererIdentity){
        A = initialA;
        build(1, 0, n - 1);
    }

    T RQ(int i, int j) { return RQ(1, 0, n - 1, i, j); }
};
