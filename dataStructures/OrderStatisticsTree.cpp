#include "FenwickTree.cpp"

#include <bits/extc++.h>                         // pbds
using namespace __gnu_pbds;
using OST = tree<int, null_type, less<int>, rb_tree_tag, 
    tree_order_statistics_node_update>;

/**
 * Because it is implemented using Fenwick Tree, can't insert x <= 0!!!!
*/
class FenwickTreeOST {

    using vi = vector<int>;

private:
    int maxVal;
    FenwickTree<int> ft;
    bool repeatedKeys;

public:
    FenwickTreeOST(int _maxVal, bool _repeatedKeys = false) : maxVal(_maxVal), repeatedKeys(_repeatedKeys) {
        vi freq(maxVal+1, 0);
        auto sum = [](int a, int b){ return a + b; };
        auto sub = [](int a, int b){ return a - b; };
        ft = FenwickTree<int>(freq, sum, sub);
    }

    bool has(int val){
        return ft.pick(val) != 0;
    }

    void insert(int val){
        if(repeatedKeys || (ft.pick(val) == 0) )
            ft.increment(val, 1);
    }

    void insertMany(int val, int quant){
        if(quant < 1) return;
        if(!repeatedKeys)
            return insert(val);
        ft.increment(val, quant);
    }

    void remove(int val){
        if(has(val))
            ft.increment(val, -1);
    }

    void removeMany(int val, int quant){
        if(quant < 1) return;
        int toRemove = min(quant, ft.pick(val));
        ft.increment(val, -toRemove);
    }

    void removeAll(int val){
        ft.increment(val, -ft.pick(val));
    }

    int orderOfKey(int key){
        if(key == 1) return 0;
        return ft.cumulative(key-1);
    }

    int findByOrder(int order){
        if(ft.cumulative(maxVal) <= order)
            return 1e9;

        int low = 1, high = maxVal;
        while(low < high){
            int mid = (low + high + 1) / 2;
            orderOfKey(mid) <= order ? low = mid : high = mid-1;
        }

        return low;
    }
};
