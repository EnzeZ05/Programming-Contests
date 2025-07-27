## 题目1 P2292 [HNOI2004] L 语言 ##
https://www.luogu.com.cn/problem/P2292

## 状压 bitset‑DP 思路（字典串长度 < 20）

设  
* $dp_{i}$：当前处理到 **索引 `i`（0‑based）** 时，要求子串 `[0, i‑1]` 均已完全匹配；  
* `mask`：滑动窗口 `[i‑20, i‑1]` 内的匹配状态（20 bit）；  
* $p_{i}$ ：把 `s[i]` 沿 AC 自动机转移后，**可一次性结束的字典词集合**（bitset）。

转移规则  

1. **存在匹配：**  
   $$\bigl((\text{mask} \ll 1) \mid p_i \bigr) > 0$$  
   则  mask = (mask << 1) | 1, 滑窗右移并把当前位标 1

2. **不存在匹配：**
    $$mask <<= 1$$, 仅滑窗右移
    << 为左移，| 为按位或。窗口恒长 20，所以 mask 随时保持 20 bit。

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

const int N = 1e5 + 1, M = 2 * N;

struct AhoCorasick{
    static constexpr int s = 26;
    
    struct P{
        int len, k;
        array<int, s> f;
        P() : len{0}, k{0}, f{} {}
    };
    
    vector<int> cnt;
    vector<P> tr;

    AhoCorasick(int n) : cnt(n){
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
        cnt[p] |= 1 << (int)(s.size() - 1);
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
                    cnt[tr[cur].f[i]] |= cnt[tr[tr[cur].k].f[i]];
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

void solve(){   
    int n, m;
    cin >> n >> m;

    AhoCorasick ac(N);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        ac.insert(s);
    }

    ac.build();

    for(int i = 0; i < m; i++){
        string s;
        cin >> s;

        s = "#" + s;
        int mask = 1, ans = 0;

        for(int j = 1, k = 1; j < s.size(); j++){
            k = ac.next(k, s[j] - 'a');
            if(mask & ac.cnt[k]){
                mask = mask << 1 | 1;
                ans = j;
            }
            else{
                mask <<= 1;
            }

            if(!mask){
                break;
            }
        }
        cout << ans << endl;
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

## 题目2 You Are Given Some Strings... ##
https://codeforces.com/contest/1202/problem/E

因为是两个串拼接，所以存在分割点。从这个思想衍生，有一个可行解就是前后缀分解，第一个ac自动机维护前缀，第二个维护后缀。
设前缀的信息为 $f_{i}$, 后缀为 $g_{i}$, 利用乘法原理，那么有每一个分割点的贡献就是 $f_{i} * g_{i+1}$.

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

const int N = 1e6 + 1, M = 2 * N;

struct AhoCorasick{
    static constexpr int s = 26;
    
    struct P{
        int len, k;
        array<int, s> f;
        P() : len{0}, k{0}, f{} {}
    };
    
    vector<int> cnt, ndp;
    vector<P> tr;

    AhoCorasick(int n) : cnt(n), ndp(n){
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
        cnt[p]++;
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
                    ndp[tr[cur].f[i]] = cnt[tr[cur].f[i]] + ndp[tr[tr[cur].k].f[i]];
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

ll dp1[N], dp2[N];

void solve(){   
    string s, t;
    cin >> s;
    t = s;
    reverse(t.begin(), t.end());

    int n;
    cin >> n;
 
    AhoCorasick ac1(N), ac2(N);
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;

        ac1.insert(s);

        reverse(s.begin(), s.end());
        ac2.insert(s);
    }


    ac1.build();
    ac2.build();

    int m = s.size();
    s = '#' + s;
    t = '#' + t;
 
    for(int i = 1, j = 1, k = 1; i < s.size(); i++){
        j = ac1.next(j, s[i] - 'a');
        k = ac2.next(k, t[i] - 'a');
        dp1[i] = ac1.ndp[j];
        dp2[m - i + 1] = ac2.ndp[k];
    }

    ll ans = 0;
    for(int i = 1; i < s.size() - 1; i++){
        ans += dp1[i] * dp2[i + 1];
    }
    cout << ans << endl;
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

## 题目3 阿狸的打字机
https://www.luogu.com.cn/problem/P2414

子串可以表示为前缀的后缀

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

const int N = 1e6 + 1, M = 2 * N;

int qr[N], ans[N], dfn1[N], dfn2[N], L[N], R[N], pt;
vector<int> adj[N];

struct AhoCorasick{
  static constexpr int s = 26;
  
  struct P{
      int len, k, fa, id;
      array<int, s> f, g;
      P() : len{0}, k{0}, f{}, g{} {}
  };
  
  vector<int> cnt;
  vector<P> tr;

  AhoCorasick(int n) : cnt(n){
      init();
  }
  
  void init(){
      tr.assign(2, P());
      tr[0].f.fill(1);
      tr[0].g.fill(1);
      tr[0].len = -1;
  }
  
  int new_p(){
      tr.emplace_back();
      return tr.size() - 1;
  }
  
  void insert(const string &s){
      int p = 1;
      tr[p].fa = -1;

      for(auto ch : s){
          int idx = ch - 'a';
          if(0 <= idx && idx < 26){
              if(tr[p].f[idx] == 0){
                  tr[p].g[idx] = tr[p].f[idx] = new_p();
                  tr[tr[p].f[idx]].len = tr[p].len + 1;
                  tr[tr[p].f[idx]].fa = p;
              }
              p = tr[p].f[idx];
          }
          else if(ch == 'B'){
              if(p != 1){
                  p = tr[p].fa;
              }
          }
          else{
              qr[++pt] = p, tr[p].id = pt; 
          }
      }
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

template <typename T>
struct Fenwick{
  int n, a[N];
  
  Fenwick(int n = 0){
      init(n);
  }
  
  void init(int len){
      n = len;
      memset(a, 0, sizeof a);
  }

  int lowbit(int i){
      return i & -i;
  }
  
  void add(ll x, const T &v) {
      for(ll i = x; i <= n; i += lowbit(i)){
          a[i] += v;
      }
  }

  T query(ll x) {
      ll sum = 0;
      if(x <= 0){
          return 0;
      }
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

AhoCorasick ac(N);
Fenwick<int> fw(N);

struct P{
  int x, y, id;
}a[N];

void dfs(int u){
  fw.add(dfn1[u], 1);

  if(L[ac.tr[u].id]){
      for(int i = L[ac.tr[u].id]; i <= R[ac.tr[u].id]; i++){
          ans[a[i].id] += fw.query(dfn2[qr[a[i].x]]) - fw.query(dfn1[qr[a[i].x]] - 1);
      }
  }
  for(int i = 0; i < 26; i++){
      if(ac.tr[u].g[i]){
          dfs(ac.tr[u].g[i]);
      }
  }
  fw.add(dfn1[u], -1);
};

void solve(){   
  string s;
  cin >> s;

  ac.insert(s);
  ac.build();
  
  int n;
  cin >> n;

  for(int i = 1; i <= n; i++){
      int x, y;
      cin >> x >> y;
      a[i] = {x, y, i};
  }

  auto cmp = [&](const P& a, const P& b){
      return a.y < b.y;
  };

  sort(a + 1, a + n + 1, cmp);
  int sz = ac.tr.size();

  for(int i = 1; i < ac.tr.size(); i++){
      adj[ac.get_k(i)].push_back(i);
  }

  int id = 2;
  vector<int> stk = {1};
  while(!stk.empty()){
      int u = stk.back();
      if(!dfn1[u]){              
          dfn1[u] = ++id;
          for(int v : adj[u]){
              stk.push_back(v);
          }
      } 
      else{                     
          stk.pop_back();
          dfn2[u] = id;
      }
  }

  int pos = 1;

  for(int i = 1, j = 1; i <= n; i = pos){
      while(pos <= n && a[i].y == a[pos].y){
          pos++;
      }
      L[a[i].y] = i;
      R[a[i].y] = pos - 1;
  }

  dfs(1);

  for(int i = 1; i <= n; i++){
      cout << ans[i] << '\n';
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

### 题目4 [CQOI2014] 通配符匹配 ###
https://www.luogu.com.cn/problem/P3167#submit

这题和 https://codeforces.com/problemset/problem/1975/G 类似，但这题相对容易一点（另一个是FFT/NTT 优化的字符串匹配 + 减半查找）。
因为通项符的个数小于等于10，分割了s以后最多会有20个子串，形式可以是(\*s1\*s2\*s3...*)，我们考虑dp处理s, 设 $dp_{i,j}$ 为匹配在第j个位置匹配第i个字串的状态，记作 $0/1$. 

如果为 *, 那么可以任意转移：只要前面的状态有1就行，用前缀和维护，同时注意开头可以是空串。

如果为 ?，那么从 $dp_{i-1,j-1}$ 转移。

如果是一个子串，那么转移时候要先满足它和查询串是匹配的，可用字符串哈希，最后从$dp_{i-1,j-len}$转移。

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

const int N = 1e5 + 1, M = 2 * N;

using ull = unsigned long long;

struct StringHash{
    string s;
    int n, p1, p2, b1, b2;
    vector<ull> pw1, pw2, pre1, pre2;

    void init(string _s, int _b1, int _b2, int _p1, int _p2) {
        s = _s, p1 = _p1, p2 = _p2;
        b1 = _b1, b2 = _b2;
        n = s.size();
        
        pre1.resize(n + 1, 0);
        pre2.resize(n + 1, 0);
        pw1.resize(n + 1, 1);
        pw2.resize(n + 1, 1);

        for(int i = 1; i <= n; ++i){
            pre1[i] = ((pre1[i - 1] * p1) + s[i - 1]) % b1;
            pw1[i] = pw1[i - 1] * p1 % b1;
        }

        for(int i = 1; i <= n; ++i){
            pre2[i] = ((pre2[i - 1] * p2) + s[i - 1]) % b2;
            pw2[i] = pw2[i - 1] * p2 % b2;
        }
    }

    ull query1(int l, int r) {
        return (pre1[r] - (pre1[l - 1] * pw1[r - l + 1]) % b1 + b1) % b1;
    }

    ull query2(int l, int r) {
        return (pre2[r] - (pre2[l - 1] * pw2[r - l + 1]) % b2 + b2) % b2;
    }

    int equals(StringHash st, int l, int r){
        return query1(l, r) == st.query1(l, r) && query2(l, r) == st.query2(l, r);
    }

    int equals(StringHash st){
        if(n != st.n){
            return 0;
        }
        return query1(1, n) == st.query1(1, n) && query2(1, n) == st.query2(1, n);
    }
};

/*
    ha1.init(s, 1e9 + 7, 1e9 + 9, 131, 1211221);
    ha2.init(s, 1e9 + 7, 1e9 + 9, 131, 1211221);
    // s = '#' + s;
*/

ull hs1[22], hs2[22];
string a[22];

int dp[22][N], ndp[N], id;


void solve(){   
    string s;
    cin >> s;

    string t = "";
    StringHash h;

    for(int i = 0; i < s.size(); i++){
        if(s[i] != '*' && s[i] != '?'){
            t += s[i];
        }
        else{
            if(t != ""){
                a[++id] = t;
                h.init(t, 1e9 + 7, 1e9 + 9, 131, 1211221);

                hs1[id] = h.query1(1, t.size());
                hs2[id] = h.query2(1, t.size());
            }
            t = "";
            a[++id] = s[i];
        }
    }
    if(t.size()){
        a[++id] = t;
        h.init(t, 1e9 + 7, 1e9 + 9, 131, 1211221);

        hs1[id] = h.query1(1, t.size());
        hs2[id] = h.query2(1, t.size());
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        string s;
        cin >> s;

        int m = s.size();

        StringHash h;
        h.init(s, 1e9 + 7, 1e9 + 9, 131, 1211221);
        s = '#' + s;

        memset(dp, 0, sizeof dp);

        dp[0][0] = 1;

        for(int j = 1; j <= id; j++){
            if(a[j] == "*"){
                dp[j][0] |= dp[j - 1][0];
            }

            ndp[0] = dp[j - 1][0];
            for(int k = 1; k <= m; k++){
                ndp[k] = ndp[k - 1] | dp[j - 1][k];
            }

            for(int k = 1; k <= m; k++){
                if(a[j] == "?"){
                    dp[j][k] |= dp[j - 1][k - 1];
                }
                else if(a[j] == "*"){
                    dp[j][k] |= ndp[k];
                }
                else{
                    auto check = [&]() -> bool{
                        if(k < a[j].size()){
                            return 0;
                        }
                        if(h.query1(k - a[j].size() + 1, k) == hs1[j]){
                            if(h.query2(k - a[j].size() + 1, k) == hs2[j]){
                                return 1;
                            }
                        }
                        return 0;
                    };

                    if(check()){
                        dp[j][k] |= dp[j - 1][k - a[j].size()];
                    }
                }
            }
        }

        cout << (dp[id][m] ? "YES" : "NO") << endl;
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
