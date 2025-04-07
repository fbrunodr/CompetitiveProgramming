#ifndef FBRUNODR_SEG_TREE
#define FBRUNODR_SEG_TREE

#include "../header.hpp"


template<typename T>
class PointUpdateSegTree{

    using vT = vec<T>;

private:
    function<T(T,T)> merge;

    int n;
    vT st;
    vT A;

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    void build(int p, int L, int R){  // O(n)
        if (L == R){
            st[p] = A[L];
            return;
        }
        int m = (L + R) / 2;
        build(l(p), L, m);
        build(r(p), m + 1, R);
        st[p] = merge(st[l(p)], st[r(p)]);
    }

    T RQ(int p, int L, int R, int i, int j){  // O(log n)
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        if(i > m)
            return RQ(r(p), m+1, R, i, j);
        else if(j <= m)
            return RQ(l(p), L, m, i, j);
        return merge(
            RQ(l(p), L, m, i, j),
            RQ(r(p), m+1, R, i, j)
        );
    }

    void update(int p, int L, int R, int i, T& newVal){ // O(log n)
        if ((L == R) && (L == i))  // found the segment
            st[p] = A[i] = newVal;
        else{
            int m = (L + R) / 2;
            if(i <= m)
                update(l(p), L, m, i, newVal);
            else
                update(r(p), m + 1, R, i, newVal);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

public:
    PointUpdateSegTree() {}

    // O(n)
    PointUpdateSegTree(const vT& _A, function<T(T,T)> _merge) : A(_A), merge(_merge) {
        n = A.size();
        st = vT(4*n);
        build(1, 0, n - 1);
    }

    // O(log(n))
    void update(int i, T newVal) {
        update(1, 0, n - 1, i, newVal);
    }

    // O(log(n))
    T RQ(int i, int j) {
        if(i > j)
            exit(8742);
        return RQ(1, 0, n - 1, i, j);
    }

    // O(1)
    T pick(int i){
        return A[i];
    }
};


template<typename DataType, typename LazyType>
class LazySegTree{

    using T = DataType;
    using Q = LazyType;
    using vT = vec<T>;
    using vQ = vec<Q>;

private:
    function<T(T,T)> merge;
    function<void(T&,Q,int,int)> internalNodeUpdator;
    function<void(Q&,Q)> lazyUpdator;

    int n;
    vT st;
    vQ lazy;
    vec<bool> hasLazy;

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    void build(const vT& A, int p, int L, int R){  // O(n)
        if (L == R){
            st[p] = A[L];
            return;
        }
        int m = (L + R) / 2;
        build(A, l(p), L, m);
        build(A, r(p), m + 1, R);
        st[p] = merge(st[l(p)], st[r(p)]);
    }

    void applyLazy(int p, const Q& val) {
        if (!hasLazy[p]) {
            lazy[p] = val;
            hasLazy[p] = true;
        } else {
            lazyUpdator(lazy[p], val);
        }
    }

    void propagate(int p, int L, int R){
        if (!hasLazy[p]) return;

        internalNodeUpdator(st[p], lazy[p], L, R);

        if (L != R){
            applyLazy(l(p), lazy[p]);
            applyLazy(r(p), lazy[p]);
        }

        hasLazy[p] = false;
    }

    T RQ(int p, int L, int R, int i, int j){
        propagate(p, L, R);  // lazy propagation
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        if(i > m)
            return RQ(r(p), m+1, R, i, j);
        else if(j <= m)
            return RQ(l(p), L, m, i, j);
        return merge(
            RQ(l(p), L, m, i, j),
            RQ(r(p), m+1, R, i, j)
        );
    }

    void rangeUpdate(int p, int L, int R, int i, int j, Q& val){
        propagate(p, L, R);
        if (j < L || i > R) return; // no overlap
        if (i <= L && R <= j){  // total overlap
            applyLazy(p, val);
            propagate(p, L, R);
            return;
        }
        int m = (L + R) / 2;
        rangeUpdate(l(p), L, m, i, j, val);
        rangeUpdate(r(p), m + 1, R, i, j, val);
        st[p] = merge(st[l(p)], st[r(p)]);
    }

public:
    LazySegTree() {}

    // O(n)
    LazySegTree(
        const vT& _A,
        function<T(T,T)> _merge,
        std::variant<
            function<void(T&,Q)>,
            function<void(T&,Q,int,int)>
        > _nodeUpdator,
        function<void(Q&,Q)> _lazyUpdator
    ){
        n = _A.size();
        merge = _merge;
        lazyUpdator = _lazyUpdator;

        if (std::holds_alternative<function<void(T&,Q)>>(_nodeUpdator)) {
            auto f = std::get<function<void(T&,Q)>>(_nodeUpdator);
            internalNodeUpdator = [f](T& a, Q b, int, int) {
                f(a, b);
            };
        } else {
            internalNodeUpdator = std::get<function<void(T&,Q,int,int)>>(_nodeUpdator);
        }

        st = vT(4*n);
        lazy = vQ(4*n);
        hasLazy = vec<bool>(4*n, false);
        build(_A, 1, 0, n - 1);
    }

    // O(log(n))
    void rangeUpdate(int i, int j, Q val) {
        rangeUpdate(1, 0, n - 1, i, j, val);
    }

    // O(log(n))
    T RQ(int i, int j) {
        if(i > j)
            exit(8742);
        return RQ(1, 0, n - 1, i, j);
    }
};


#endif
