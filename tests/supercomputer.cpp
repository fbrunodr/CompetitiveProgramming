// see https://open.kattis.com/problems/supercomputer
// latest submission: https://open.kattis.com/submissions/16971554

#include "../dataStructures/FenwickTree.hpp"

int32_t main(){
    fastIO();
    int N, K; cin >> N >> K;

    vi A(N+1, 0);

    auto sum = [](int a, int b){ return a + b; };
    auto sub = [](int a, int b){ return a - b; };
    FenwickTree<int> cumulative(A, sum, sub);

    while(K--){
        char type; cin >> type;
        if(type == 'F'){
            int i; cin >> i;
            A[i] = (A[i]+1)&1;
            cumulative.update(i, A[i]);
        }
        else{
            int i, j; cin >> i >> j;
            cout << cumulative.RQ(i, j) << endl;
        }
    }

    return 0;
}
