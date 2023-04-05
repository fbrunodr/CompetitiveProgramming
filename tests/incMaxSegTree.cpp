#include "../dataStructures/LazySegTree.cpp"

int main(){
    using i64 = long long;
    using vi64 = vector<i64>;

    vi64 A{13, 4, 8, 11, 18, 12, 17, 15, 6, 7, 10, 3, 5, 19, 2, 14, 20, 1, 9, 16};

    struct getMax { i64 operator()(i64 a, i64 b){ return max(a,b); } };

    LazySegTree<i64, getMax, plus<i64>> segTree(A, LONG_LONG_MIN, (i64)0);

    cout << segTree.RQ(0, 10) << endl;
    cout << segTree.RQ(5, 15) << endl;
    segTree.update(11, 19, -5);
    cout << segTree.RQ(5, 15) << endl;

    return 0;
}
