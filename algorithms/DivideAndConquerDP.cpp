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
 
    T solveLeft(int L, int mid){
        if(memo[mid].count(L))
            return memo[mid][L];
        if(L == mid)
            return singleElement(L);
        auto subProblem = solveLeft(L+1, mid);
        return memo[mid][L] = elementMerge(subProblem, L);
    }
 
    T solveRight(int mid, int R){
        if(memo[mid].count(R))
            return memo[mid][R];
        if(mid == R)
            return singleElement(R);
        auto subProblem = solveRight(mid, R-1);
        return memo[mid][R] = elementMerge(subProblem, R);
    }
 
    TT solve(int i, int j, int L, int R){
        int mid = (L + R) / 2;
        if(i == mid)
            return {solveRight(mid, j), EMPTY};
        if(mid == j)
            return {solveLeft(i, mid), EMPTY};
        if(mid < i)
            return solve(i, j, mid+1, R);
        if(mid > j)
            return solve(i, j, L, mid-1);
        if(i < mid && mid < j){
            auto left = solveLeft(i, mid);
            auto right = solveRight(mid+1, j);
            return {left, right};
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
