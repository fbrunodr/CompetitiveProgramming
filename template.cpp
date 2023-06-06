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

template<typename T>
ostream& operator << (ostream& _os, const vec<T>& _v){
    for(int i = 0; i < _v.size() - 1; i++)
        _os << _v[i] << ' ';
    _os << _v.back();
    return _os;
}

template<typename T>
istream& operator >> (istream& _is, vec<T>& _v){
    for(auto& _v_i : _v)
        cin >> _v_i;
    return _is;
}

// Code below

void solve(){
    int n; cin >> n;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases = 1;
    // cin >> testCases;

    while(testCases--)
        solve();

    return 0;
}
