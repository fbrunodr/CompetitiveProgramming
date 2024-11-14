#include<bits/stdc++.h>
using namespace std;
template<typename T>
using vec = vector<T>;
using i64 = long long;

template<typename T>
i64 countAndMerge(vec<T>& arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;

    vec<T> left(n1), right(n2);
    for (int i = 0; i < n1; i++)
        left[i] = arr[i + l];
    for (int j = 0; j < n2; j++)
        right[j] = arr[m + 1 + j];

    i64 res = 0;
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else {
            arr[k++] = right[j++];
            res += (n1 - i);
        }
    }

    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];

    return res;
}

template<typename T>
i64 countInv(vec<T>& arr, int l, int r){
    i64 res = 0;
    if (l < r) {
        int m = (r + l) / 2;
        res += countInv(arr, l, m);
        res += countInv(arr, m + 1, r);
        res += countAndMerge(arr, l, m, r);
    }
    return res;
}

template<typename T>
i64 inversionCount(vec<T> &arr) {
      int n = arr.size();
      return countInv(arr, 0, n-1);
}