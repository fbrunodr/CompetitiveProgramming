#ifndef FBRUNODR_TREE_ISOMORPHISM
#define FBRUNODR_TREE_ISOMORPHISM

#include "subtreeCenter.hpp"
#include "RollingHash.hpp"

const std::bitset<128> openHash = []{
    std::bitset<128> bs;
    bs.set(0);
    bs.set(32);
    bs.set(64);
    bs.set(96);
    return bs;
}();
const std::bitset<128> closedHash = openHash << 1;


struct SubtreeHashInfo{
    int size;
    bitset<128> hashed;
    SubtreeHashInfo(){}
    SubtreeHashInfo(int _size, bitset<128> h) : size(_size), hashed(h) {}

    bool operator < (SubtreeHashInfo other) const {
        constexpr bitset<128> lowest_32(0xFFFFFFFF);
        iii thisKey{
            this->size,
            (this->hashed & lowest_32).to_ullong(),
            ((this->hashed >> 64) & lowest_32).to_ullong(),
        };

        iii otherKey{
            other.size,
            (other.hashed & lowest_32).to_ullong(),
            ((other.hashed >> 64) & lowest_32).to_ullong(),
        };

        return thisKey < otherKey;
    }

    bool operator == (SubtreeHashInfo other) const {
        return (this->size == other.size) && (this->hashed == other.hashed);
    }
};

// SubtreeHashInfo subtreeHash


vec<SubtreeHashInfo> subtreeHashes(vec<vi>& al, int root){
    int n = al.size();
    vec<SubtreeHashInfo> hashes(n);
    f<void(int,int)> dfs = [&](int u, int p){
        if(al[u].empty())
            hashes[u] = SubtreeHashInfo(2, sum(openHash, moveRight(closedHash, 1)));
        if(al[u].size() == 1 && al[u][0] == p)
            hashes[u] = SubtreeHashInfo(2, sum(openHash, moveRight(closedHash, 1)));

        vec<SubtreeHashInfo> children;
        for(int v : al[u]){
            if(v == p) continue;
            dfs(v, u);
            children.push_back(hashes[v]);
        }

        sort(children.begin(), children.end());
        bitset<128> h = openHash;
        int currSize = 1;
        for(auto [size, childHash] : children){
            h = sum(h, moveRight(childHash, currSize));
            currSize += size;
        }
        h = sum(h, moveRight(closedHash, currSize++));
        hashes[u] = SubtreeHashInfo(currSize, h);
    };
    dfs(root, -1);
    return hashes;
}

bool isomorphicTrees(vec<vi>& al1, vec<vi>& al2, int start1 = 0, int start2 = 0){
    int n1 = 0, n2 = 0;
    // pro tip: there are O(sqrt(n)) distinct sizes in a tree of size n
    hash_map<int, int> sizes1, sizes2;

    f<void(int,int)> dfs1 = [&](int u, int p){
        n1++;
        sizes1[al1[u].size()]++;
        for(int v : al1[u]){
            if(v == p) continue;
            dfs1(v, u);
        }
    };

    f<void(int,int)> dfs2 = [&](int u, int p){
        n2++;
        sizes2[al2[u].size()]++;
        for(int v : al2[u]){
            if(v == p) continue;
            dfs2(v, u);
        }
    };

    dfs1(start1, -1);
    dfs2(start2, -1);

    if(n1 != n2)
        return false;

    if(n1 <= 2)
        return true;

    if(sizes1 != sizes2)
        return false;

    auto c1 = subtreeCenter(al1, start1, start1);
    auto c2 = subtreeCenter(al2, start2, start2);

    if(c1.size() != c2.size())
        return false;

    vec<SubtreeHashInfo> hashes1;
    for(int c : c1)
        hashes1.push_back(subtreeHashes(al1, c)[c]);

    vec<SubtreeHashInfo> hashes2;
    for(int c : c2)
        hashes2.push_back(subtreeHashes(al2, c)[c]);

    if(hashes1.front() != hashes2.front())
        reverse(hashes2.begin(), hashes2.end());

    for(int i = 0; i < hashes1.size(); i++)
        if(hashes1[i] != hashes2[i])
            return false;
    return true;
}

#endif
