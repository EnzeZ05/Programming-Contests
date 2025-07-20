#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
const int mod = (int)1e9 + 7;
const ll  INF = 1e18;

template <typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template <typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = 1e6 + 1, M = 2 * N;
int dp[N];

void solve(){
    int p;
    cin >> p;

    for(int i = 1; i < p; i++){
        dp[i] = 0;
    }
    dp[0] = dp[1] = 1;

    auto dfs = [&](auto& self, int x, int p) -> int{
        if(dp[p % x]){
            return dp[x] = dp[p % x] + 1;
        }
        else{
            return dp[x] = self(self, p % x, p) + 1;
        }
    };

    for(int i = 2; i < p; i++){
        if(!dp[i]){
            dfs(dfs, i, p);
        }
    }

    double ans = 0;
    for(int i = 1; i < p; i++){
        ans += dp[i];
    }

    cout << setprecision(20) << ans / (p - 1) << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;

    while(t--){
        solve();
    }
    return 0;
}