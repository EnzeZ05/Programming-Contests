#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
const int mod = (int)1e9 + 7;
const ll INF = 1e18;

template <typename T>
T chmax(T a, T b){
    return a > b ? a : b;
} 

template <typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}   

const int N = 1e6 + 1, M = 2 * N;

int l[N], r[N], a[N], b[N], vis[N];
vector<pair<int, int>> adj[N];

void solve(){
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;
    s = "#" + s;

    for(int i = 0; i <= n; i++){
        l[i] = r[i] = -1;
    }

    for(int i = 0; i <= m; i++){
        a[i] = b[i] = -1;
    }

    for(int i = 1; i <= m; i++){
        int k;
        cin >> k;

        for(int j = 1; j <= k; j++){
            int x;
            cin >> x;

            if(l[x] == -1){
                l[x] = i;
            }
            else{
                r[x] = i;
            }
        }
    }

    for(int i = 1; i <= n; i++){
        int x = (s[i] == 'R' ? 0 : (s[i] == 'G' ? 1 : 2));
        x = (3 - x) % 3;
        if(l[i] == -1 && x){
            cout << "impossible\n";
            return;
        }
        else if(r[i] == -1){
            if(a[l[i]] != -1 && a[l[i]] != x){
                cout << "impossible\n";
                return;
            }
            a[l[i]] = x;
        }
        else{
            adj[l[i]].push_back({r[i], x});
            adj[r[i]].push_back({l[i], x});
        }
    }

    int tag = 1, sum = 0;
    auto dfs = [&](auto& self, int u) -> bool{
        vis[u] = tag;
        sum += b[u];
        if(a[u] != -1 && a[u] != b[u]){
            return 0;
        }

        for(auto& [v, w] : adj[u]){
            if(vis[v] == tag){
                if((b[u] + b[v] - w + 3) % 3){
                    return 0;
                }
                continue;
            }

            b[v] = (w - b[u] + 3) % 3;
            if(!self(self, v)){
                return 0;
            }
        }
        return 1;
    };

    int ans = 0;
    for(int i = 1; i <= m; i++){
        if(vis[i]){
            continue;
        }

        int cur = (int)1e9;
        for(int j = 0; j < 3; j++){
            tag += 1;
            b[i] = j;
            sum = 0;
            if(dfs(dfs, i)){
                cur = chmin(cur, sum);
            }
        }
        if(cur == 1e9){
            cout << "impossible\n";
            return;
        }
        ans += cur;
    }
    cout << ans << "\n";
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
