#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const double pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = (ll)4e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = (int)1e6 + 1;

vector<pair<int, int>> adj[N];
ll par[N];

void solve(){
    int n;
    cin >> n;

    for(int i = 0; i < n - 1; i++){
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w % 2});
        adj[v].push_back({u, w % 2});
    }

    auto dfs = [&](auto& self, int u, int fa) -> void{
        for(auto& [v, w] : adj[u]){
            if(v == fa){
                continue;
            }

            par[v] = par[u] ^ (w & 1);
            self(self, v, u);
        }
    };

    dfs(dfs, 1, 1);
    ll l = 0, r = 0;
    for(int i = 1; i <= n; i++){
        if(par[i]){
            l++;
        }
        else{
            r++;
        }
    }
    cout << l * r << "\n";
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