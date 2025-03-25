#ifndef FBRUNODR_HEADER
#define FBRUNODR_HEADER

#include <bits/stdc++.h>

#include <bits/extc++.h>                         // pbds

#define int long long int
static_assert(CHAR_BIT * sizeof(int) == 64);

#define LSOne(S) ((S) & -(S))

using std::vector;
using std::pair;
using std::set;
using std::multiset;
using std::map;
using std::string;
using std::tuple;
using std::max;
using std::min;
using std::swap;
using std::function;
using std::queue;
using std::stack;
using std::make_pair;
using std::make_tuple;
using std::tie;
using std::gcd;
using std::lcm;
using std::bitset;
using std::cin;
using std::cout;
using std::optional;
using std::nullopt;
using std::make_optional;
using std::endl;

template<typename T>
using vec = vector<T>;
using vi = vec<int>;
using ii = pair<int, int>;
using vii = vec<ii>;
using iii = tuple<int, int, int>;
using str = string;
template<typename T>
using min_heap = std::priority_queue<T, vec<T>, std::greater<T>>;
template<typename T>
using max_heap = std::priority_queue<T>;
using cd = std::complex<long double>;

// Avoid those damned people doing hash colision attacks
// see https://codeforces.com/contest/2057/problem/B
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<typename Key, typename Value>
using hash_map = typename std::conditional<
    std::is_same_v<Key, int>,
    std::unordered_map<Key, Value, custom_hash>, // specialized
    std::unordered_set<Key> // default
>::type;
template<typename T>
using hash_set = typename std::conditional<
    std::is_same_v<T, int>,
    std::unordered_set<int, custom_hash>, // specialized
    std::unordered_set<T> // default
>::type;

template<typename T>
using gnu_OST = __gnu_pbds::tree<
    T,
    __gnu_pbds::null_type,
    std::less<T>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;

// Supports insert / erase at any position in O(log n)
template<typename T>
using Rope = __gnu_cxx::rope<T>;

const double PI = 3.14159265358979323846264338327950288;

void fastIO(){
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

#endif
