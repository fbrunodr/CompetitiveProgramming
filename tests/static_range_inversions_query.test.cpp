#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include "../header.hpp"
#include "../algorithms/countInversions.hpp"
#include "../dataStructures/SegTree.hpp"

int solve(){
    fastIO();
    int n, q; cin >> n >> q;
    vi a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];

    struct Data{
        vi seq;
        int inversions;
        Data(){}
    };

    vec<Data> data(n);
    for(int i = 0; i < n; i++)
        data[i].seq = {a[i]};

    PointUpdateSegTree<Data> segTree(data, [](Data x, Data y){
        Data z;
        z.seq = x.seq;
        z.seq.insert(z.seq.end(), y.seq.begin(), y.seq.end());
        z.inversions = x.inversions + y.inversions + countAndMerge(z.seq, 0, x.seq.size() - 1, z.seq.size() - 1);
        return z;
    });

    for(int i = 0; i < q; i++){
        int l, r; cin >> l >> r;
        if(r - l + 1 <= 32)
            cout << countInversions(vi(a.begin() + l, a.begin() + r)) << '\n';
        else
            cout << segTree.RQ(l, r-1).inversions << '\n';
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
