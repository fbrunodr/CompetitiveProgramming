#include <bits/stdc++.h>
using namespace std;

template<typename T>
class FrozenSegTree{

    using vT = vector<T>;
    using _T = optional<T>;
    using v_T = vector<_T>;

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

    void build(int p, int L, int R){
        if (L == R)
            st[p] = A[L];  // base case
        else{
            int m = (L + R) / 2;
            build(l(p), L, m);
            build(r(p), m + 1, R);
            st[p] = conquer(st[l(p)], st[r(p)]);
        }
    }

    _T RQ(int p, int L, int R, int i, int j){
        if (i > j)
            return nullopt;
        if ((i <= L) && (R <= j))
            return st[p];  // found the segment
        int m = (L + R) / 2;
        return conquer(RQ(l(p), L, m, i, min(j, m)),
                       RQ(r(p), m + 1, R, max(m + 1, i), j));
    }

public:
    FrozenSegTree() {}

    // O(n)
    FrozenSegTree(const vT& _A, function<T(T,T)> _conquerer) : A(_A), conquerer(_conquerer) {
        n = A.size();
        st = v_T(4*n, nullopt);
        build(1, 0, n - 1);
    }

    // O(log(n))
    T RQ(int i, int j) {
        assert(i <= j);
        return *RQ(1, 0, n - 1, i, j);
    }

    // O(1)
    T pick(int i){
        return A[i];
    }
};
