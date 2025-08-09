## [HNOI2014] 世界树 ##
https://www.luogu.com.cn/problem/P3233

没调出来，下面的样例都没过qwq
```
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
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

const int N = 3e5 + 10, M = 2 * N;

void solve(){   
    cin >> n;
    cnt = 0;

    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    
    dep[0] = 0;
    dfs(1, 0);
 
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int k;
        cin >> k;

        for(int j = 0; j < k; j++){
            cin >> a[j];
            tag[a[j]] = 1;
            b[j] = a[j];
        }

        build(k);
        for(int j = 0; j < k; j++){
            dp[a[j]] = rooted_sz(a[0], a[j]);
        }
        queue<int> q;

        q.push(a[0]);
        cout << a[0] << " " << rooted_sz(a[0], a[0]) << endl;
        while(!q.empty()){
            auto u = q.front();
            q.pop();

            int d = dep[u] - dep[fa[u][0]], id = fa[u][0];
            for(auto& k : adj2[u]){
                if(tag[u]){
                    if(dep[k]){
                        int ds = (dep[k] - dep[u] + 1) / 2;
                        if(dep[k] - dep[u] == 1){
                            dp[u] -= rooted_sz(a[0], k);
                        }
                        else if((dep[k] - dep[u] + 1) & 1){
                            if(u > k){
                                int mid = jump(k, ds);
                                dp[u] -= rooted_sz(a[0], mid);
                                dp[k] += rooted_sz(a[0], mid) - rooted_sz(a[0], k);
                            }
                            else{
                                int mid = jump(k, ds - 1);
                                dp[u] -= rooted_sz(a[0], mid);
                                dp[k] += rooted_sz(a[0], mid) - rooted_sz(a[0], k);
                            }
                        }
                        else{
                            int mid = jump(k, ds);
                            cout << u << " " << k << " " << mid << "\n";
                            cout << rooted_sz(a[0], mid) << "\n";
                            dp[u] -= rooted_sz(a[0], mid);
                            dp[k] += rooted_sz(a[0], mid) - rooted_sz(a[0], k);
                        }
                    }
                }
                else{
                    if(abs(dep[k] - dep[u]) <= d){
                        d = abs(dep[k] - dep[u]);
                        if(k < id){
                            id = k;
                        }
                    }
                }
                if(dep[k] > dep[u]){
                    q.push(k);
                }
            }

            if(!tag[u] && adj2[u].size() == 1){
                dp[fa[u][0]] += rooted_sz(a[0], u);
            }
            else{
                dp[id]++;
            }
        }

        for(int j = 0; j < k; j++){
            cout << dp[b[j]] << " ";
            adj2[a[j]].clear();
            tag[a[j]] = 0;
        }
        cout << "\n";
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
```

