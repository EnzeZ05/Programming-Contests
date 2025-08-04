https://qoj.ac/contest/1236

## A. Oops, It's Yesterday Twice More ##

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

void solve(){   
    int n, x, y;
    cin >> n >> y >> x;

    vector<vector<int>> a;
    a.push_back({1, n});
    a.push_back({n, 1});
    a.push_back({1, 1});
    a.push_back({n, n});

    int id = 0, min = (int)1e9;
    for(int i = 0; i < 4; i++){
        if(abs(a[i][0] - x) + abs(a[i][1] - y) < min){
            min = abs(a[i][0] - x) + abs(a[i][1] - y);
            id = i;
        }
    }

    if(id == 0){
        for(int i = 0; i < n - 1; i++){
            cout << "L";
        }
        for(int i = 0; i < n - 1; i++){
            cout << "D";
        }
        int dx = 1, dy = n;
        while(dx != x){
            cout << "R";
            dx++;
        }
        while(dy != y){
            cout << "U";
            dy--;
        }
    }
    else if(id == 1){
        for(int i = 0; i < n - 1; i++){
            cout << "R";
        }
        for(int i = 0; i < n - 1; i++){
            cout << "U";
        }
        int dx = n, dy = 1;
        while(dx != x){
            cout << "L";
            dx--;
        }
        while(dy != y){
            cout << "D";
            dy++;
        }
    }
    else if(id == 2){
        for(int i = 0; i < n - 1; i++){
            cout << "L";
        }
        for(int i = 0; i < n - 1; i++){
            cout << "U";
        }
        int dx = 1, dy = 1;
        while(dx != x){
            cout << "R";
            dx++;
        }
        while(dy != y){
            cout << "D";
            dy++;
        }
    }
    else if(id == 3){
        for(int i = 0; i < n - 1; i++){
            cout << "R";
        }
        for(int i = 0; i < n - 1; i++){
            cout << "D";
        }
        int dx = n, dy = n;
        while(dx != x){
            cout << "L";
            dx--;
        }
        while(dy != y){
            cout << "U";
            dy--;
        }
    }
    cout << "\n";
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

## C. Klee in Solitary Confinement ##

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

const int N = 6e6 + 1, M = 2 * N;

int a[N], b[N], c[N], inc = (int)3e6 + 1;

void solve(){   
    int n, k;
    cin >> n >> k;

    int ans = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] += inc;
        ++b[a[i]];
        ans = chmax(ans, b[a[i]]);
    }

    for(int i = 0; i < n; i++){
        ++c[a[i]];
        c[a[i] - k] = chmax(0, c[a[i] - k] - 1);
        ans = chmax(ans, b[a[i] + k] + c[a[i]]);
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

## D. Paimon Sorting ##

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

ll a[N], c[N], dp[N];

void solve(){   
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    Fenwick<ll> fw(N);
    dp[0] = 0;

    c[a[0]] = 1;
    fw.add(a[0], 1);
    ll max = a[0], ndp = 0, flag = 0;

    for(int i = 1; i < n; i++){
        if(a[i] > max){
            dp[i] = dp[i - 1] + 2 + ndp;
            ndp = flag = 0;
            max = a[i];
        }
        else if(a[i] == max){
            dp[i] = dp[i - 1];
            flag = 1;
        }
        else{
            dp[i] = dp[i - 1] + fw.range_query(a[i], n);
        }

        ndp += flag;

        if(!c[a[i]]){
            fw.add(a[i], 1);
            c[a[i]] = 1;
        }
    }

    for(int i = 0; i < n; i++){
        cout << dp[i] << " \n"[i == n - 1];
        c[a[i]] = 0;
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

## H. Crystalfly ##

```
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
```

## I. Cloud Retainer's Game ## 

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

void solve(){   
    ll H;
    int n, m;
    cin >> H >> n;

    vector<vector<ll>> a;
    a.push_back({0, 0, 1});

    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        a.push_back({x, y, 1});
    }

    cin >> m;
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        a.push_back({x, y, 2});
    }

    sort(a.begin(), a.end());
    map<ll, int> dp;
    
    for(int i = a.size() - 1; i >= 0; i--){
        int x = a[i][0], y = a[i][1], z = a[i][2];
        if(z == 1){
            dp[(x + y) % (2 * H)] = dp[(2 * H + x - y) % (2 * H)] = chmax(dp[(x + y) % (2 * H)], dp[(2 * H + x - y) % (2 * H)]);
        }
        else{
            dp[(x + y) % (2 * H)] += 1;
            dp[(2 * H + x - y) % (2 * H)] += 1;
        }
    }

    cout << dp[0] << endl;
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

## J. Xingqiu's Joke ##

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

unordered_map<ll, ll> mp;
vector<ll> pr;

void prime(ll x){
    for(int i = 2; i <= x / i; i++){
        if(x % i == 0){
            pr.push_back(i);
            while(x % i == 0){
                x /= i;
            }
        }
    }
    if(x > 1){
        pr.push_back(x);
    }
}

ll get(ll x, ll y){
    return x * 1e9 + y;
}

ll dfs(ll x, ll y){
    if(mp[get(x, y)]){
        return mp[get(x, y)];
    }
    if(y - x == 1){
        return mp[get(x, y)] = x - 1;
    }
    if(x == 1){
        return mp[get(x, y)] = 0;
    }

    ll ans = x - 1;
    for(auto p : pr){
        if((y - x) % p == 0){
            ll d = x % p;
            ans = chmin(ans, chmin(d + 1 + dfs(x / p, y / p), p - d + 1 + dfs(x / p + 1, y / p + 1)));
        }   
    }

    return mp[get(x, y)] = ans;
}
 
void solve(){   
    mp.clear();
    pr.clear();

    ll x, y;
    cin >> x >> y;

    if(x > y){
        swap(x, y);
    }
    prime(y - x);
    cout << dfs(x, y) << endl;
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

## M. Windblume Festival ##

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
 
void solve(){   
    int n;
    cin >> n;

    ll a[n], f1 = 0, f2 = 0, sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] < 0){
            f1 = 1;
        }
        if(a[i] > 0){
            f2 = 1;
        }
        sum += abs(a[i]);
    }

    if(n == 1){
        cout << a[0] << "\n";
    }
    else if(f1 && f2){
        cout << sum << "\n";
    }
    else if(f2){
        ll max = 0;
        for(int i = 0; i < n; i++){
            if(a[i] < a[(i + 1) % n]){
                max = chmax(max, sum - a[i] - a[(i + 1) % n] + abs(a[i] - a[(i + 1) % n]));
            }
        }

        if(max == 0){
            max = sum - a[0] - a[1];
        }
        cout << max << "\n";
    }
    else{
        ll max = 0;
        for(int i = 0; i < n; i++){
            if(a[i] > a[(i + 1) % n]){
                max = chmax(max, sum + a[i] + a[(i + 1) % n] + abs(a[i] - a[(i + 1) % n]));
            }
        }

        if(max == 0){
            max = sum + a[0] + a[1];
        }
        cout << max << "\n";
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
