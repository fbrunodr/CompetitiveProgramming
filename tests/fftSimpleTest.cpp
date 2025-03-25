#include "../algorithms/fastPolynomialMultiplication.cpp"

vi normalMultiply(vi a, vi b){
    int n = a.size();
    int m = b.size();
    vi c(n+m-1, 0);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            c[i+j] += a[i] * b[j];

    return c;
}

vi normalUsualConvolution(vi a, vi b){
    int n = a.size();
    int m = b.size();
    assert(m <= n && "Convolution size fail");
    vi c(n-m+1, 0);
    for(int i = 0; i < c.size(); i++)
        for(int j = 0; j < m; j++)
            c[i] += a[i+j] * b[j];
    return c;
}

int32_t main(){
    // x^6 + x^2 + 2x + 1
    vi a{1, 2, 1, 0, 0, 0, 1};

    // 2x^5 - x^3 + x^2 + 3
    vi b{3, 0, 1, -1, 0, 2};

    assert(
        normalMultiply(a, b) == multiply(a, b)
    );

    vi c = normalUsualConvolution(a, b);
    vi d = usualConvolution(a,b);

    assert(
        normalUsualConvolution(a, b) == usualConvolution(a, b)
    );

    return 0;
}
