#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

#define pb push_back

const ld pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = 1e18;

template<typename T>
T chmax(T a, T b) {
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b) {
    return a > b ? b : a;
}

const int N = (int)1e6 + 1, M = N * 2;
int h[N], e[M], ne[M], idx;
ll a[N], t[N], dp[N][2];

void add(int u, int v){
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void solve(){
    int n;
    cin >> n;

    for(int i = 1; i <= n; i++){
        dp[i][0] = dp[i][1] = 0;
        h[i] = -1;
    }
    idx = 0;

    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }        
    for(int i = 1; i <= n; i++){
        cin >> t[i];
    }

    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }

    auto dfs = [&](auto& self, int u, int fa) -> void{  
        ll max = 0, sum = 0;
        for(int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if(j == fa){
                continue;
            }
            self(self, j, u);
            max = chmax(max, a[j]);
            sum += dp[j][0];
        }

        dp[u][0] = sum + max;

        vector<int> mx(2), b(2);
        for(int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if(j == fa || t[j] != 3){
                continue;
            }
            if(a[j] > mx[0]){
                mx[1] = mx[0];
                b[1] = b[0];
                mx[0] = a[j];
                b[0] = j;
            }   
            else if(a[j] >= mx[1]){
                mx[1] = a[j];
                b[1] = j;
            }
        }

        for(int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if(j == fa){
                continue;
            }
            dp[u][0] = chmax(dp[u][0], sum + dp[j][1] - dp[j][0] + (j == b[0] ? mx[1] : mx[0]));
        }

        dp[u][1] = sum + a[u];
    };

    dfs(dfs, 1, 1);
    cout << dp[1][0] + a[1] << endl;
}  

int main(){
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);

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
