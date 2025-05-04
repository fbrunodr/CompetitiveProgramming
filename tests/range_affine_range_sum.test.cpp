#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "../dataStructures/SegTree.hpp"

const int MOD = 998244353;

int solve(){
    fastIO();

    int n, q; cin >> n >> q;

    vi a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];

    auto merge = [&](int x, int y){
        return (x + y) % MOD;
    };
    auto update = [&](int& x, ii up, int l, int r){
        x = (x * up.first + up.second * (r - l + 1)) % MOD;
    };
    // a -> ax + y -> (ax + y) * z + w = a * xz + y*z + w
    auto compose = [&](ii& up1, ii up2){
        up1 = make_pair((up1.first * up2.first) % MOD, (up2.first * up1.second + up2.second) % MOD);
    };

    LazySegTree<int, ii> lazySegTree(a, merge, update, compose);

    while(q--){
        int type; cin >> type;
        if(type == 0){
            int l, r, b, c; cin >> l >> r >> b >> c;
            r--;
            lazySegTree.rangeUpdate(l, r, make_pair(b, c));
        }
        else if(type == 1){
            int l, r; cin >> l >> r;
            r--;
            cout << lazySegTree.RQ(l, r) << '\n';
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
