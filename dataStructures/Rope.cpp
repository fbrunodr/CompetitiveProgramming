#include<ext/rope>                         // pbds


// Supports insert / erase at any position in O(log n)
template<typename T>
using Rope = __gnu_cxx::rope<T>;
