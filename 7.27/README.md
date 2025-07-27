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
设前缀的信息为 $f_{i}$, 后缀为$g_{i}$, 那么有每一个分割点的贡献就是 $f_{i} * g_{i+1}$.

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

