#include "../dataStructures/FenwickTree.cpp"

/**
 * Range increment update
 * Range query sum
*/
class RURQ{

    using i64 = long long;
    using vi64 = vector<i64>;

private: // needs two helper FTs
    int n;
    FenwickTree<i64> purq;
    FenwickTree<i64> rupq;

    void rupq_rangeUpdate(int i, int j, i64 v){
        rupq.increment(i, v);
        if(j+1 < n)
            rupq.increment(j+1, -v);
    }

    i64 rupq_pointQuery(int i){
        return rupq.cumulative(i);
    }

public:
    RURQ(int _n) : n(_n + 1) {
        auto sum = [](i64 a, i64 b){ return a + b; };
        auto sub = [](i64 a, i64 b){ return a - b; };

        vi64 empty(n, 0);
        purq = FenwickTree<i64>(empty, sum, sub);
        rupq = FenwickTree<i64>(empty, sum, sub);
    }

    void rangeUpdate(int i, int j, i64 v){
        rupq_rangeUpdate(i, j, v);      // [ui, ui+1, .., uj] +v
        purq.increment(i, v * (i - 1)); // -(ui-1)*v before ui
        if(j + 1 < n)
            purq.increment(j + 1, -v * j);  // +(uj-ui+1)*v after uj
    }
    
    i64 rsq(int j){
        return rupq_pointQuery(j) * j -  // optimistic calculation
               purq.cumulative(j);       // cancelation factor
    }

    i64 rsq(int i, int j) { return rsq(j) - rsq(i - 1); } // standard
};
