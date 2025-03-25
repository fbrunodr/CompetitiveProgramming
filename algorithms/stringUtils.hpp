#ifndef FBRUNODR_STRING_UTILS
#define FBRUNODR_STRING_UTILS

#include "../header.hpp"

// Doing this way so it works for both string and vi
template<typename T>
vi prefixFunction(const T& s) {
    int n = (int)s.size();
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

template<typename T>
vi zFunction(const T& s) {
    int n = (int) s.length();
    vi z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

template<typename T, typename U>
vi matching_positions(const T& text, const T& pattern, U separator){
    T aux = pattern;
    aux.push_back(separator);
    aux.insert(aux.end(), text.begin(), text.end());
    vi pi = prefixFunction(aux);
    vi ans;
    for(int i = pattern.size(); i < aux.size(); i++)
        if(pi[i] == pattern.size())
            ans.push_back(i - 2 * pattern.size());
    return ans;
}

vi getSuffixArray(string s) {
    s.push_back(5);
    int n = s.size(), N = max(n, (int)260);
    vi sa(n), ra(n);
    for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];

    for(int k = 0; k < n; k ? k *= 2 : k++) {
        vi nsa(sa), nra(n), cnt(N);

        for(int i = 0; i < n; i++) nsa[i] = (nsa[i]-k+n)%n, cnt[ra[i]]++;
        for(int i = 1; i < N; i++) cnt[i] += cnt[i-1];
        for(int i = n-1; i+1; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];

        for(int i = 1, r = 0; i < n; i++)
            nra[sa[i]] = r += ra[sa[i]] != ra[sa[i-1]] or ra[(sa[i]+k)%n] != ra[(sa[i-1]+k)%n];
        ra = nra;
        if (ra[sa[n-1]] == n-1) break;
    }
    return vi(sa.begin()+1, sa.end());
}

vi kasai(const string& s, const vi& sa) {
    int n = s.size(), k = 0;
    vi ra(n), lcp(n);
    for (int i = 0; i < n; i++) ra[sa[i]] = i;

    for (int i = 0; i < n; i++, k -= !!k) {
        if (ra[i] == n-1) { k = 0; continue; }
        int j = sa[ra[i]+1];
        while (i+k < n and j+k < n and s[i+k] == s[j+k]) k++;
        lcp[ra[i]] = k;
    }
    return lcp;
}


#endif
