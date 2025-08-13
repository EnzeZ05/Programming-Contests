#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
const int mod = 998244353;
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

int h[N], a[N], sz[N], e[M], ne[M], idx;
ll dp[5001][5001], ndp[5001];

void add(int u, int v){
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}
 
void solve(){
    int n;
    cin >> n;

    for(int i = 0; i <= n; i++){
        h[i] = -1;
        sz[i] = 0;

        for(int j = 0; j <= n; j++){
            dp[i][j] = 0;
        }
    }    
    idx = 0;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }

    auto dfs = [&](auto& self, int u, int fa) -> void{
        int leaf = 1;
        dp[u][0] = 1;

        for(int i = h[u]; i != -1; i = ne[i]){
            int v = e[i];
            if(v == fa){
                continue;
            }
            leaf = 0;

            self(self, v, u);

            for(int j = 0; j <= sz[u] + sz[v]; j++){
                ndp[j] = 0;
            }

            for(int j = 0; j <= sz[u]; j++){
                if(dp[u][j]){
                    for(int k = 0; k <= sz[v]; k++){
                        if(dp[v][k]){
                            ndp[j + k] = (ndp[j + k] + dp[u][j] * dp[v][k]) % mod;
                        }
                    }
                }
            }

            sz[u] += sz[v];
            for(int j = 0; j <= sz[u]; j++){
                dp[u][j] = ndp[j];
            }
        }

        for(int i = 0; i <= sz[u] + 1; i++){
            ndp[i] = 0;
        }

        for(int i = 0; i <= sz[u]; i++){
            if(i + 1 == a[u]){
                ndp[i + 1] = dp[u][i];
            }
            if(i != a[u]){
                ndp[i] = dp[u][i];
            }
        }

        ++sz[u];
        for(int i = 0; i <= sz[u]; i++){
            dp[u][i] = ndp[i];
        }
    };

    dfs(dfs, 1, 1);
    ll sum = 0;
    for(int i = 0; i <= sz[1]; i++){
        sum = (sum + dp[1][i]) % mod;
    }
    cout << sum << endl;
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
