// See https://codeforces.com/problemset/problem/380/C

#include "../dataStructures/FrozenSegTree.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;

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

    FrozenSegTree<iii> segTree(A, mergeIntervals);

    using ii = pair<int, int>;
    using vii = vector<ii>;

    int nQueries; cin >> nQueries;

    while(nQueries--){
        int i, j; cin >> i >> j;
        i--; j--;
        auto [matches, open, closed] = segTree.RQ(i, j);
        cout << 2*matches << '\n';
    }

    return 0;
}
