#include<bits/stdc++.h>
using namespace std;
template<typename T>
using vec = vector<T>;
using vi = vec<int>;
using ii = pair<int, int>;
using vii = vec<ii>;
using iii = tuple<int, int, int>;


// Runs in N * sqrt(N) * O(max(add, remove))
template<typename D, typename T>
vec<T> SnakeSolveQueries(
    vii queries,
    function<void(D&,int)> add,
    function<void(D&,int)> remove,
    D& initialVal,
    function<T(D&)> save_answer
){
    int n = queries.size();
    int sqrt_n = max((int)ceil(sqrt(n)), 10);
    vec<iii> queries_w_order(n);
    for(int i = 0; i < n; i++)
        queries_w_order[i] = {queries[i].first, queries[i].second, i};

    auto get_key = [&sqrt_n](iii query_with_order){
        auto [l, r, i] = query_with_order;
        int col = l / sqrt_n;
        int row = r / sqrt_n;
        if(row % 2 == 0)
            return make_tuple(row * sqrt_n + col + 1, l, r);
        return make_tuple(row * sqrt_n + sqrt_n - col, l, r);
    };

    sort(queries_w_order.begin(), queries_w_order.end(), [&get_key](iii a, iii b){
        return get_key(a) < get_key(b);
    });

    int begin = 0, end = 0;
    vec<T> ans(n);
    D& curr = initialVal;
    for(auto [l, r, i] : queries_w_order){
        bool finished = false;
        while (!finished){
            if(begin > l){
                begin--;
                add(curr, begin);
            }
            else if(end <= r){
                add(curr, end);
                end++;
            }
            else if(begin < l){
                remove(curr, begin);
                begin++;
            }
            else if(end > r+1){
                end--;
                remove(curr, end);
            }
            else if(begin == l && end == r+1){
                ans[i] = save_answer(curr);
                finished = true;
            }
        }
    }

    return ans;
}