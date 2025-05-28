#ifndef FBRUNODR_COUNT_INVERSIONS
#define FBRUNODR_COUNT_INVERSIONS

#include "../header.hpp"

template<typename T, typename cmp = std::less<T>>
int countAndMerge(vec<T>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;

    vec<T> left(n1), right(n2);
    for (int i = 0; i < n1; i++)
        left[i] = arr[i + l];
    for (int j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    int res = 0;
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if(cmp{}(right[j], left[i])){
            arr[k++] = right[j++];
            res += (n1 - i);
        }
        else
            arr[k++] = left[i++];
    }

    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];

    return res;
}

template<typename T, typename cmp = std::less<T>>
int countInversions(vec<T>& arr, int l, int r){
    const int THRESHOLD = 16;
    int res = 0;
    if(r - l + 1 <= THRESHOLD){
        for(int i = l; i <= r; i++)
            for(int j = i + 1; j <= r; j++)
                if(cmp{}(arr[j], arr[i]))
                    res++;
        sort(arr.begin() + l, arr.begin() + r + 1, cmp{});
        return res;
    }
    if (l < r) {
        int m = (r + l) / 2;
        res += countInversions<T, cmp>(arr, l, m);
        res += countInversions<T, cmp>(arr, m + 1, r);
        res += countAndMerge<T, cmp>(arr, l, m, r);
    }
    return res;
}

template<typename T, typename cmp = std::less<T>>
int countInversions(vec<T> arr) {
    int n = arr.size();
    return countInversions<T, cmp>(arr, 0, n-1);
}

#endif
