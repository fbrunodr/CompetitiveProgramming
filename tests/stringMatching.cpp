// see https://open.kattis.com/problems/stringmatching
// latest submission: https://open.kattis.com/submissions/16969533

#include "../algorithms/stringUtils.hpp"

int32_t main(){
    string pattern, text;

    while(getline(cin, pattern)){
        getline(cin, text);
        for(int position : matching_positions(text, pattern, (char)5))
            cout << position << ' ';
        cout << endl;
    }

    return 0;
}
