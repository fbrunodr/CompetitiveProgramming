#ifndef FBRUNODR_FAST_POLYNOMIAL_MULTIPLICATION
#define FBRUNODR_FAST_POLYNOMIAL_MULTIPLICATION

#include "../header.hpp"

// YOU SURE IT IS FFT?

void fft(vec<cd> & a, bool invert){
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++){
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1){
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++){
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert){
        for (cd & x : a)
            x /= n;
    }
}


vi multiply(vi p1, vi p2){
    int n = 1;  // n needs to be a power of 2
    while (n < p1.size() + p2.size() - 1)
        n <<= 1;
        
    vec<cd> A(p1.begin(), p1.end());
    vec<cd> B(p2.begin(), p2.end());
    A.resize(n);
    B.resize(n); // prepare A and B for FFT calls

    fft(A, false);
    fft(B, false);

    vec<cd> C(n);
    for (int k = 0; k < n; ++k)
        C[k] = A[k] * B[k]; // perform the multiplication

    fft(C, true);

    vi res;
    for (auto &p : C)
        res.push_back(round(p.real()));    // prepare output

    res.resize(p1.size() + p2.size() - 1); // resize to original degree

    return res;
}


vi usualConvolution(vi a, vi b){
    reverse(b.begin(), b.end());
    vi c = multiply(a, b);
    vi ans;
    int n = a.size();
    int m = b.size();
    for(int i = m-1; i < n; i++)
        ans.push_back(c[i]);
    return ans;
}


#endif
