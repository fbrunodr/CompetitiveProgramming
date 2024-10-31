#include<bits/stdc++.h>
using namespace std;

template<typename T>
class Cum{
    using vT = vector<T>;
    using opT = function<T(T,T)>;

    private:
    int n;
    vT A;
    opT op, inv;

    public:
    Cum(vT _A, opT _op, opT _inv){
        n = _A.size();
        A = _A;
        op = _op;
        inv = _inv;
        for(int i = 1; i < A.size())
            A[i] = op(A[i], A[i-1]);
    }

    T get(int i){
        return A[i];
    }

    T range(int i, int j){
        if(i > j)
            exit(8742);
        if(i == 0)
            return get(i);
        return inv(get(j), get(i-1));
    }
};