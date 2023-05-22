#include<bits/stdc++.h>
using namespace std;

struct TrieNode{
    // add info here
    TrieNode* children[26];

    TrieNode(){
        for(int i = 0; i < 26; i++)
            children[i] = nullptr;
        // initialize info here
    }

    TrieNode* addChar(char c){
        int idx = c - 'a';
        if(children[idx] == nullptr)
            children[idx] = new TrieNode();
        return children[idx];
    }

    void addString(string& s){
        auto it = this;
        for(auto& c : s)
            it = it->addChar(c);
    }
};

TrieNode* root;
