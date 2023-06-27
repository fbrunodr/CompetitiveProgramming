// see https://codeforces.com/problemset/problem/432/D

#include "../algorithms/stringUtils.cpp"

int main(){
    using ii = pair<int, int>;
    using vii = vector<ii>;

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s; cin >> s;
    int n = s.size();

    auto pi = prefixFunction(s);
    auto z = zFunction(s);
    z[0] = n;

    vi cumulative(n+5, 0);
    for(auto& z_i : z){
        cumulative[1]++;
        cumulative[z_i + 1]--;
    }

    for(int i = 1; i < cumulative.size(); i++)
        cumulative[i] += cumulative[i-1];

    vii ans;
    int i = n;
    while(i){
        ans.emplace_back(i, cumulative[i]);
        i = pi[i-1];
    }

    reverse(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for(auto& [l, count] : ans)
        cout << l << ' ' << count << '\n';

    return 0;
}
