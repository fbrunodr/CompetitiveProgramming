#include "../algorithms/LCA.cpp"

int32_t main(){
    using vi = vector<int>;
    vector<vi> children(10);
    children[0] = {1, 7};
    children[1] = {2, 3, 6};
    children[3] = {4, 5};
    children[7] = {8, 9};

    SegLCA tree(children, 0);

    cout << tree.lca(6, 4) << endl;
    cout << tree.lca(8, 9) << endl;
    cout << tree.lca(2, 7) << endl;

    return 0;
}
