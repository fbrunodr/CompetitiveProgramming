// see https://codeforces.com/contest/271/problem/D

#include "../algorithms/RollingHash.cpp"

int32_t main(){
    ios_base::sync_with_stdio(false);

    setRollingHashPowers(2000);

    string s; cin >> s;

    vector<bool> good(26, false);
    string goodMask; cin >> goodMask;
    for(int i = 0; i < 26; i++)
        if(goodMask[i] - '0')
            good[i] = true;

    int n = s.size();
    using vi = vector<int>;
    vi a(n, 0);
    for(int i = 0; i < n; i++){
        if(i != 0) a[i] += a[i-1];
        if(!good[s[i] - 'a']) a[i]++;
    }


    int k; cin >> k;

    RollingHash hasher(s);
    unordered_set<bitset<128>> hashes;

    int ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++){
            int nBad = a[j];
            if(i != 0) nBad -= a[i-1];
            if(nBad > k) continue;
            auto hash_ij = hasher.getHash(i, j);
            if(hashes.count(hash_ij)) continue;
            hashes.insert(hash_ij);
            ans++;
        }

    cout << ans << endl;

    return 0;
}
