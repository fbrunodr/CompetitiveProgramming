// see https://www.codechef.com/problems/TALCA?tab=statement
// latest submission: https://www.codechef.com/viewsolution/94425849

#include "../algorithms/LCA.hpp"

int32_t main(){
    fastIO();

    int N; cin >> N;

    using vi = vector<int>;

    vector<vi> AL(N+1);

    for(int i = 0; i < N-1; i++){
        int u, v; cin >> u >> v;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    // SegLCA solve(AL, 1);
    // SpTLCA solver(AL, 1);
    BinaryLiftLCA solver(AL, 1);

    int queries; cin >> queries;
    while(queries--){
        int root, u, v;
        cin >> root >> u >> v;

        int a = solver.lca(u, v);
        int b = solver.lca(root, u);
        int c = solver.lca(root, v);

        if(a == b && b == c)
            cout << a << endl;
        else if(a == b)
            cout << c << endl;
        else if(a == c)
            cout << b << endl;
        else
            cout << a << endl;
    }

    return 0;
}
