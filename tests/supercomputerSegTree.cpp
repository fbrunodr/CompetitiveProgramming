// see https://open.kattis.com/problems/supercomputer

#include "../dataStructures/PointUpdateSegTree.cpp"

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K; cin >> N >> K;

    using vi = vector<int>;
    vi A(N+1, 0);

    auto sum = [](int a, int b){ return a + b; };
    PointUpdateSegTree<int> cumulative(A, sum);

    while(K--){
        char type; cin >> type;
        if(type == 'F'){
            int i; cin >> i;
            A[i] = (A[i]+1)&1;
            cumulative.update(i, A[i]);
        }
        else{
            int i, j; cin >> i >> j;
            cout << cumulative.RQ(i, j) << '\n';
        }
    }

    return 0;
}
