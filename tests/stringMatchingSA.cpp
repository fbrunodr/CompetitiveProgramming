// see https://open.kattis.com/problems/stringmatching

// The point here is testing the Suffix Array implementation, rather than
// solving the question optimally. You can solve the question in O(n+m)
// using prefix function (or KMP match)

#include "../algorithms/stringUtils.cpp"

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string text, pattern;

    while(getline(cin, pattern)){
        getline(cin, text);
        vi sa = getSuffixArray(text);

        int n = text.size();
        int m = pattern.size();
        int lo = 0, hi = n - 1; 	// range = [0..n-1]
        while (lo < hi){						  // find lower bound
            int mid = (lo + hi) / 2;			  // this is round down
            int res = strncmp(text.c_str() + sa[mid], pattern.c_str(), m); // P in suffix SA[mid]?
            (res >= 0) ? hi = mid : lo = mid + 1; // notice the >= sign
        }
        if (strncmp(text.c_str() + sa[lo], pattern.c_str(), m) != 0){
            cout << '\n';
            continue;
        }
        int low = lo;

        hi = n - 1;
        while (lo < hi){  // now find upper bound
            int mid = (lo + hi) / 2;
            int res = strncmp(text.c_str() + sa[mid], pattern.c_str(), m);
            (res > 0) ? hi = mid : lo = mid + 1;  // notice the > sign
        }
        if (strncmp(text.c_str() + sa[hi], pattern.c_str(), m) != 0)
            --hi;  // special case
        int high = hi;

        vi ans;
        for(int i = low; i <= high; i++)
            ans.push_back(sa[i]);

        sort(ans.begin(), ans.end());

        for(auto& val : ans)
            cout << val << ' ';

        cout << '\n';
    }

    return 0;
}
