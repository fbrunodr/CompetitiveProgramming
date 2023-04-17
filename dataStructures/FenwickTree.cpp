#include<bits/stdc++.h>
using namespace std;
#define LSOne(S) ((S) & -(S))

// IDX 0 IS NOT USED
template<typename T>
class FenwickTree{
    
    using vT = vector<T>;
    using opT = function<T(T,T)>;

    private:
    int n;
    vT BIT;
    opT op;

    public:
    FenwickTree() {}

    FenwickTree(vT& A, opT _op) : op(_op) {
        BIT = A;
        n = A.size();
        for(int i = 1; i < n; i++){
            int parent = i + LSOne(i);
            if(parent < n)
                BIT[parent] = op(BIT[parent], BIT[i]);
        }
    }

    T update(int i, T val){
        for(; i < n; i += LSOne(i))
            BIT[i] = op(BIT[i], val);
    }

    T cumulative(int i){
        T ans = BIT[i];
        for(int j = i-LSOne(i); j; j -= LSOne(j))
            ans = op(ans, BIT[j]);
        return ans;
    }
};
