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

const int N = 1e5 + 10, M = 2 * N;

int a[3001], d[3001], dp[3001];

void solve(){
    int n, m, t;
    cin >> n >> m >> t;

    for(int i = 2; i <= n; i++){
        cin >> a[i];
    }

    vector<int> adj[n + 1];
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i <= n; i++){
        d[i] = (int)1e9;
    }

    queue<int> q;
    q.push(1); 
    d[1] = 0;

    while(!q.empty()){
        auto u = q.front();
        q.pop();

        for(auto& v : adj[u]){
            if(d[v] > d[u] + 1){
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    for(int i = 1; i <= n; i++){
        d[i] *= 2;
    }

    for(int i = 1; i <= n; i++){
        for(int j = t; j >= d[i]; j--){
            dp[j - d[i]] = chmax(dp[j - d[i]], dp[j] + a[i]);
        }
    }

    for(int i = t - 1; i >= 0; i--){
        cout << dp[i] << " ";
    }
    cout << "\n";
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
