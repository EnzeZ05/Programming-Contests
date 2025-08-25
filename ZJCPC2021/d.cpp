#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = 1e18;

template <typename T>
T chmax(T a, T b){
    return a > b ? a : b;
} 

template <typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = 2e5 + 10, M = 2 * N;

vector<pair<int, int>> adj[N];
ll dp1[17][N], dp2[N];

void solve(){
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    for(int i = 0; i < 17; i++){
        for(int j = 0; j < (1 << 17); j++){
            dp1[i][j] = INF;
        }
    }

    for(int i = (1 << 16); i < (1 << 17); i++){
        dp1[16][i] = 0;
    }

    for(int i = 15; i >= 0; i--){
        for(int j = (1 << i); j < (1 << 17); j++){
            dp2[j] = INF;
        }
        for(int j = (1 << i); j < (1 << i + 1); j++){
            dp1[i][j] = dp2[j] = 0;
        }

        for(int j = (1 << i); j < (1 << i + 1); j++){
            for(auto& [v, w] : adj[j]){
                dp2[v] = chmin(dp2[v], 1ll * w);
            }
        }

        for(int j = (1 << 17) - 1; j >= (1 << i); j--){
            int k = 31 - __builtin_clz(j);
            for(int l = 1; l < 17 && (j >> l) >= (1 << i); l++){
                dp2[j >> l] = chmin(dp2[j >> l], dp2[j] + dp1[k - l][j]);
            }
        }

        for(int j = (1 << i); j < (1 << 17); j++){
            ll ans = INF;
            int k = 31 - __builtin_clz(j);
            for(int l = 0; l < 17 && (j >> l) >= (1 << i); l++){
                ans = chmin(ans, dp2[j >> l] + dp1[k - l][j]);
            }
            dp1[i][j] = ans;
        }
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int u, v;
        cin >> u >> v;

        int l = 31 - __builtin_clz(u), r = 31 - __builtin_clz(v);
        ll ans = INF;

        for(int i = 0; i <= chmin(l, r); i++){
            if((u >> (l - i)) == (v >> (r - i))){
                ans = chmin(ans, dp1[i][u] + dp1[i][v]);
            }
        }

        cout << (ans == INF ? -1 : ans) << "\n";
    }
}
    
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;

    while(t--){
        solve();
    }
    return 0;
}
