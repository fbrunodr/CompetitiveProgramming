#ifndef FBRUNODR_FAST_OFFLINE_QUERIES
#define FBRUNODR_FAST_OFFLINE_QUERIES

#include "../header.hpp"

const int block_size = 512;

template<typename D, typename T>
vec<T> MoSolveQueries(
    vii queries,
    function<void(D&,int)> add,
    function<void(D&,int)> remove,
    D& initialVal,
    function<T(D&)> save_answer
){
    using i4 = tuple<int,int,int,int>;
    int n = queries.size();
    vec<i4> mo_queries(n);
    for(int i = 0; i < n; i++)
        mo_queries[i] = {
            queries[i].first/block_size,
            queries[i].second,
            queries[i].first,
            i
        };

    sort(mo_queries.begin(), mo_queries.end(), [](i4 x, i4 y){
        int block_x = get<0>(x);
        int block_y = get<0>(y);
        if(block_x == block_y)
            return block_x & 1 ? get<1>(x) < get<1>(y) : get<1>(x) > get<1>(y);
        return block_x < block_y;
    });

    int begin = 0, end = 0;
    vec<T> ans(n);
    D& curr = initialVal;
    for(auto [block, r, l, i] : mo_queries){
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

#endif
