https://qoj.ac/contest/1280

## A. Orders ##

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
    int n;
    ll k;
    cin >> n >> k;

    map<ll, ll> mp;
    vector<ll> a;
    for(int i = 0; i < n; i++){
        int u, v;
        cin >> u >> v;
        mp[u] += v;

        a.push_back(u);
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    if(mp[a[0]] > k * a[0]){
        cout << "No" << "\n";
    }
    else{
        for(int i = 1; i < a.size(); i++){
            mp[a[i]] += mp[a[i - 1]];
            if(a[i] * k < mp[a[i]]){
                cout << "No" << "\n";
                return;
            }
        }
        cout << "Yes" << "\n";
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

## B. Building Company ##

```
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = 1e18;

template <typename T>
T chmax(T a, T b){
    return a > b ? a : b;
} 

template <typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = 1e5 + 10, M = 2 * N;
unordered_map<int, priority_queue<vector<ll>, vector<vector<ll>>, greater<>>> q;

void solve(){
    int g;
    cin >> g;

    map<ll, ll> mp;
    for(int i = 0; i < g; i++){
        int id, x;
        cin >> id >> x;
        mp[id] += x;
    }    

    int n;
    cin >> n;

    vector<int> a(n);

    vector<vector<pair<int, int>>> rw(n);
    for(int i = 0; i < n; i++){
        int m;
        cin >> m;

        a[i] = m;
        for(int j = 0; j < m; j++){
            int id, x;
            cin >> id >> x;
            q[id].push({x, i});
        }

        int flag = (m == 0);

        cin >> m;
        for(int j = 0; j < m; j++){
            int id, x;
            cin >> id >> x;

            if(flag){
                mp[id] += x;
            }
            else{
                rw[i].push_back({id, x});
            }
        }
    }

    queue<pair<ll, int>> qd;
    for(auto& [k, v] : mp){
        qd.push({v, k});
    }
 
    int ans = 0;
    while(!qd.empty()){
        auto p = qd.front();
        qd.pop();

        ll u = p.first, id = p.second;
        map<int, int> vis;

        while(!q[id].empty()){
            auto p = q[id].top();
            if(u >= p[0]){
                q[id].pop();

                a[p[1]]--;
                if(a[p[1]] == 0){
                    for(auto& [x, y] : rw[p[1]]){
                        mp[x] += y;
                        vis[x] = 1;
                    }
                }
            }
            else{
                break;
            }
        }

        for(auto& [x, y] : vis){
            qd.push({mp[x], x});
        }
    }

    for(int i = 0; i < n; i++){
        ans += !a[i];
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
```

## D. Fast and Fat ##

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
    int n;
    cin >> n;

    vector<vector<ll>> a, b;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;

        a.push_back({x, y});
    }

    int l = 0, r = (int)1e9 + 1;
    while(l < r){
        int mid = l + r >> 1;

        priority_queue<vector<ll>, vector<vector<ll>>, less<>> q;
        for(int i = 0; i < n; i++){
            if(a[i][0] < mid){
                b.push_back(a[i]);
            }
            else{
                q.push({a[i][0] + a[i][1], a[i][0], a[i][1]});
            }
        }

        auto cmp = [&](const vector<ll>& a, const vector<ll>& b) -> bool{
            return a[1] > b[1];
        };
        sort(b.begin(), b.end(), cmp);

        int flag = b.empty();
        for(int i = 0; i < b.size(); i++){
            if(q.empty()){
                break;
            }

            auto p = q.top();
            q.pop();

            if(p[2] > b[i][1]){
                
            }
            else{
                p[1] -= (b[i][1] - p[2]);
                if(p[1] >= mid){
                
                }
                else{
                    break;
                }
            }

            if(i == b.size() - 1){
                flag = 1;
            }
        }
        b.clear();

        if(!flag){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    cout << l - 1 << "\n";
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

## E. Math Problem  ##

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

ostream& operator<<(ostream& os, i128 n) {
    if(n == 0){ 
        os << '0'; 
        return os; 
    }
    bool neg = n < 0;
    if (neg) n = -n;

    string s;
    while(n > 0){
        int digit = (int)(n % 10);
        s.push_back(char('0' + digit));
        n /= 10;
    }
    if(neg){
        s.push_back('-');
    }
    reverse(s.begin(), s.end());
    return os << s;
}

void solve(){
    ll N, K, M, A, B;
    cin >> N >> K >> M >> A >> B;

    i128 n = N, k = K, m = M, a = A, b = B;
    if(n % m == 0){
        cout << 0 << "\n";
    } 
    else if(k == 1){
        cout << -1 << "\n";
    }
    else{
        i128 ans = 0;
        i128 t = n;
        while(t){
            t /= k;
            ans += b;
        }

        for(int i = 0; ; i++){
            t = n;
            i128 res = 0;

            for(int j = 0; j < i; j++){
                t /= k;
                res += b;
            }
            if(res >= ans){
                break;
            }
            if(t % m == 0){
                ans = res;
                continue;
            }

            i128 l = t, r = t;
            for(int j = 0; ; j++){
                if(res >= ans){
                    break;
                }
                l = k * l;
                r = k * r + k - 1;
                res += a;

                if(r / m * m >= l){
                    break;
                }
            }
            ans = chmin(ans, res);
        }
        cout << ans << "\n";
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

## F. Colorful Segments ##

```
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
const int mod = 998244353;
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

template<class Operation, class Mark>
struct SegTree{
    const int n;
    vector<Operation> op;
    vector<Mark> mrk;
 
    SegTree(int n) : n(n), op(4 << __lg(n)), mrk(4 << __lg(n)){
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
        mrk[u].modify(mk);
    }
 
    void pushdown(int u){
        modify(u << 1, mrk[u]);
        modify(u << 1 | 1, mrk[u]);
        mrk[u] = Mark();
    }
 
    void update(int u, int l, int r, int x, const Operation &v){
        if(l == r){
            op[u] = v;
            return;
        }
        int m = (l + r) >> 1;
        pushdown(u);
 
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
        pushdown(u);
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
        pushdown(u);
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
 
struct Mark{
    ll add = 1;
    Mark(ll p = 1){
        add = p;
    }
    void modify(const Mark &v){
        add *= v.add;
        add %= mod;
    }
};
 
struct Operation{
    ll dp = 0;
    Operation(ll p = 0){
        dp = p;
    }

    void modify(const Mark &v){
        if(v.add){
            dp *= v.add;
            dp %= mod;
        }
    }
};
 
Operation operator+(Operation a, Operation b){
    return {(a.dp + b.dp) % mod};
}

void solve(){
    int n;
    cin >> n;

    vector<vector<int>> a;
    vector<int> b;

    for(int i = 0; i < n; i++){
        int l, r, c;
        cin >> l >> r >> c;
        a.push_back({l, r, c});

        b.push_back(l);
        b.push_back(r);
    }   

    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    SegTree<Operation, Mark> tr1(b.size() + 10), tr2(b.size() + 10);

    for(int i = 0; i < n; i++){
        a[i][0] = lower_bound(b.begin(), b.end(), a[i][0]) - b.begin() + 1;
        a[i][1] = lower_bound(b.begin(), b.end(), a[i][1]) - b.begin() + 1;
    }

    auto cmp = [&](const vector<int>& a, const vector<int>& b) -> bool{
        return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
    };

    sort(a.begin(), a.end(), cmp);

    tr1.update(1, 1);
    tr2.update(1, 1);

    ll ans = 1;
    for(int i = 0; i < n; i++){
        int l = a[i][0] + 1, r = a[i][1] + 1, c = a[i][2];
        if(c == 0){
            ll ndp = tr2.query(1, l - 1).dp;
            tr2.range_update(1, l - 1, 2);
            tr1.update(r, tr1.query(r, r).dp + ndp);
            ans = (ans + ndp) % mod;
        }
        else{
            ll ndp = tr1.query(1, l - 1).dp;
            tr1.range_update(1, l - 1, 2);
            tr2.update(r, tr2.query(r, r).dp + ndp);
            ans = (ans + ndp) % mod;
        }
    }

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
```

## G. Matching  ##

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
    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    map<ll, vector<ll>> mp;
    for(int i = 0; i < n; i++){
        mp[a[i] - i].push_back(a[i]);
    }

    for(auto& [k, v] : mp){
        sort(v.begin(), v.end(), greater<>());
    }

    ll sum = 0;
    for(auto& [k, v] : mp){
        for(int i = 1; i < v.size(); i += 2){
            if(v[i] + v[i - 1] > 0){
                sum += v[i] + v[i - 1];
            }
        }
    }
    cout << sum << "\n";
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

## I. Three Dice  ##

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
    int A, B;
    cin >> A >> B;

    vector<vector<int>> a, b;
    a.push_back({0});
    a.push_back({1, 4});
    a.push_back({2, 5, 8});
    a.push_back({3, 6, 9, 12});

    b.push_back({0});
    b.push_back({2, 3, 5, 6});
    b.push_back({4, 5, 6, 7, 8, 9, 10, 11, 12});
    b.push_back({6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});

    for(int i = 0; i <= 3; i++){
        for(int j = 0; j < a[i].size(); j++){
            if(a[i][j] != A){
                continue;
            }
            for(int k = 0; k < b[3 - i].size(); k++){
                if(b[3 - i][k] == B){
                    cout << "Yes" << "\n";
                    return;
                }
            }
        }
    }
    cout << "No" << "\n";
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

## J. Not Another Path Query Problem ##

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

struct DSU{
    vector<int> node, size;
 
    DSU(){}
    DSU(int n){
        init(n);
    }
 
    void init(int n){
        node.resize(n);
        size.resize(n);
 
        for(int i = 0; i < n; i++){
            node[i] = i;
            size[i] = 1;
        }
    }
 
    int find(int x){
        return x == node[x] ? x : node[x] = find(node[x]);
    }
 
    void erase(int x){
        size[find(x)] -= 1;
        node[x] = x;
    }
 
    void relocate(int x, int y){ //can't be root
        int dx = find(x), dy = find(y);
        if(dx == dy){
            return;
        }
        node[x] = dy;
        size[dx] -= 1;
        size[dy] += 1;
    }
 
    int set(int x, int y){
        return find(x) == find(y);
    }
 
    int merge(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y){
            return 0;
        }
 
        size[x] += size[y];
        node[y] = x;
        return 1;
    }
 
    int heuristic_merge(int x, int y){ 
        x = find(x);
        y = find(y);
        if(size[x] < size[y]){
            swap(x, y);
        }
        return merge(x, y);
    }
 
    int get(int x){
        return size[find(x)];
    }
};

void solve(){
    int n, m, q;
    ll V;
    cin >> n >> m >> q >> V;
    
    vector<DSU> dsu;
    DSU any(n + 1);

    for(int i = 0; i < 61; i++){
        DSU uf(n + 1);
        dsu.push_back(uf);
    }

    int msb = 0, lsb = -1;
    for(int i = 0; i < 61; i++){
        if(V >> i & 1){
            msb = i;
            if(lsb == -1){
                lsb = i;
            }
        }
    }

    for(int i = 0; i < m; i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;

        any.heuristic_merge(u, v);
        if(w < V){
            continue;
        }
        else{
            for(int j = 60; j > msb; j--){
                if(w >> j & 1){
                    dsu[j].heuristic_merge(u, v);
                }
            }
            for(int j = msb; j >= lsb; j--){
                if(!(V >> j & 1) && (w >> j & 1)){
                    dsu[j].heuristic_merge(u, v);
                }
                else if((V >> j & 1) && !(w >> j & 1)){
                    break;
                }
                else if(j == lsb && (w >> j & 1)){
                    dsu[j].heuristic_merge(u, v);
                }
            }
        }
    }

    for(int i = 0; i < q; i++){
        int u, v;
        cin >> u >> v;

        if(V == 0){
            cout << (any.set(u, v) ? "Yes" : "No") << "\n";
            continue;
        }
        for(int j = lsb; j < 61; j++){
            if(dsu[j].set(u, v)){
                cout << "Yes" << "\n";
                goto entry;
            }
        }

        cout << "No" << "\n";
        entry:;
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

## L. Puzzle: Sashigane  ##
```
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
const int mod = 998244353;
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
    int n, a, b;
    cin >> n >> a >> b;

    cout << "Yes" << "\n";
    if(n == 1){
        cout << 0 << "\n";
    }
    else{
        int x1 = a, y1 = b, l = 1, r = -1;
        cout << n - 1 << "\n";
        while(x1 > 1 && y1 < n){
            x1--, y1++;
            cout << x1 << " " << y1 << " " << l << " " << r << "\n";
            l++, r--;
        }

        int x2 = a, y2 = b;
        l = -l, r = -r;

        while(x2 < n && y2 > 1){
            x2++, y2--;
            cout << x2 << " " << y2 << " " << l << " " << r << "\n";
            l--, r++;
        }

        int x3 = chmin(x1, x2), y3 = chmin(y1, y2);
        l = -l;

        while(x3 > 1 && y3 > 1){
            x3--, y3--;
            cout << x3 << " " << y3 << " " << l << " " << r << "\n";
            l++, r++;
        }

        int x4 = chmax(x1, x2), y4 = chmax(y1, y2);
        l = -l, r = -r;
        while(x4 < n && y4 < n){
            x4++, y4++;
            cout << x4 << " " << y4 << " " << l << " " << r << "\n";
            l--, r--;
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

## M. Computational Geometry ##

```
#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
const int mod = 998244353;
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

template<typename T>
struct Point{
    T x, y;
    ld eps;

    Point() : x(0), y(0), eps(1e-9) {}
    Point(T x, T y) : x(x), y(y), eps(1e-9) {}

    void set_eps(T eps){
        this->eps = eps;
    }

    Point operator+ (const Point& b){
        return Point(x + b.x, y + b.y);
    }

    Point operator- (const Point& b){
        return Point(x - b.x, y - b.y);
    }

    Point operator- (){
        return Point(-x, -y);
    }

    Point operator* (T t) const{
        return Point(x * t, y * t);
    }

    Point operator/ (T t) const{
        return Point(x / t, y / t);
    }

    Point &operator+=(Point p) &{
        x += p.x;
        y += p.y;
        return *this;
    }

    Point &operator-=(Point p) &{
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point &operator*=(T v) &{
        x *= v;
        y *= v;
        return *this;
    }

    Point &operator/=(T v) &{
        x /= v;
        y /= v;
        return *this;
    }

    Point &operator=(const Point& b) &{
        x = b.x;
        y = b.y;
        return *this;
    }

    friend Point operator+ (const Point& a, const Point& b){
        return {a.x + b.x, a.y + b.y};
    }

    friend Point operator- (const Point& a, const Point& b){
        return {a.x - b.x, a.y - b.y};
    }

    friend bool operator==(Point a, Point b){
        return a.x == b.x && a.y == b.y;
    }

    int sign(T x){
        if(fabs(x) < eps){
            return 0;
        }
        if(x < 0){
            return -1;
        }
        return 1;
    }

    bool cmp(T x, T y){
        if(fabs(x - y) > eps){
            return 0;
        }
        return 1;
    }

    bool cmp(const Point& a, const Point& b){
        return cmp(a.x, b.x) && cmp(a.y, b.y);
    }

    T dot(const Point& a, const Point& b){
        return a.x * b.x + a.y * b.y;
    }

    T square(Point a){
        return dot(a, a);
    }

    T cross(const Point& a, const Point& b){
        return a.x * b.y - a.y * b.x;
    }

    T cross(const Point& a, const Point& b, const Point& p){
        return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    }

    T get_len(const Point& a){
        return sqrt(dot(a, a));
    }

    T get_angle(const Point& a, const Point& b){
        return acos(dot(a, b) / get_len(a) / get_len(b));
    }

    T area(const Point& a, const Point& b, const Point& c){
        return cross(b - a, c - a);
    }

    Point rotate(const Point& a, T angle){ //两个点就 b - a (b按a转)
        T dx = a.x * cos(angle) + a.y * sin(angle); 
        T dy = -a.x * sin(angle) + a.y * cos(angle);
        return Point(dx, dy);
    }

    Point intersect(const Point& p, const Point& v, const Point& q, const Point& w){
        Point u = p - q;
        T t = cross(w, u) / cross(v, w);
        return p + v * t;
    }

    T point_dist(const Point& a, const Point& b){
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    T line_dist(const Point& a, const Point& b, const Point& p){
        Point u = b - a, v = p - a;
        return fabs(cross(u, v)) / get_len(u);
    }

    T get_slope(const Point& a, const Point& b){
        if(b.y == a.y) return INF;
        if(b.x == a.x) return 0;
        return (b.y - a.y) / (b.x - a.x);
    }

    T circle_intersect(const Point& p1, const Point& p2, const T r1, const T r2){
        ld d = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

        if(d > r1 + r2 || d + chmin(r1, r2) <= chmax(r1, r2)){
            return 0;
        }
        else if(d == r1 + r2){
            return 1;
        }
        else{
            return 2;
        }
    }

    T seg_dist(const Point& a, const Point& b, const Point& p){
        if(a == b){
            return get_len(p - a);
        }
        Point u = b - a, v = p - a, w = p - b;

        if(sign(dot(u, v)) < 0){
            return get_len(v);
        }
        if(sign(dot(u, w)) > 0){
            return get_len(w);
        }
        return line_dist(a, b, p);
    }

    Point projection(const Point& a, const Point& b, const Point& p){
        Point v = b - a;
        return a + v * dot(v, p - a) / dot(v, v);
    }

    bool on_segment(const Point& a, const Point& b, const Point& p){
        bool u = sign(cross(p - a, p - b)) == 0;
        bool v = sign(dot(p - a, p - b)) <= 0;
        return u && v;
    }

    bool seg_intersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2){
        T c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
        T c3 = cross(b2 - b1, a2 - b1), c4 = cross(b2 - b1, a1 - b1);
        return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
    }

    friend std::ostream &operator<<(ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

//S = a + b / 2 - 1, S = area, a = lattice points inside, b = lattice point on boundary

void solve(){
    int n, k;
    cin >> n >> k;

    vector<Point<ld>> a;
    for(int i = 0; i < n; i++){
        ld x, y;
        cin >> x >> y;

        a.push_back({x, y});
    }

    for(int i = 0; i < n; i++){
        a.push_back(a[i]);
    }

    ld area = 0, max = 0;
    Point<ld> pt;

    auto DO = [&](int l, int r, int L, int R) -> void {
        auto f = [&](int p) -> ld {
            return pt.cross(a[p], a[L], a[R]) * 0.5;
        };

        while(r - l > 3){
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;
            if (f(m1) <= f(m2)) l = m1;
            else r = m2;
        }

        for(int i = l; i <= r; i++){
            max = chmax(max, area + f(i));
        }
    };

    for(int l = 0, r = 0; r <= n + k; r++){
        if(r - l >= 1) {
            area += (pt.cross(a[r - 1], a[r]) + pt.cross(a[r], a[l]) - pt.cross(a[r - 1], a[l])) * 0.5;
        }
        if(r - l > k){
            area += (-pt.cross(a[l], a[l + 1]) + pt.cross(a[r], a[l + 1]) - pt.cross(a[r], a[l])) * 0.5;
            ++l;
        }

        if(r - l == k){
            DO(r + 1, l - 1 + n, l, r);
        }
    }

    cout << setprecision(20) << max << "\n";
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
