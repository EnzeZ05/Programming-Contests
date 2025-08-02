https://ac.nowcoder.com/acm/contest/108300

## A 	Ad-hoc Newbie ##

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

const int N = 2e5 + 1, M = 2 * N;

void solve(){
    int n;
    cin >> n;

    int a[n + 1];
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    int b[n + 1][n + 1];
    memset(b, 0, sizeof b);

    for(int i = 1; i <= n; i++){
        if(a[i] <= 1){
            continue;
        }
        else{
            b[i][i] = 1;
            for(int j = 0; j < i; j++){
                b[j][i] = j + 1;
                if(a[i] <= j + 2){
                    break;
                }
            }

            for(int j = 0; j < i; j++){
                b[i][j] = j + 1;
                if(a[i] <= j + 2){
                    break;
                }
            }
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout << b[i][j] << " ";
        }
        cout << "\n";
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

## B 	Bitwise Puzzle ##

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
    ll a, b, c;
    cin >> a >> b >> c;

    auto msb = [&](ll x) -> int{
        for(int i = 62; i >= 0; i--){
            if(x >> i & 1){
                return i;
            }
        }
        return -1;
    };

    if(a == 0 && b == 0 && c != 0){
        cout << -1 << "\n";
    }
    else if(a == c && b == c){
        cout << 0 << "\n";
    }
    else{
        if(b == 0 && a == c){
            cout << 1 << "\n" << 4 << "\n";
        }
        else{
            vector<int> op;

            if(b == 0 || msb(b) < msb(a)){
                op.push_back(4);
                b ^= a;
            }
            else if(msb(b) > msb(a)){
                op.push_back(3);
                a ^= b;
            }

            int l = msb(b), d = msb(c) - msb(a);
            while(d > 0){
                if((a >> l & 1) != (c >> (l + d) & 1)){
                    op.push_back(3);
                    a ^= b;
                }
                op.push_back(1);
                a <<= 1;
                d--;
            }

            while(b){
                int id = msb(b);
                if((c >> id & 1) != (a >> id & 1)){
                    op.push_back(3);
                    a ^= b;
                }
                op.push_back(2);
                b >>= 1;
            }

            if(b != a){
                op.push_back(4);
                b ^= a;
            }

            assert(a == b && b == c && op.size() <= 64);
            cout << op.size() << endl;
            for(auto ops : op){
                cout << ops << " ";
            }
            cout << "\n";
        }
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

## D 	Distant Control ##

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

const int N = 2e5 + 1, M = 2 * N;

void solve(){
    int n, a;
    cin >> n >> a;

    string s;
    cin >> s;

    int cnt = 0, one = 0;
    s = '#' + s;
    for(int i = 1; i <= n; i++){
        if(s[i] != s[i - 1]){
            cnt = 1;
        }
        else{
            cnt++;
        }
        if(cnt >= a + !(s[i] - '0')){
            cout << n << endl;
            return;
        }
        one += s[i] - '0';
    }

    cout << one << endl; 
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

## E 	Equal ##

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

const int N = 5e6 + 1, M = 2 * N;

struct Sieve{
    int n, cnt;
    vector<int> p, p_min;
    Sieve(int _n) : n(_n) {
        p_min.resize(n + 1, 0);
        init();
    }

    void init(){
        cnt = 0;
        for(int i = 2; i <= n; ++i){
            if(!p_min[i]) {
                p.push_back(i);
            }

            for(int pr : p) {
                if(i * pr > n) break;
                p_min[i * pr] = pr;

                if(i % pr == 0) {
                    break;
                }
            }
        }
    }
};

Sieve sv(N);
int c[N];

void solve(){
    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    if(n % 2){
        cout << "Yes" << "\n";
    }
    else if(n == 2){
        cout << (a[0] == a[1] ? "Yes" : "No") << "\n";
    }
    else{
        int k = 0;
        vector<int> vis;
        int flag = 0;

        for(int i = 0; i < n; i++){
            int x = a[i];
            while(sv.p_min[x]){
                ++c[sv.p_min[x]];
                x /= sv.p_min[x];
                
            }
            if(x != 1){
                ++c[x];
            }
        }

        for(int i = 0; i < n; i++){
            int x = a[i];
            while(sv.p_min[x]){
                flag |= c[sv.p_min[x]] & 1;
                c[sv.p_min[x]] = 0;
                x /= sv.p_min[x];
                
            }
            if(x != 1){
                flag |= c[x] & 1;
                c[x] = 0;
            }
        }

        cout << (flag ? "No" : "Yes") << "\n";
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

## H 	Head out to the Target ##

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

int h[N], ne[M], e[M], f[N], dep[N], idx;
int v[N], t[N][3], fa[N][21];

void add(int u, int v){
    e[idx] = v, ne[idx] = h[u], h[u] = idx++;
}

void solve(){   
    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        dep[i] = (int)1e9;
        h[i] = -1;
    }
    idx = 0;

    for(int i = 2; i <= n; i++){
        cin >> f[i];
        add(i, f[i]), add(f[i], i);
    }

    for(int i = 1; i <= m; i++){
        cin >> t[i][0] >> t[i][1] >> t[i][2];
    }

    dep[1] = 0;
    v[1] = 1;

    queue<int> q;
    q.push(1);

    while(!q.empty()){
        auto u = q.front();
        q.pop();

        for(int i = h[u]; i != -1; i = ne[i]){
            int j = e[i];
            if(dep[j] > dep[u] + 1){
                dep[j] = dep[u] + 1;
                q.push(j);

                fa[j][0] = u;
                for(int k = 0; k < 20; k++){
                    fa[j][k + 1] = fa[fa[j][k]][k];
                }
            }
        }
    }

    for(int i = 1; i <= m; i++){
        int u = t[i][0], l = t[i][1], r = t[i][2];
        int d = r - l + 1;
        if(v[u] && chmax(l, v[u]) <= r){
            cout << chmax(l, v[u]) << "\n";
            return;
        }

        int du = u;
        for(int k = 20; k >= 0; k--){
            int dv = fa[du][k];
            if(!dv){
                continue;
            }
            if(!v[dv]){
                du = dv;
            }
        }

        if(du != 1){
            du = fa[du][0];
        }

        if(dep[u] - dep[du] <= d){
            cout << l + dep[u] - dep[du] - 1 << "\n";
            return;
        }
        else{
            int x = u;
            for(int k = 20; k >= 0; k--){
                int dv = fa[x][k];
                if(dep[dv] >= dep[du] + d){
                    x = dv;
                }
            }

            int ts = v[du] + d;
            while(x != du){
                v[x] = ts--;
                x = f[x];
            }
        }
    }
    cout << -1 << "\n";
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

## J 	Jetton ##

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

const int N = 2e5 + 1, M = 2 * N;

void solve(){
    ll x, y;
    cin >> x >> y;

    if(x > y){
        swap(x, y);
    }

    ll cnt = 0, t = x + y;
    x = __gcd(x, y);
    while(x < t){
        x <<= 1ll;
        cnt++;
    }
    if(x != t){
        cout << -1 << "\n";
        return;
    }
    cout << cnt << "\n";
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
