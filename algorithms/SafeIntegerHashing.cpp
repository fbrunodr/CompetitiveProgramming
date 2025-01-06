// see https://codeforces.com/contest/2057/problem/B

#include<bits/stdc++.h>
using namespace std;
template<typename T>
using vec = vector<T>;
using vi = vec<int>;
using ii = pair<int, int>;
using vii = vec<ii>;
using i64 = long long;
using vi64 = vec<i64>;
using iii = tuple<int, int, int>;
using str = string;
template<typename Key, typename Value>
using hash_map = unordered_map<Key, Value>;
template<typename T>
using hash_set = unordered_set<T>;
template<typename T>
using min_heap = priority_queue<T, vec<T>, greater<T>>;
template<typename T>
using max_heap = priority_queue<T>;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve(){
    int n, k; cin >> n >> k;
    vi a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    unordered_map<int, int, custom_hash> freq;
    for(int i = 0; i < n; i++)
        freq[a[i]]++;

    vi apps;
    for(auto [val, app] : freq)
        apps.push_back(app);
    sort(apps.begin(), apps.end());
    reverse(apps.begin(), apps.end());

    while(k && !apps.empty()){
        if(apps.size() > 1 && apps.back() <= k){
            k -= apps.back();
            apps.front() += apps.back();
            apps.pop_back();
        }
        else
            break;
    }

    cout << apps.size() << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases = 1;
    cin >> testCases;

    while(testCases--)
        solve();

    return 0;
}
