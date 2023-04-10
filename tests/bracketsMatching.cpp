// See https://codeforces.com/problemset/problem/380/C

#include "../dataStructures/FrozenSegTree.cpp"

int main(){
    string s = "())(())(())(";

    using iii = tuple<int, int, int>;
    using viii = vector<iii>;

    viii A;

    for(auto c : s)
        if(c == '(')
            A.emplace_back(0,1,0);
        else if(c == ')')
            A.emplace_back(0,0,1);

    auto mergeIntervals = [](iii left, iii right){
        auto [leftMatches, leftOpen, leftClosed] = left;
        auto [rightMatches, rightOpen, rightClosed] = right;
        int newMatches = min(leftOpen, rightClosed);
        return make_tuple(
            leftMatches + rightMatches + newMatches,
            leftOpen + rightOpen - newMatches,
            leftClosed + rightClosed - newMatches
        );
    };

    const iii ERROR{0, 0, 0};
    FrozenSegTree<iii> segTree(A, mergeIntervals, ERROR);

    using ii = pair<int, int>;
    using vii = vector<ii>;

    vii queries{ {1, 1}, {2, 3}, {1, 2}, {1, 12}, {8, 12}, {5, 11}, {2, 10} };
    for(auto [i, j] : queries){
        i--; j--;
        auto [matches, open, closed] = segTree.RQ(i, j);
        cout << 2*matches << endl;
    }
    

    return 0;
}
