#ifndef FBRUNODR_SEG_TREE
#define FBRUNODR_SEG_TREE

#include "../header.hpp"


template<typename T>
class PointUpdateSegTree{

    using vT = vec<T>;
    using _T = optional<T>;
    using v_T = vec<_T>;

private:
    function<T(T,T)> conquerer;

    int n;
    v_T st;
    vT A;

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    _T conquer(_T a, _T b){
        if(a == nullopt) return b;
        if(b == nullopt) return a;
        return make_optional(conquerer(*a, *b));
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

    _T RQ(int p, int L, int R, int i, int j){  // O(log n)
        if (i > j)
            return nullopt;
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        return conquer(RQ(l(p), L, m, i, min(j, m)),
                       RQ(r(p), m + 1, R, max(m + 1, i), j));
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
    PointUpdateSegTree(const vT& _A, function<T(T,T)> _conquerer) : A(_A), conquerer(_conquerer) {
        n = A.size();
        st = v_T(4*n, nullopt);
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
        return *RQ(1, 0, n - 1, i, j);
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
    using _T = optional<T>;
    using _Q = optional<Q>;
    using v_T = vec<_T>;
    using v_Q = vec<_Q>;

private:
    function<T(T,T)> conquerer;
    function<void(T&,Q,int,int)> nodeUpdator;
    function<void(Q&,Q)> lazyUpdator;

    int n;
    v_T st;
    v_Q lazy;

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    _T conquer(_T a, _T b){
        if(a == nullopt) return b;
        if(b == nullopt) return a;
        return make_optional(conquerer(*a, *b));
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
        if (lazy[p] == nullopt)
            return;
        nodeUpdator(*st[p], *lazy[p], L, R);
        if (L != R){
            if(lazy[l(p)] == nullopt)
                lazy[l(p)] = lazy[p];
            else
                lazyUpdator(*lazy[l(p)], *lazy[p]);
            if(lazy[r(p)] == nullopt)
                lazy[r(p)] = lazy[p];
            else
                lazyUpdator(*lazy[r(p)], *lazy[p]);
        }
        lazy[p] = nullopt;
    }

    _T RQ(int p, int L, int R, int i, int j){
        propagate(p, L, R);  // lazy propagation
        if (i > j)
            return nullopt;
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        return conquer(RQ(l(p), L, m, i, min(j, m)),
                       RQ(r(p), m + 1, R, max(m + 1, i), j));
    }

    void rangeUpdate(int p, int L, int R, int i, int j, Q& val){
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

    // O(n)
    LazySegTree(
        const vT& _A,
        function<T(T,T)> _conquerer,
        function<void(T&,Q,int,int)> _nodeUpdator,
        function<void(Q&,Q)> _lazyUpdator
    ){
        n = _A.size();
        conquerer = _conquerer;
        nodeUpdator = _nodeUpdator;
        lazyUpdator = _lazyUpdator;

        st = v_T(4*n, nullopt);
        lazy = v_Q(4*n, nullopt);
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
        return *RQ(1, 0, n - 1, i, j);
    }
};

#endif
