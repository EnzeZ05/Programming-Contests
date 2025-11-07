#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const ld pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = 1e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = (int)1e6 + 1, M = N * 10;

ll fac[5001], inv[5001], dp[5001][5001];

int a[5001], h[5001], e[10001], ne[10001], idx;

ll qpow(ll a, ll b){
    ll res = 1;  
    a = a % mod;  
    
    while(b > 0){
        if(b % 2 == 1){
            res = (res * a) % mod; 
        }
        a = (a * a) % mod; 
        b /= 2;  
    }
    
    return res;
}

void add(int u, int v){
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}
 
void solve(){
    int n;
    cin >> n;

    // dp[u][i]: when u = root, #nodes need i ancestors with greater p

    for(int i = 1; i <= n; i++){
        h[i] = -1;
        for(int j = 0; j <= n; j++){
            dp[i][j] = 0;
        }
    }
    idx = 0;

    for(int i = 2; i <= n; i++){
        int v;
        cin >> v;
        add(v, i);
    }

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    ll ans = 1;

    auto dfs = [&](auto& self, int u) -> void{
        for(int i = h[u]; i != -1; i = ne[i]){
            int v = e[i];
            self(self, v);

            for(int j = 0; j <= n; j++){
                dp[u][j] += dp[v][j]; // transfer nodes to u when not considering p[u] > p[son_u]
                ans = ans * inv[dp[v][j]] % mod; // preparing for multinomial inv
            }
        }

        for(int i = 0; i <= n; i++){
            ans = ans * fac[dp[u][i]] % mod; // counting #chain intersections with different i demands 
        }

        for(int i = a[u] + 1; i <= n; i++){ // when insert itself, causing one offset to its sons
            dp[u][i - 1] += dp[u][i];
            dp[u][i] = 0;
        }
        dp[u][a[u]]++; // u needs a[u] greater p's
    };

    dfs(dfs, 1);
    cout << ans << "\n";
}  

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;

    fac[0] = inv[0] = 1;
    for(int i = 1; i < 5001; i++){
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = qpow(fac[i], mod - 2);
    }

    while(t--){
        solve();
    }

    return 0;
}