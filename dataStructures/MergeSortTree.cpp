#include<bits/stdc++.h>
using namespace std;
template<typename T>
using vec = vector<T>;


template<typename T>
class MergeSortTree{
    using vT = vec<T>;

    int n;
    vT A;
    vec<vT> mergeSort;
    function<bool(T,T)> comparator;

    int l(int p) { return p << 1; }        // go to left child
    int r(int p) { return (p << 1) + 1; }  // go to right child

    // takes O(n*log(n)) memory, instead of the usual O(n) memory of a segtree
    // as every one of the O(log(n)) layers has a copy of every A[i]
    void build(int p, int L, int R){
        if(L == R)
            mergeSort[p] = vT{A[L]};
        else{
            int m = (L + R) / 2;
            build(l(p), L, m);
            build(r(p), m+1, R);

            vT& leftChild = mergeSort[l(p)];
            vT& rightChild = mergeSort[r(p)];

            mergeSort[p].reserve(leftChild.size() + rightChild.size());

            int itr_l = 0, itr_r = 0;
            while(itr_l < leftChild.size() && itr_r < rightChild.size()){
                if(comparator(leftChild[itr_l], rightChild[itr_r])){
                    mergeSort[p].push_back(leftChild[itr_l]);
                    itr_l++;
                }
                else{
                    mergeSort[p].push_back(rightChild[itr_r]);
                    itr_r++;
                }
            }
            while(itr_l < leftChild.size()){
                mergeSort[p].push_back(leftChild[itr_l]);
                itr_l++;
            }
            while(itr_r < rightChild.size()){
                mergeSort[p].push_back(rightChild[itr_r]);
                itr_r++;
            }
        }
    }

    vec<vT*> RQ(int p, int L, int R, int i, int j){
        if(i > j)
            return vec<vT*>();
        if ((i <= L) && (R <= j))
            return vec<vT*>{&mergeSort[p]};
        int m = (L + R) / 2;
        auto left = RQ(l(p), L, m, i, min(j, m));
        auto right = RQ(r(p), m + 1, R, max(m + 1, i), j);
        left.insert(left.end(), right.begin(), right.end());
        return left;
    }

    public:
    MergeSortTree(vT& _A, function<bool(T,T)> _comparator) : A(_A), comparator(_comparator) {
        n = A.size();
        mergeSort = vec<vT>(4*n);
        build(1, 0, n - 1);
    }

    // return O(log(n)) pointers to ordered intervals
    // the pointers are never nullptr
    vec<vT*> RQ(int i, int j){
        if(i > j)
            exit(2948);
        return RQ(1, 0, n-1, i, j);
    }
};
