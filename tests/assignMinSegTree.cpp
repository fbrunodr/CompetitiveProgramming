#include "../dataStructures/LazySegTree.cpp"

int main(){
    using i64 = long long;
    using vi64 = vector<i64>;

    vi64 A{13, 4, 8, 11, 18, 12, 17, 15, 6, 7, 10, 3, 5, 19, 2, 14, 20, 1, 9, 16};

    auto mergeNode = [](i64 a, i64 b){ return min(a,b); };
    auto nodeUpdate = [](i64& a, i64 update, int L, int R){ a = update; };
    auto lazyUpdate = [](i64& a, i64 update){ a = update; };

    LazySegTree<i64, i64> segTree(A, mergeNode, nodeUpdate, lazyUpdate, LONG_LONG_MAX, LONG_LONG_MAX);

    cout << segTree.RQ(0, 10) << endl; // 4
    cout << segTree.RQ(5, 15) << endl; // 2
    segTree.rangeUpdate(11, 19, 10);
    cout << segTree.RQ(5, 15) << endl; // 6

    return 0;
}
