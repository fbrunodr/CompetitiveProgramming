// see https://open.kattis.com/problems/stringmatching

#include "../algorithms/stringUtils.cpp"

int main(){
    string pattern, text;

    while(getline(cin, pattern)){
        getline(cin, text);
        char separator = 5;
        string aux = pattern;
        aux.push_back(separator);
        aux += text;
        auto pi = prefixFunction(aux);
        for(int i = pattern.size() + 1; i < pi.size(); i++)
            if(pi[i] == pattern.size())
                cout << i - 2*pattern.size() << ' ';
        cout << endl;
    }

    return 0;
}
