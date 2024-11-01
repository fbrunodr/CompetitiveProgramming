#include<bits/stdc++.h>
using namespace std;
template<typename T>
using vec = vector<T>;
using vi = vec<int>;
using ii = pair<int, int>;
using vii = vec<ii>;
using i64 = long long;
using iii = tuple<int, int, int>;

// see https://en.wikipedia.org/wiki/Z-order_curve
i64 interleave(int x, int y) {
    i64 z = 0;
    for (int i = 0; i < 32; ++i) {
        z |= ((x >> i) & 1ULL) << (2 * i);
        z |= ((y >> i) & 1ULL) << (2 * i + 1);
    }
    return z;
}


template<typename D, typename T>
vec<T> ZOrderSolveQueries(
    vii queries,
    function<void(D&,int)> add,
    function<void(D&,int)> remove,
    D& initialVal,
    function<T(D&)> save_answer
){
    using i64iii = tuple<i64,int,int,int>;
    int n = queries.size();
    vec<i64iii> morton_query_order(n);
    for(int i = 0; i < n; i++)
        morton_query_order[i] = {
            interleave(queries[i].first, queries[i].second),
            queries[i].first,
            queries[i].second,
            i
        };

    sort(morton_query_order.begin(), morton_query_order.end());

    int begin = 0, end = 0;
    vec<T> ans(n);
    D& curr = initialVal;
    for(auto [morton, l, r, i] : morton_query_order){
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