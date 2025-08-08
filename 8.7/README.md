## 3630. 划分数组得到最大异或运算和与运算之和 ##
https://leetcode.cn/problems/partition-array-for-maximum-xor-and-and/description/

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

struct Basis{
    static const int bits = 32;

    vector<ll> bs, t;
    int flag, sz;

    Basis() : bs(bits + 1), t(bits + 1), flag(0), sz(0) {}

    ll insert(ll x){
        for(int i = bits; i >= 0; i--){
            if(x & (1ll << i)){
                if(!bs[i]){
                    bs[i] = x;
                    sz++;
                    return 0;
                }
                x ^= bs[i];
            }
        }
        flag = 1;
        return x;
    }

    int check(ll x){ //查询一个数是否可以被一堆数异或出来
        if(x == 0){
            return 1;
        }
        for(int i = bits; i >= 0; i--){
            if(x & (1ll << i)){
                if(!bs[i]) return 0;
                x ^= bs[i];
            }
        }
        return 1;
    }

    ll get_max(ll res = 0){ //查询异或最大值
        for(int i = bits; i >= 0; i--){
            res = chmax(res, res ^ bs[i]);
        }
        return res;
    }

    ll get_min(){ //查询异或最小值
        if(flag){
            return 0;
        }
        for(int i = 0; i <= bits; i++){
            if(bs[i]) return bs[i];
        }
        return 0;
    }

    ll query(ll k){ //查询异或第k大值
        ll res = 0, cnt = 0;

        k -= flag;
        if(!k){
            return 0;
        }

        for(int i = 0; i <= bits; i++){
            for(int j = i - 1; j >= 0; j--){
                if(bs[i] & (1ll << j)){
                    bs[i] ^= bs[j];
                }
            }
            if(bs[i]) t[cnt++] = bs[i];
        }

        if(k >= (1ll << cnt)){
            return -1;
        }

        for(int i = 0; i < cnt; i++){
            if(k & (1ll << i)){
                res ^= t[i];
            }
        }
        return res;
    }
};

class Solution {
public:
    ll maximizeXorAndXor(vector<int>& a) {
        int n = a.size();

        ll max = 0;
        for(int i = 0; i < 1 << n; i++){
            int _and = 0, flag = 0;

            Basis b;
            ll _xor = 0;
            for(int j = 0; j < n; j++){
                if(i >> j & 1){
                    if(!flag){
                        _and = a[j];
                        flag = 1;
                    }
                    else{
                        _and &= a[j];
                    }
                }
                else{
                    _xor ^= a[j];
                }
            }
            
            for(int j = 0; j < n; j++){
                if(!(i >> j & 1)){
                    b.insert(a[j] & (~_xor));
                }
            }

            ll x = b.get_max();
            max = chmax(max, _xor + 2 * (x & (~_xor)) + _and);
        }
        return max;
    }
};
```
## C2. Interactive RBS (Medium Version) ##
https://codeforces.com/contest/2129/problem/C2

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

const int N = 2e5 + 1, M = 2 * N;
 
void solve(){   
    int n;
    cin >> n;

    auto ask = [&](const vector<int>& a) -> int{
        cout << "?" << " " << a.size() << " ";
        for(auto A : a){
            cout << A << " ";
        }
        cout << "\n";

        int ans;
        cin >> ans;
        return ans;
    };

    int l = 1, r = n + 1;
    while(l < r){
        int mid;
        mid = l + r >> 1;

        vector<int> a;
        for(int i = 1; i <= mid; i++){
            a.push_back(i);
        }

        int ans = ask(a);
        if(ans){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }

    //asserting s[l - 1, l] = "()"
    string s(n + 1, '?');

    if(l > n){
        int l = 1, r = n + 1;
        while(l < r){
            int mid = l + r >> 1;
            if(ask({mid, 1}) == 1){
                r = mid;
            }
            else{
                l = mid + 1;
            }
        }

        for(int i = 1; i < l; i++){
            s[i] = ')';
        }
        for(int i = l; i <= n; i++){
            s[i] = '(';
        }
    }   
    else{
        int L = l - 1;

        vector<int> ans;
        for(int i = 128; i >= 1; i /= 2){
            for(int j = 0; j < i; j++){
                ans.push_back(L);
                ans.push_back(L + 1);
            }
            ans.push_back(L + 1);
        }

        int diff = ask(ans);

        for(int i = 1; i <= n; i += 8){
            vector<int> a;
            for(int j = 128, t = 0; j >= 1; j /= 2, t++){
                if(i + t > n){
                    a.push_back(L + 1);
                }
                else{
                    a.push_back(i + t);                     
                }
                a.push_back(L + 1);
                for(int k = 0; k < j - 1; k++){
                    a.push_back(L);
                    a.push_back(L + 1);
                }
                a.push_back(L + 1);
            }

            int x = diff - ask(a);
            for(int j = 7, k = 0; j >= 0; j--, k++){
                if(i + k > n){
                    break;
                }
                if(x >> j & 1){
                    s[i + k] = ')';
                }
                else{
                    s[i + k] = '(';
                }
            }
        }
    }

    cout << "! ";
    for(int i = 1; i <= n; ++i){
        cout << s[i];
    }
    cout << "\n" << flush;
}   
    
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    int t = 1;
    cin >> t;

    while(t--){
        solve();
    }
    return 0;
}
```

## E. Array Queries ##
https://codeforces.com/problemset/problem/797/E

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

const int N = 1e5 + 10, M = 2 * N;
int a[N], dp[N][360];

void solve(){   
    int n;
    cin >> n;

    int m = sqrt(n);
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    for(int i = n; i >= 1; i--){
        for(int j = 1; j <= m; j++){
            dp[i][j] = dp[chmin(n + 1, i + a[i] + j)][j] + 1;
        }
    }

    int q;
    cin >> q;

    for(int i = 1; i <= q; i++){
        int p, k;
        cin >> p >> k;

        if(k <= m){
            cout << dp[p][k] << "\n";
        }
        else{
            int op = 0;
            while(p <= n){
                p = p + a[p] + k;
                op++;
            }
            cout << op << "\n";
        }
    }
}   
    
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    int t = 1;
    // cin >> t;

    while(t--){
        solve();
    }
    return 0;
}
```

## D. Unusual Sequences ##
https://codeforces.com/problemset/problem/900/D

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

const int N = 1e5 + 10, M = 2 * N;

ll qpow(ll a, ll b, ll m){
    ll res = 1;  
    a = a % m;  
    
    while(b > 0){
        if(b % 2 == 1){
            res = (res * a) % m; 
        }
        a = (a * a) % m; 
        b /= 2;  
    }
    
    return res;
}

vector<int> pr;

void sieve(int LIM = 31623){
    vector<bool> is(LIM + 1, true);
    is[0] = is[1] = false;
    for(int i = 2; 1LL * i * i <= LIM; ++i){
        if(is[i]){
            for(int j = i * i; j <= LIM; j += i){ 
                is[j] = false;
            }
        }
    }
    for(int i = 2; i <= LIM; ++i){
        if(is[i]){
            pr.push_back(i);
        }
    }
}

int mu(ll n) {
    if(n == 1){
        return 1;
    }

    int cnt = 0;
    for(int p : pr){
        if(1ll * p * p > n){
            break;
        }
        if(n % p == 0){
            n /= p;
            if(n % p == 0){ 
                return 0; 
            }

            ++cnt;                    
            while(n % p == 0){ 
                n /= p;
            }
        }
    }
    
    if(n > 1){ 
        ++cnt;
    }              
    return (cnt & 1) ? -1 + mod : 1;
}


void solve(){   
    ll x, y;
    cin >> x >> y;

    if(y % x != 0){
        cout << 0 << "\n";
    }
    else{
        y = y / x;
        ll ans = 0;
        sieve();

        for(ll i = 1; i * i <= y; i++){
            if(y % i == 0){
                ans = (ans + mu(y / i) * 1ll * qpow(2, i - 1, mod) % mod) % mod;
                if(y / i != i){
                    ans = (ans + mu(y / (y / i)) * 1ll * qpow(2, y / i - 1, mod) % mod) % mod;
                }
            }
        }
        cout << ans << "\n";
    }
}   
    
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    int t = 1;
    // cin >> t;

    while(t--){
        solve();
    }
    return 0;
}
```
