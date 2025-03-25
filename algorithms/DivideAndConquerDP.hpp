#ifndef FBRUNODR_DIVIDE_AND_CONQUER_DP
#define FBRUNODR_DIVIDE_AND_CONQUER_DP

#include "../header.hpp"

template<typename T>
class DivideAndConquerDP{

    using _T = optional<T>;
    using _T_T = pair<_T, _T>;

private:
    // [0, N-1]
    int N;

    function<T(int)> singleElement;
    function<T(T&,int)> elementMerge;

    vec<vec<_T>> memo;

    void solveMoving(int mid, int d, bool toRight){
        if(memo[mid][d] != nullopt)
            return;
        int idx = toRight ? mid + d : mid - d;
        if(d == 0){
            memo[mid][d] = singleElement(idx);
            return;
        }
        solveMoving(mid, d-1, toRight);
        memo[mid][d] = elementMerge(*memo[mid][d-1], idx);
    }

    _T_T solve(int i, int j, int L, int R){
        int mid1 = (L + R) / 2;
        int mid2 = mid1 + 1;

        if(j < mid1)
            return solve(i, j, L, mid1-1);
        else if(i > mid2)
            return solve(i, j, mid2+1, R);
        else if(j == mid1){
            solveMoving(mid1, mid1-i, false);
            return {memo[mid1][mid1-i], nullopt};
        }
        else if(i == mid2){
            solveMoving(mid2, j-mid2, true);
            return {memo[mid2][j-mid2], nullopt};
        }
        else{
            solveMoving(mid1, mid1-i, false);
            solveMoving(mid2, j-mid2, true);
            return {memo[mid1][mid1-i], memo[mid2][j-mid2]};
        }

        return {nullopt, nullopt};
    }

    void init(int L, int R){
        if(L > R)
            return;

        int mid1 = (L + R) / 2;
        int mid2 = mid1 + 1;

        memo[mid1] = vec<_T>(mid1 - L + 1, nullopt);
        if(mid2 <= R)
            memo[mid2] = vec<_T>(R - mid2 + 1, nullopt);

        init(L, mid1-1);
        init(mid2+1, R);
    }

    public:
    DivideAndConquerDP(int _n, function<T(int)> _ele, function<T(T&,int)> _eleMerge){
        N = _n;
        memo = vec<vec<_T>>(N);
        init(0, N-1);
        singleElement = _ele;
        elementMerge = _eleMerge;
    }

    // The merge of intervals is left for the user
    _T_T RQ(int i, int j){
        if(i > j)
            exit(8742);
        return solve(i, j, 0, N-1);
    }
};


#endif
