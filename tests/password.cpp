// see https://codeforces.com/problemset/problem/126/B

#include "../algorithms/stringUtils.cpp"

int main(){
    string s; cin >> s;

    vi z = zFunction(s);

    int maxSize = 0;

    for(int i = 1; i < s.size(); i++){
        if( (i+z[i] == s.size()) && (z[i] <= maxSize) ){
            cout << s.substr(i, z[i]) << endl;
            return 0;
        }
        maxSize = max(maxSize, z[i]);
    }

    cout << "Just a legend" << endl;

    return 0;
}
