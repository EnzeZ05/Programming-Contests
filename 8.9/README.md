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
## G. Fibonacci  ##
https://qoj.ac/contest/1477/problem/8025

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

void solve(){
    ll n;
    cin >> n;

    ll m = n / 3;
    ll l = m * n - 3 * m * (m + 1) / 2;
    ll r = m * (m + 1);

    cout << l + r << "\n";
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

## M. Gitignore  ##
https://qoj.ac/contest/1477/problem/8031

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
vector<int> adj[N];

unordered_map<string, int> mp1;
unordered_map<int, int> fa, mp2;

void solve(){
    int n, m;
    cin >> n >> m;

    mp1.clear();
    mp2.clear();
    fa.clear();

    int id = 1; 

    for(int i = 0; i < n; i++){
        string s; cin >> s; s += '/';
        string t = "";
        int pre = -1;

        for(int j = 0; j < (int)s.size(); j++){
            t += s[j];                 
            if(s[j] == '/'){
                if(!mp1.count(t)){
                    mp1[t] = id++;
                }
                int cur = mp1[t];
                if(pre != -1){
                    if(!fa.count(cur)){
                        adj[pre].push_back(cur);
                        fa[cur] = pre;
                    }
                }
                pre = cur;
            }
        }
    }

    for(int i = 0; i < m; i++){
        string s; cin >> s; s += '/';
        string t = "";
        int pre = -1;

        for(int j = 0; j < (int)s.size(); j++){
            t += s[j];
            if(s[j] == '/'){
                if(!mp1.count(t)){
                    mp1[t] = id++;
                }
                int cur = mp1[t];
                if(pre != -1){
                    if(!fa.count(cur)){
                        adj[pre].push_back(cur);
                        fa[cur] = pre;
                    }
                }
                pre = cur;
            }
        }

        if(pre != -1){
            mp2[pre] = 1;
        }
    }


    for(int i = 1; i < id; i++){
        if(mp2[i]){
            int u = i;
            while (fa[u] && mp2[fa[u]] != 1){
                mp2[fa[u]] = 1;
                u = fa[u];
            }
        }
    }

    int ans = 0;
    for(int i = 1; i < id; i++){
        if(!fa[i]){
            auto dfs = [&](auto& self, int u) -> void{
                if(mp2[u] == 0){ 
                    ans++; 
                    return; 
                }
                for(int v : adj[u]){
                    self(self, v);
                }
            };
            dfs(dfs, i);
        }
    }
    cout << ans << "\n";

    for(auto& [k, v] : mp1){
        adj[v].clear();
    }
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

## B. Mine Sweeper II ##
https://qoj.ac/contest/1477/problem/8020

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

int dir_x[4] = {1, -1, 0, 0}, dir_y[4] = {-1, 1, 0, 0};
 
void solve(){
    int n, m;
    cin >> n >> m;

    vector<string> a, b;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        a.push_back(s);
    }

    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        b.push_back(s);
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans += a[i][j] == b[i][j];
        }
    }

    if(ans <= n * m / 2){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                cout << (a[i][j] == '.' ? 'X' : '.'); 
            }
            cout << "\n";
        }
    }
    else{
        for(int i = 0; i < n; i++){
            cout << a[i] << "\n";
        }
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

## D. Walker  ##
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
 
void solve(){
    ld n, p1, v1, p2, v2;
    cin >> n >> p1 >> v1 >> p2 >> v2;

    if(p1 > p2){
        swap(p1, p2);
        swap(v1, v2);
    }

    auto case1 = [&](ld x) -> int{
        ld R = 0.0L;
        ld vt1 = v1 * x;
        if(vt1 >= p1){
            R = max((vt1 + p1) / 2.0L, vt1 - p1);
            R = max((ld)0, min(R, n));        
        }

        ld L = 0.0L;
        ld vt2 = v2 * x;
        ld q = n - p2;
        if(vt2 >= q){
            L = chmax((vt2 + q) / 2.0L, vt2 - q);
            L = chmax((ld)0, chmin(L, n));
        }

        return R + L + 1e-18L >= n;
    };

    auto case2 = [&](ld x) -> int{
        ld t = (p2 - p1) / (v2 + v1);
        if(p1 == 0 && p2 == n){
            return t <= x;
        }
        else{
            x -= t;
            if(x < 0){
                return 0;
            }
            if(x * v1 - t * v1 - p1 >= n){
                return 1;
            }
            if(x * v2 - t * v2 - (n - p2) >= n){
                return 1;
            }
            if(chmax((p1 + t * v1) / v1, (n - p2 + t * v2) / v2) <= x){
                return 1;
            }
            return 0;
        }
    };

    auto case3 = [&](ld x) -> int{
        if(p1 == 0 && n / v1 <= x){
            return 1;
        }
        if(p2 == n && n / v2 <= x){
            return 1;
        }
        if(chmax(p2 / v2, (n - p1) / v1) <= x){
            return 1;
        }
        if(v1 * x >= n + chmin(p1, n - p1) || v2 * x >= n + chmin(p2, n - p2)){
            return 1;
        }
        return 0;
    };

    auto check = [&](ld x) -> int{
        return case1(x) || case2(x) || case3(x);
    };

    ld l = 0, r = 1e12, base = 1.0, eps = 1e-12;
    while(r - l > chmax(base, l) * eps){
        ld x = (l + r) / 2;
        if(check(x)){
            r = x;
        }
        else l = x;
    }

    cout << setprecision(20) << r << "\n";
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
