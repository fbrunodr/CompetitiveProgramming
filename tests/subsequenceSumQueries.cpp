// see https://codeforces.com/gym/101741/problem/J

#include<bits/stdc++.h>
using namespace std;
 
template<typename T>
class DivideAndConquerDP{
 
    using _T = optional<T>;
    using _T_T = pair<_T, _T>;
 
private:
    // [0, N-1]
    int N;
 
    function<T(int)> singleElement;
    function<T(T&,int)> elementMerge;
 
    vector<vector<_T>> memo;
 
    void solveMoving(int mid, int d, bool toRight){
        if(memo[mid][d] != nullopt)
            return;
        int idx = toRight ? mid + d : mid - d;
        if(d == 0){
            memo[mid][d] = singleElement(idx);
            return;
        }
        solveMoving(mid, d-1, toRight);
        memo[mid][d] = elementMerge(*memo[mid][d-1], idx);
    }
 
    _T_T solve(int i, int j, int L, int R){
        int mid1 = (L + R) / 2;
        int mid2 = mid1 + 1;
 
        if(j < mid1)
            return solve(i, j, L, mid1-1);
        else if(i > mid2)
            return solve(i, j, mid2+1, R);
        else if(j == mid1){
            solveMoving(mid1, mid1-i, false);
            return {memo[mid1][mid1-i], nullopt};
        }
        else if(i == mid2){
            solveMoving(mid2, j-mid2, true);
            return {memo[mid2][j-mid2], nullopt};
        }
        else{
            solveMoving(mid1, mid1-i, false);
            solveMoving(mid2, j-mid2, true);
            return {memo[mid1][mid1-i], memo[mid2][j-mid2]};
        }
 
        return {nullopt, nullopt};
    }
 
    void init(int L, int R){
        if(L > R)
            return;
 
        int mid1 = (L + R) / 2;
        int mid2 = mid1 + 1;
 
        memo[mid1] = vector<_T>(mid1 - L + 1, nullopt);
        if(mid2 <= R)
            memo[mid2] = vector<_T>(R - mid2 + 1, nullopt);
 
        init(L, mid1-1);
        init(mid2+1, R);
    }
 
    public:
    DivideAndConquerDP(int _n, function<T(int)> _ele, function<T(T&,int)> _eleMerge){
        N = _n;
        memo = vector<vector<_T>>(N);
        init(0, N-1);
        singleElement = _ele;
        elementMerge = _eleMerge;
    }
 
    // The merge of intervals is left for the user
    _T_T RQ(int i, int j){
        assert(i <= j);
        return solve(i, j, 0, N-1);
    }
};


#define MOD (int)(1e9 + 7)

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, m;
    cin >> n >> m;
 
    using vi = vector<int>;
    vi a(n);
    for(auto& a_i : a){
        cin >> a_i;
        a_i %= m;
    }


    auto element = [&](int i){
        vi ans(m, 0);
        ans[0]++;
        ans[a[i]]++;
        return ans;
    };

    auto mergeElement = [&](vi& range, int i){
        vi dontTake = range;
        vi take = dontTake;
        rotate(take.begin(), take.begin() + (m - a[i]), take.end());
        for(int i = 0; i < m; i++)
            take[i] = (dontTake[i] + take[i]) % MOD;
        return take;
    };

    vi empty;

    DivideAndConquerDP<vi> solver(n, element, mergeElement);

    int queries; cin >> queries;
    while(queries--){
        int i, j; cin >> i >> j;
        i--; j--;
        auto [left, right] = solver.RQ(i, j);
        if(right == nullopt){
            cout << (*left)[0] << '\n';
        }
        else{
            int ans = 0;
            for(int i = 0; i < m; i++){
                ans += ((long long)(*left)[i] * (*right)[(m-i)%m]) % MOD;
                ans %= MOD;
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
