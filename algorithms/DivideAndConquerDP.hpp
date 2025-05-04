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

    f<T(int)> singleElement;
    f<T(T&,int)> elementMerge;

    int maxRecursionDepth;
    vec<vec<T>> memo;
    vec<vec<bool>> on;

    void solveMoving(int mid, int d, bool toRight){
        if(on[mid][d])
            return;
        int idx = toRight ? mid + d : mid - d;
        on[mid][d] = true;
        if(d == 0){
            memo[mid][d] = singleElement(idx);
            return;
        }
        solveMoving(mid, d-1, toRight);
        memo[mid][d] = elementMerge(memo[mid][d-1], idx);
    }

    _T_T solve(int i, int j, int L, int R, int depth){
        if(depth > maxRecursionDepth){
            T ans = singleElement(i);
            for(int idx = i+1; idx <= j; idx++)
                ans = elementMerge(ans, idx);
            return {ans, nullopt};
        }

        int mid1 = (L + R) / 2;
        int mid2 = mid1 + 1;

        if(j < mid1)
            return solve(i, j, L, mid1-1, depth+1);
        else if(i > mid2)
            return solve(i, j, mid2+1, R, depth+1);
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

    void init(int L, int R, int depth){
        if(L > R)
            return;
        if(depth > maxRecursionDepth)
            return;

        int mid1 = (L + R) / 2;
        int mid2 = mid1 + 1;

        memo[mid1] = vec<T>(mid1 - L + 1);
        on[mid1] = vec<bool>(mid1 - L + 1, false);
        if(mid2 <= R){
            memo[mid2] = vec<T>(R - mid2 + 1);
            on[mid2] = vec<bool>(R - mid2 + 1, false);
        }

        init(L, mid1-1, depth+1);
        init(mid2+1, R, depth+1);
    }

    public:
    DivideAndConquerDP(int _n, f<T(int)> _ele, f<T(T&,int)> _eleMerge, int maxDepth = 15){
        maxRecursionDepth = maxDepth;
        N = _n;
        memo = vec<vec<T>>(N);
        on = vec<vec<bool>>(N);
        init(0, N-1, 1);
        singleElement = _ele;
        elementMerge = _eleMerge;
    }

    // The merge of intervals is left for the user
    _T_T RQ(int i, int j){
        if(i > j)
            exit(8742);
        return solve(i, j, 0, N-1, 1);
    }
};


#endif
