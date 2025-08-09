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

int fa[N][21], dfn[N], seq[N], sz[N], dep[N], cnt;
int a[N], s[N], top, n;

vector<int> adj1[N], adj2[N];

void add(int u, int v){
    adj1[u].push_back(v);
    adj1[v].push_back(u);
}

void dfs(int u, int p){
    fa[u][0] = p;
    dep[u] = dep[p] + 1;
    dfn[u] = ++cnt;
    sz[u] = 1;

    for(int j = 1; j <= 20; j++){
        fa[u][j] = fa[fa[u][j - 1]][j - 1];
    }

    for(auto& v : adj1[u]){
        if(v == p){ 
            continue;
        }
        dfs(v, u);
        sz[u] += sz[v];
    }

    seq[u] = cnt;
    sort(adj1[u].begin(), adj1[u].end(), [&](int x,int y){ 
        return dfn[x] < dfn[y]; 
    });
}

int lca(int u, int v){
    if(dep[u] < dep[v]){
        swap(u, v);
    }

    for(int i = 20; i >= 0; i--){
        if(dep[fa[u][i]] >= dep[v]){
            u = fa[u][i];
        }
    }
    if(u == v) return u;

    for(int i = 20; i >= 0; i--){
        if (fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

bool is_anc(int u, int v){
    return dfn[u] <= dfn[v] && dfn[v] < seq[u];
}

int rooted_fa(int u, int v) {
    swap(u, v);
    if(u == v){
        return u;
    }
    if(!is_anc(u, v)){
        return fa[u][0];
    }
    auto it = upper_bound(adj1[u].begin(), adj1[u].end(), v, [&](int x, int y) {
        return dfn[x] < dfn[y];
    }) - 1;
    return *it;
}

int rooted_sz(int u, int v) {
    if(u == v) {
        return n;
    }
    if(!is_anc(v, u)) {
        return sz[v];
    }
    return n - sz[rooted_fa(u, v)];
}

int rooted_lca(int a, int b, int c) {
    return lca(a, b) ^ lca(b, c) ^ lca(c, a);
}

int jump(int u, int k){
    for(int i = 20; i >= 0; i--){
        if(dep[fa[u][i]] >= k){
            u = fa[u][i];
        }
    }
    return u;
}

int cmp(int& a, int& b){
    return dfn[a] < dfn[b];
}

void build(int k){
    sort(a, a + k, cmp);
    top = 0;
    s[++top] = a[0];

    for(int i = 1; i < k; i++){
        int anc = rooted_lca(a[0], s[top], a[i]);
        while(top > 1 && dep[s[top - 1]] >= dep[anc]){
            adj2[s[top - 1]].push_back(s[top]);
            top--;
        }

        if(anc != s[top]){
            adj2[anc].push_back(s[top]);
            s[top] = anc;
        }
        s[++top] = a[i];
    }

    while(top > 1){
        adj2[s[top - 1]].push_back(s[top]);
        top--;
    }
}

int b[N], dp[N], tag[N];

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

## E. Ancient Tree ##
https://codeforces.com/contest/2127/problem/E

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

const int N = 2e5 + 10, M = 2 * N;
int fa[N][21], dep[N], sz[N], dfn[N], cnt;
int h[N], e[M], ne[M], idx;
int a[N], s[N], top;
int st[N], ft[N];

vector<int> adj[N];

void add(int u, int v){
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

int c[N], w[N];

void dfs(int u, int p){
    fa[u][0] = p;
    dep[u] = dep[p] + 1;
    dfn[u] = ++cnt;
    sz[u] = 1;

    if(c[u]){
        ft[u] = c[u];
    }
    else{
        ft[u] = ft[p];
    }

    for(int j = 1; j <= 20; j++){
        fa[u][j] = fa[fa[u][j - 1]][j - 1];
    }

    for(int i = h[u]; i != -1; i = ne[i]){
        int v = e[i];
        if(v == p){ 
            continue;
        }
        dfs(v, u);
        sz[u] += sz[v];

        if(st[v]){
            st[u] = st[v];
        }
    }

    if(c[u]){
        st[u] = c[u];
    }
}

int lca(int u, int v){
    if(dep[u] < dep[v]){
        swap(u, v);
    }

    for(int i = 20; i >= 0; i--){
        if(dep[fa[u][i]] >= dep[v]){
            u = fa[u][i];
        }
    }
    if(u == v) return u;

    for(int i = 20; i >= 0; i--){
        if (fa[u][i] != fa[v][i]){
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int cmp(int& a, int& b){
    return dfn[a] < dfn[b];
}

vector<int> cr[N];
vector<int> vt;
int fq[N];

void build(int k){
    sort(a, a + k, cmp);
    top = 0;

    s[++top] = a[0];
    vt.push_back(a[0]);
    
    for(int i = 1; i < k; i++){
        int anc = lca(s[top], a[i]);
        while(top > 1 && dep[s[top - 1]] >= dep[anc]){
            if(s[top - 1] != s[top]){
                adj[s[top - 1]].push_back(s[top]);
            }
            top--;
        }

        if(anc != s[top]){  
            adj[anc].push_back(s[top]);
            s[top] = anc;
            vt.push_back(anc);
        }
        s[++top] = a[i];
        vt.push_back(a[i]);
    }

    while(top > 1){
        if(s[top - 1] != s[top]){
            adj[s[top - 1]].push_back(s[top]);
        }
        top--;
    }
}

void calc(int u, int op, int cr){
    fq[u] += op;
    if(!c[u]){
        c[u] = cr;
    }

    for(auto v : adj[u]){
        calc(v, op, cr);
    }
}

void color(int u, int cr){
    if(c[u]){
        cr = c[u];
    }
    else{
        c[u] = cr;
    }

    for(int i = h[u]; i != -1; i = ne[i]){
        int j = e[i];
        if(fa[u][0] != j){
            color(j, cr);
        }
    }
}

// multi cases plus queries is stupid
void solve(){   
    int n, q;
    cin >> n >> q;

    for(int i = 0; i <= n; i++){
        st[i] = ft[i] = fq[i] = 0;
        dep[i] = (int)1e9;
        h[i] = -1;
    }    

    for(int i = 0; i <= q; i++){
        cr[i].clear();
    }

    for(int i = 0; i <= 20; i++){
        fa[0][i] = 0;
    }
    idx = cnt = 0;

    for(int i = 1; i <= n; i++){
        cin >> w[i];
    }

    int flag = 0;
    for(int i = 1; i <= n; i++){
        cin >> c[i];
        flag |= c[i];

        cr[c[i]].push_back(i);
    }

    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        add(u, v), add(v, u);
    }

    if(!flag){
        cout << 0 << "\n";
        for(int i = 1; i <= n; i++){
            cout << 1 << " ";
        }
        cout << "\n";
        return;
    }

    dep[0] = 0;
    dfs(1, 0);

    for(int i = 1; i <= q; i++){
        if(cr[i].size()){
            for(int j = 0; j < cr[i].size(); j++){
                a[j] = cr[i][j];
            }
            
            build(cr[i].size());
            calc(s[1], 1, i);
            
            sort(vt.begin(), vt.end());
            vt.erase(unique(vt.begin(), vt.end()), vt.end());
            for(int u : vt){
                adj[u].clear();
            }
            vt.clear();
        }
    }

    ll ans = 0;
    for(int i = 1; i <= n; i++){
        if(fq[i] > 1){
            ans += w[i];
        }
    }

    for(int i = 1; i <= n; i++){
        if(c[i]){
            color(1, c[i]);
            break;
        }
    }

    cout << ans << "\n";
    for(int i = 1; i <= n; i++){
        cout << c[i] << " ";
    }
    cout << "\n";
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
```
