#ifndef FBRUNODR_RURQ
#define FBRUNODR_RURQ

#include "../dataStructures/FenwickTree.hpp"

/**
 * Range increment update
 * Range query sum
*/
class RURQ{

private: // needs two helper FTs
    int n;
    FenwickTree<int> purq;
    FenwickTree<int> rupq;

    void rupq_rangeUpdate(int i, int j, int v){
        rupq.increment(i, v);
        if(j+1 < n)
            rupq.increment(j+1, -v);
    }

    int rupq_pointQuery(int i){
        return rupq.cumulative(i);
    }

public:
    RURQ(int _n) : n(_n + 1) {
        auto sum = [](int a, int b){ return a + b; };
        auto sub = [](int a, int b){ return a - b; };

        vi empty(n, 0);
        purq = FenwickTree<int>(empty, sum, sub);
        rupq = FenwickTree<int>(empty, sum, sub);
    }

    void rangeUpdate(int i, int j, int v){
        rupq_rangeUpdate(i, j, v);      // [ui, ui+1, .., uj] +v
        purq.increment(i, v * (i - 1)); // -(ui-1)*v before ui
        if(j + 1 < n)
            purq.increment(j + 1, -v * j);  // +(uj-ui+1)*v after uj
    }
    
    int rsq(int j){
        return rupq_pointQuery(j) * j -  // optimistic calculation
               purq.cumulative(j);       // cancelation factor
    }

    int rsq(int i, int j) { return rsq(j) - rsq(i - 1); } // standard
};


#endif
