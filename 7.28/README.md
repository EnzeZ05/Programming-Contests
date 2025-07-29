## 题目1 Death DBMS ##
https://codeforces.com/contest/1437/problem/G

熟悉AC自动机的性质，一个串中的子串能通过fail指针得到，那么建出fail树时候可以发现查询串中fail指针所有祖先节点包含的完整串都是它的子串，那么对于每个fail指针可以做树链剖分到根查询。注意重复要用multiset维护相同名字所对应的值。

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

const int N = 3e5 + 1, M = 2 * N;
int siz[N], top[N], dep[N], fa[N], in[N];
vector<int> adj[N];

struct HLD{
    int n, cur;
    
    HLD() {}
    HLD(int n){
        init(n);
    }

    void init(int n){
        this->n = n;
        for(int i = 0; i < n; i++){
            siz[i] = top[i] = dep[i] = fa[i] = in[i] = 0;
        }
        cur = 1;
    }

    void add(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work(int root = 1){
        top[root] = root;
        dep[root] = 0;
        fa[root] = -1;
        dfs1(root);
        dfs2(root);
    }

    void dfs1(int u){
        if(fa[u] != -1){
            adj[u].erase(find(adj[u].begin(), adj[u].end(), fa[u]));
        }
        
        siz[u] = 1;
        for(auto &v : adj[u]){
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if(siz[v] > siz[adj[u][0]]){
                swap(v, adj[u][0]);
            }
        }
    }

    void dfs2(int u){
        in[u] = cur++;
        for(auto v : adj[u]){
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
    }
};

struct AhoCorasick{
    static constexpr int s = 26;
    
    struct P{
        int len, k;
        array<int, s> f;
        P() : len{0}, k{0}, f{} {}
    };
    
    vector<P> tr;

    AhoCorasick(int n){
        init();
    }
    
    void init(){
        tr.assign(2, P());
        tr[0].f.fill(1);
        tr[0].len = -1;
    }
    
    int new_p(){
        tr.emplace_back();
        return tr.size() - 1;
    }
    
    int insert(const string &s){
        int p = 1;
        for(auto ch : s){
            int idx = ch - 'a';
            if(tr[p].f[idx] == 0){
                tr[p].f[idx] = new_p();
                tr[tr[p].f[idx]].len = tr[p].len + 1;
            }
            p = tr[p].f[idx];
        }
        return p;
    }
    
    void build(){
        queue<int> q;
        q.push(1);
        
        while(!q.empty()){
            int cur = q.front();
            q.pop();
            
            for(int i = 0; i < s; i++){
                if(tr[cur].f[i] == 0){
                    tr[cur].f[i] = tr[tr[cur].k].f[i];
                } 
                else{
                    tr[tr[cur].f[i]].k = tr[tr[cur].k].f[i];
                    q.push(tr[cur].f[i]);
                }
            }
        }
    }
    
    int next(int p, int ch){ 
        return tr[p].f[ch];
    }
    
    int get_k(int p){ //找到p的fail指针
        return tr[p].k;
    }
    
    int get_len(int p){
        return tr[p].len;
    }
    
    int get_sz(){
        return tr.size();
    }
};

struct Mark{
    void modify(const Mark &v){ 

    }
};
 
struct Operation{
    int max = -1;
    Operation(int p = -1){
        max = p;
    }

    void modify(const Mark &v){

    }
};
 
Operation operator+(Operation a, Operation b){
    return {chmax(a.max, b.max)};
}

Operation op[N * 4];

template<class Operation, class Mark>
struct SegTree{
    const int n;
 
    SegTree(int n) : n(n){
        function<void(int, int, int)> build = [&](int u, int l, int r){
            op[u] = Operation();
            if(l == r) return;
            int mid = l + r >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushup(u);
        };
 
        build(1, 1, n);
    }
 
    void pushup(int u){
        op[u] = op[u << 1] + op[u << 1 | 1];
    }
 
    void modify(int u, const Mark &mk){
        op[u].modify(mk);
    }
 
    void update(int u, int l, int r, int x, const Operation &v){
        if(l == r){
            op[u] = v;
            return;
        }
        int m = (l + r) >> 1;
 
        if(x <= m){
            update(u << 1, l, m, x, v);
        } 
        else{
            update(u << 1 | 1, m + 1, r, x, v);
        }
        pushup(u);
    }
 
    void update(int u, const Operation &v){
        update(1, 1, n, u, v);
    }
 
    Operation query(int u, int l, int r, int x, int y){
        if(x <= l && r <= y) {
            return op[u];
        }
        
        int m = (l + r) >> 1;
        Operation cur;

        if(x <= m){
            cur = query(u << 1, l, m, x, y);
        }
        if(y > m){
            cur = cur + query(u << 1 | 1, m + 1, r, x, y);
        }
        return cur;
    }
 
    Operation query(int l, int r){
        return query(1, 1, n, l, r);
    }
 
    void range_update(int u, int l, int r, int x, int y, const Mark &v){
        if(l >= x && r <= y){
            modify(u, v);
            return;
        }
 
        int m = (l + r) >> 1;

        if(x <= m){
            range_update(u << 1, l, m, x, y, v);
        }
        if(y > m){
            range_update(u << 1 | 1, m + 1, r, x, y, v);
        }
        pushup(u);
    }
 
    void range_update(int l, int r, const Mark &v){
        return range_update(1, 1, n, l, r, v);
    }
};

multiset<int> st[N];
string mp[N];
int V[N];

void solve(){   
    int n, m;
    cin >> n >> m;

    AhoCorasick ac(N);
    HLD _(N);

    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        mp[i + 1] = s;

        ac.insert(s);
    }
    ac.build(); 

    for(int i = 1; i < ac.tr.size(); i++){
        _.add(i, ac.get_k(i));
    }

    _.work(0);
    SegTree<Operation, Mark> tr(_.cur + 1);

    auto _upd = [&](int p, int ov, int nv) -> void{
        if(ov != -1){
            auto it = st[p].find(ov);
            st[p].erase(it);
        }
        st[p].insert(nv);
        tr.update(in[p], *st[p].rbegin());
    };

    auto _qr = [&](int p) -> int{
        int x = 0, y = p, max = -1;
        while(top[x] != top[y]){
            if(dep[top[x]] > dep[top[y]]){
                max = chmax(max, tr.query(in[top[x]], in[x]).max);
                x = fa[top[x]];
            }
            else{
                max = chmax(max, tr.query(in[top[y]], in[y]).max);
                y = fa[top[y]];
            }
        }
        max = chmax(max, tr.query(chmin(in[x], in[y]), chmax(in[x], in[y])).max);
        return max;
    };

    for(int i = 1; i <= n; i++){
        int p = 1;
        for(auto& c : mp[i]){
            p = ac.next(p, c - 'a');
        }
        _upd(p, -1, 0);
    }

    for(int i = 0; i < m; i++){
        int op;
        cin >> op;

        if(op == 1){
            int id, x, p = 1;
            cin >> id >> x;

            for(auto& c : mp[id]){
                p = ac.next(p, c - 'a');
            }
            _upd(p, V[id], x);
            V[id] = x;
        }
        else{
            string s; 
            cin >> s;

            int p = 1, ans = -1;
            for(auto& c : s){
                p = ac.next(p, c - 'a');
                ans = chmax(ans, _qr(p));
            }
            cout << ans << '\n';
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

## 题目2 无尽的生命 ##
https://www.luogu.com.cn/problem/P2448

拆区间做逆序对。

```
#include <bits/stdc++.h>
using namespace std;

using ll   = long long;
using ld   = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
const int    mod = 1e9 + 7;
const ll     INF = 1e18;

template <typename T>
T chmax(T a, T b){ return a > b ? a : b; }

template <typename T>
T chmin(T a, T b){ return a > b ? b : a; }

const int N = 3e5 + 5;           

template <typename T>
struct Fenwick{
    int n;
    vector<T> a, b;
    
    Fenwick(int n = 0){
        init(n);
    }
    
    void init(int len){
        n = len;
        a.assign(n + 1, T{});
        b.assign(n + 1, T{});
    }

    int lowbit(int i){
        return i & -i;
    }
    
    void add(ll x, const T &v) {
        for(ll i = x; i <= n; i += lowbit(i)){
            b[i] += x * v, a[i] += v;
        }
    }

    T query(ll x) {
        ll sum = 0;
        for(ll i = x; i; i -= lowbit(i)){
            sum += a[i];
        }
        return sum;
    }
    
    T range_query(int l, int r) {
        return query(r) - query(l);
    }

    int select(const T &k) {
        int x = 0;
        T cur{};
        for(int i = 1 << __lg(n); i; i /= 2){
            if(x + i <= n && cur + a[x + i - 1] <= k){
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

int p[N << 1], ps[N << 1], len[N << 1];

void solve(){
    int n;  cin >> n;

    vector<pair<int,int>> seg(n);
    vector<int> vals;  vals.reserve(2 * n);

    for(auto &p : seg){
        cin >> p.first >> p.second;
        vals.push_back(p.first);
        vals.push_back(p.second);
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    int id = 0;
    p[++id] = vals[0];
    len[id] = 1;
    ps[id] = id;

    for(int i = 1; i < (int)vals.size(); ++i){
        if(vals[i] - vals[i - 1] > 1){
            p[++id] = vals[i - 1] + 1;
            len[id] = vals[i] - vals[i - 1] - 1;
            ps[id] = id;
        }
        p[++id] = vals[i];
        len[id] = 1;
        ps[id] = id;
    }

    auto locate = [&](int v){
        return (int)(lower_bound(p + 1, p + 1 + id, v) - p);
    };

    for(auto &p : seg){
        int x = locate(p.first);
        int y = locate(p.second);
        swap(len[x], len[y]);
        swap(ps[x], ps[y]);
    }

    Fenwick<ll> fw(id);
    ll ans = 0;

    for(int i = id; i >= 1; --i){
        ans += fw.query(ps[i] - 1) * 1ll * len[i];
        fw.add(ps[i], len[i]);
    }

    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while(T--) solve();
    return 0;
}
```
