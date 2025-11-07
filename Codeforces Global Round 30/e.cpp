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
 
void solve(){
    int n, m;
    cin >> n >> m;

    for(int i = 0; i <= n + m; i++){
        adj[i].clear();
        deg[i] = 0;
        node[i] = i;
    }

    for(int i = 1; i <= m; i++){
        c[n + i] = (int)2e9;
    }

    int root = n;

    ll ans = 0;
    for(int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        deg[u]++, deg[v]++;

        int du = find(u), dv = find(v);
        ans += w;

        if(du != dv){
            node[du] = node[dv] = ++root;
            c[root] = w;
            add(du, root);
            add(dv, root);
        }
        else{
            node[du] = ++root;
            c[root] = w;
            add(du, root);
        }
    }

    auto dfs1 = [&](auto& self, int u, int fa) -> void{
        for(auto& v : adj[u]){
            if(v == fa || v <= n){
                continue;
            }

            c[v] = chmin(c[v], c[u]);
            self(self, v, u);
        }
    };

    dfs1(dfs1, root, root);

    auto dfs2 = [&](auto& self, int u, int fa) -> int{
        int pass = (u <= n && deg[u] % 2);

        for(auto& v : adj[u]){
            if(v == fa){
                continue;
            }
            pass += self(self, v, u);
        }

        if(u > n){
            int k = pass / 2;
            pass &= 1;
            ans += k * 1ll * c[u];
        }
        return pass;
    };

    assert(dfs2(dfs2, root, root) == 0);
    cout << ans << "\n";
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