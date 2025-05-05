#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../dataStructures/AVLtree.hpp"

int solve(){
    fastIO();
    int n, q; cin >> n >> q;
    vi a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];

    AVL<int,int> bst(std::less<int>(), [](_Tree_Vertex<int,int>* node){return;});
    for(int i = 0; i < n; i++)
        bst.insert(a[i]);

    while(q--){
        int type, x; cin >> type >> x;

        if(type == 0)
            bst.insert(x);
        else if(type == 1)
            bst.erase(x);
        else if(type == 2){
            if(bst.size() < x)
                cout << "-1\n";
            else
                cout << bst.getKthNode(x-1)->key << '\n';
        }
        else if(type == 3){
            auto [left, right] = bst.split(x + 1);
            cout << left.size() << '\n';
            bst = bst.join(left, right);
        }
        else if(type == 4){
            auto [left, right] = bst.split(x + 1);
            if(left.size() == 0)
                cout << "-1\n";
            else
                cout << left.getMaxNode()->key << '\n';
            bst = bst.join(left, right);
        }
        else if(type == 5){
            auto [left, right] = bst.split(x);
            if(right.size() == 0)
                cout << "-1\n";
            else
                cout << right.getMinNode()->key << '\n';
            bst = bst.join(left, right);
        }
    }

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
