#include<bits/stdc++.h>
using namespace std;
 
template<typename T>
class DivideAndConquerDP{
 
    using TT = pair<T, T>;
 
private:
    // [0, N-1]
    int N;
 
    function<T(int)> singleElement;
    function<T(T&,int)> elementMerge;
    T EMPTY;
 
    vector<unordered_map<int, T>> memo;
 
    void solveLeft(int mid, int L){
        if(memo[mid].count(L))
            return;
        if(L == mid){
            memo[mid][L] = singleElement(L);
            return;
        }
        solveLeft(mid, L+1);
        memo[mid][L] = elementMerge(memo[mid][L+1], L);
    }
 
    void solveRight(int mid, int R){
        if(memo[mid].count(R))
            return;
        if(mid == R){
            memo[mid][R] = singleElement(R);
            return;
        }
        solveRight(mid, R-1);
        memo[mid][R] = elementMerge(memo[mid][R-1], R);
    }
 
    TT solve(int i, int j, int L, int R){
        int mid1 = (L + R) / 2;
        int mid2 = mid1 + 1;

        if(j < mid1)
            return solve(i, j, L, mid1-1);
        else if(i > mid2)
            return solve(i, j, mid2+1, R);
        else if(j == mid1){
            solveLeft(mid1, i);
            return {memo[mid1][i], EMPTY};
        }
        else if(i == mid2){
            solveRight(mid2, j);
            return {memo[mid2][j], EMPTY};
        }
        else{
            solveLeft(mid1, i);
            solveRight(mid2, j);
            return {memo[mid1][i], memo[mid2][j]};
        }
 
        return {EMPTY, EMPTY};
    }
 
    public:
    DivideAndConquerDP(int _n, function<T(int)> _ele, function<T(T&,int)> _eleMerge, T empty){
        N = _n;
        memo = vector<unordered_map<int, T>>(N);
        singleElement = _ele;
        elementMerge = _eleMerge;
        EMPTY = empty;
    }
 
    // The merge of intervals is left for the user
    TT RQ(int i, int j){
        assert(i <= j);
        return solve(i, j, 0, N-1);
    }
};
