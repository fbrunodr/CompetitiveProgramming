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
    vT A;
    opT op, inv;

    private:
    T cumulative(int i){
        T ans = BIT[i];
        for(int j = i-LSOne(i); j; j -= LSOne(j))
            ans = op(ans, BIT[j]);
        return ans;
    }

    public:
    FenwickTree() {}

    FenwickTree(vT& _A, opT _op, opT _inv) : A(_A), op(_op), inv(_inv) {
        n = A.size();
        BIT = A;
        for(int i = 1; i < n; i++){
            int parent = i + LSOne(i);
            if(parent < n)
                BIT[parent] = op(BIT[parent], BIT[i]);
        }
    }

    T update(int i, T newVal){
        for(int j = i; j < n; j += LSOne(j)){
            BIT[j] = inv(BIT[j], A[i]);
            BIT[j] = op(BIT[j], newVal);
        }
        A[i] = newVal;
    }

    T Query(int i, int j){
        if(i == 1) return cumulative(j);
        return inv(cumulative(j), cumulative(i));
    }
};
