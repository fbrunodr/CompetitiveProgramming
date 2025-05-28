#define PROBLEM "https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification"

#include "../header.hpp"
#include "../algorithms/treeIsomorphism.hpp"

int solve(){
    fastIO();
    setRollingHashPowers(5e5);
    int n; cin >> n;
    vec<vi> al(n);
    for(int i = 1; i < n; i++){
        int p_i; cin >> p_i;
        al[p_i].push_back(i);
        al[i].push_back(p_i);
    }
    vec<SubtreeHashInfo> hashes = subtreeHashes(al, 0);
    hash_map<bitset<128>, int> hashToIndex;
    for(int i = 0; i < n; i++){
        if(hashToIndex.find(hashes[i].hashed) == hashToIndex.end())
            hashToIndex[hashes[i].hashed] = hashToIndex.size();
    }

    cout << hashToIndex.size() << '\n';
    for(int i = 0; i < n; i++)
        cout << hashToIndex[hashes[i].hashed] << ' ';
    cout << '\n';
    return 0;
}

static void* run(void*){
    exit(solve());
}

int32_t main(){
    const size_t STACK_SIZE = 512ull * 1024 * 1024;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, STACK_SIZE);

    pthread_t thread;
    pthread_create(&thread, &attr, &run, nullptr);
    pthread_join(thread, nullptr);

    return 0;
}

#include "../footer.hpp"
