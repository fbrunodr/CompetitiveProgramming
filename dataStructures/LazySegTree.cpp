#include <bits/stdc++.h>
using namespace std;

template<typename DataType, typename LazyType>
class LazySegTree{

    using T = DataType;
    using Q = LazyType;

    using vT = vector<T>;
    using vQ = vector<Q>;

private:
    function<T(T,T)> conquerer;
    function<void(T&,Q,int,int)> nodeUpdator;
    function<void(Q&,Q)> lazyUpdator;

    T RANGE_ERROR;
    Q LAZY_OFF;

    int n;
    vT st;
    vQ lazy;

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    T conquer(T a, T b){
        if(a == RANGE_ERROR) return b;
        if(b == RANGE_ERROR) return a;
        return conquerer(a, b);
    }

    void build(const vT& A, int p, int L, int R){  // O(n)
        if (L == R)
            st[p] = A[L];
        else{
            int m = (L + R) / 2;
            build(A, l(p), L, m);
            build(A, r(p), m + 1, R);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

    void propagate(int p, int L, int R){
        if (lazy[p] == LAZY_OFF)
            return;
        nodeUpdator(st[p], lazy[p], L, R);
        if (L != R){
            if(lazy[l(p)] == LAZY_OFF)
                lazy[l(p)] = lazy[p];
            else
                lazyUpdator(lazy[l(p)], lazy[p]);
            if(lazy[r(p)] == LAZY_OFF)
                lazy[r(p)] = lazy[p];
            else
                lazyUpdator(lazy[r(p)], lazy[p]);
        }
        lazy[p] = LAZY_OFF;
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

    void rangeUpdate(int p, int L, int R, int i, int j, Q val){ // O(log n)
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

    LazySegTree(
        const vT& _A,
        function<T(T,T)> _conquerer,
        function<void(T&,Q,int,int)> _nodeUpdator,
        function<void(Q&,Q)> _lazyUpdator,
        T _RANGE_ERROR,
        Q _LAZY_OFF
    ){
        n = _A.size();
        conquerer = _conquerer;
        nodeUpdator = _nodeUpdator;
        lazyUpdator = _lazyUpdator;
        RANGE_ERROR = _RANGE_ERROR;
        LAZY_OFF = _LAZY_OFF;

        st = vT(4*n);
        lazy = vQ(4*n, LAZY_OFF);
        build(_A, 1, 0, n - 1);
    }

    void rangeUpdate(int i, int j, Q val) {
        rangeUpdate(1, 0, n - 1, i, j, val);
    }

    T RQ(int i, int j) {
        return RQ(1, 0, n - 1, i, j);
    }
};
