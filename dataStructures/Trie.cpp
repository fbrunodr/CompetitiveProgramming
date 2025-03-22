#include<bits/stdc++.h>
using namespace std;

struct TrieNode{
    // add info here
    TrieNode* children[26];
    // if you need to save memory:
    // map<char, TrieNode*> children;

    TrieNode(){
        memset(children, 0, sizeof(children));
        // initialize info here
    }
};

TrieNode* addChar(TrieNode* u, char c){
    int idx = c - 'a';
    if(!u->children[idx])
        u->children[idx] = new TrieNode();
    return u->children[idx];
}

TrieNode* addString(TrieNode* u, string& s){
    for(auto& c : s)
        u = addChar(u, c);
    return u;
}


TrieNode* root;
