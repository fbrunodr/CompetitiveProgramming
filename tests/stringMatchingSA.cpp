// see https://open.kattis.com/problems/stringmatching

// The point here is testing the Suffix Array implementation, rather than
// solving the question optimally. You can solve the question in O(n+m)
// using prefix function (or KMP match)

#include "../dataStructures/SuffixArray.cpp"

int main(){
    ios_base::sync_with_stdio(false);

    string text, pattern;

    while(getline(cin, pattern)){
        getline(cin, text);
        SuffixArray suffixArray(text);
        auto [low, high] = suffixArray.stringMatching(pattern);
        if(low == -1){
            cout << endl;
            continue;
        }

        using vi = vector<int>;
        vi ans;
        for(int i = low; i <= high; i++)
            ans.push_back(suffixArray.SA[i]);

        sort(ans.begin(), ans.end());

        for(auto& val : ans)
            cout << val << ' ';

        cout << endl;
    }

    return 0;
}
