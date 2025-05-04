#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "../dataStructures/OrderStatisticsTree.hpp"
#include "../algorithms/binarySearch.hpp"

int solve(){
    fastIO();
    vi numbers;

    int n, q; cin >> n >> q;
    vi a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        numbers.push_back(a[i]);
    }

    vii queries(q);
    for(int i = 0; i < q; i++){
        cin >> queries[i].first >> queries[i].second;
        numbers.push_back(queries[i].second);
    }

    numbers.push_back(-1);
    numbers.push_back(-2);
    uniqueSorted(numbers);
    f<int(int)> relativeVal = [&](int x){
        return std::lower_bound(numbers.begin(), numbers.end(), x) - numbers.begin();
    };

    FenwickTreeOST ost(numbers.size() + 5);
    for(int a_i : a)
        ost.insert(relativeVal(a_i));
    for(auto [type, x] : queries){
        if(type == 0)
            ost.insert(relativeVal(x));
        else if(type == 1)
            ost.remove(relativeVal(x));
        else if(type == 2){
            if(ost.size() < x)
                cout << "-1\n";
            else
                cout << numbers[ost.findByOrder(x-1)] << '\n';
        }
        else if(type == 3)
            cout << ost.orderOfKey(relativeVal(x)+1) << '\n';
        else if(type == 4){
            x = relativeVal(x);
            if(ost.has(x))
                cout << numbers[x] << '\n';
            else if(ost.orderOfKey(x) == 0)
                cout << "-1\n";
            else
                cout <<  numbers[lastTrue(1, x, [&](int i){
                    return ost.orderOfKey(i) < ost.orderOfKey(x);
                })] << '\n';
        }
        else if(type == 5){
            x = relativeVal(x);
            if(ost.has(x))
                cout << numbers[x] << '\n';
            else if(ost.orderOfKey(x) == ost.size())
                cout << "-1\n";
            else
            cout <<  numbers[lastTrue(x, numbers.size(), [&](int i){
                return ost.orderOfKey(i) == ost.orderOfKey(x);
            })] << '\n';
        }
        cout.flush();
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
