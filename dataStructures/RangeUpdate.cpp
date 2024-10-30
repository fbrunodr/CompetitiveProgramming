#include<bits/stdc++.h>
using namespace std;

template<typename T>
class RangeOperation{
    using vT = vector<T>;
    using opT = function<T(T,T)>;

    private:
        int n;
        vT A;
        opT op, inv;

    public:
    RangeOperation(int _n, T initialVal, opT _op, opT _inv){
        n = _n;
        A = vT(n+1, initialVal);
        op = _op;
        inv = _inv;
    }

    void range_update(int l, int r, T val){
        if(r < l) return;
        A[l] = op(A[l], val);
        A[r+1] = inv(A[r+1], val);
    }

    vT get_vector(){
        vT ans(n);
        ans[0] = A[0];
        for(int i = 1; i < n; i++)
            ans[i] = op(ans[i-1], A[i]);
        return ans;
    }

    void clear(T initialVal){
        A = vT(n+1, initialVal);
    }
};