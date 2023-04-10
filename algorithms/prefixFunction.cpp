#include<bits/stdc++.h>
using namespace std;
using vi = vector<int>;

vi prefixFunction(const string& s) {
    int n = (int)s.length();
    vi pi(n);
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}
