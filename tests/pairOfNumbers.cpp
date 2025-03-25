// see https://codeforces.com/problemset/problem/359/D
// latest submission: https://codeforces.com/contest/359/submission/312375887

#include "../algorithms/firstElementToLeft.hpp"

int32_t main(){
    fastIO();
    int n; cin >> n;

    vi a(n);
    for(auto& a_i : a)
        cin >> a_i;

    // opposite of not divisible is divisible
    // divisible is transitive, that is:
    // a|b and b|c => a|c
    // so we can use next element to left on not divisible
    auto notDivisible = [](int next, int curr){
        return next%curr != 0;
    };

    vi nextLeft = firstElementToLeft<int>(a, notDivisible);
    vi nextRight = firstElementToRight<int>(a, notDivisible);

    int maxDist = -1;
    for(int i = 0; i < n; i++)
        maxDist = max(maxDist, (nextRight[i]-1) - (nextLeft[i]+1));

    set<int> ans;
    for(int i = 0; i < n; i++)
        if((nextRight[i]-1) - (nextLeft[i]+1) == maxDist)
            ans.insert(nextLeft[i]+2);

    cout << ans.size() << ' ' << maxDist << '\n';
    for(auto& i : ans)
        cout << i << ' ';
    cout << '\n';

    return 0;
}
