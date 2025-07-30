
## 题目1 A - Recycling Center ##

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

void solve(){   
    int n, c;
    cin >> n >> c;

    ll a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    sort(a, a + n);
    ll ans = 0;

    for(int i = 0, inc = 1; i < n; i++, inc = 2){
        int flag = 0, id = 0;
        for(int j = 0; j < n; j++){
            a[j] *= inc;
            if(a[j] && a[j] <= c){
                flag = 1;
                id = j;
            }
        }
        if(flag){
            a[id] = 0;
        }
        else{
            ans++;
        }
    }
    cout << ans << endl;
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

## 题目2 B - Deque Process ##

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

void solve(){   
    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    string s = "";
    for(int i = 0, j = n - 1, k = 0; i <= j; k ^= 1){
        if(i == j){
            s += 'L';
            break;
        }
        if(k % 2){
            if(a[i] < a[j]){
                s += 'L';
                i++;
            }
            else{
                s += 'R';
                j--;
            }
        }
        else{
            if(a[i] > a[j]){
                s += 'L';
                i++;
            }
            else{
                s += 'R';
                j--;
            }
        }
    }
    cout << s << endl;
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

## 题目3 C. Leftmost Below ##

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

void solve(){   
    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    if(a[0] == 1 && a[1] == 2){
        cout << "No" << endl;
        return;
    }
    if(a[0] < a[1] && a[1] > 2ll * a[0] - 1){
        cout << "No" << endl;
        return;
    }

    int min = chmin(a[0], a[1]);
    for(int i = 2; i < n; i++){
        if(a[i] > 2ll * min - 1){
            cout << "No" << endl;
            return;
        }
        min = chmin(min, a[i]);
    }
    cout << "Yes" << endl;
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

## 题目4 D. Sum of LDS ##
考虑dp，设 $dp_{i}$ 为从 左区间边界 $1$ 到 $i-1$ 和右区间边界为 $i$ 的时候的LDS数量。

如果当前 $a_{i} \leq a_{i-1}$, 说明对于以 $a_{i-1}$ 结尾的子数组中的LDS都可以和 $a_{i}$ 衔接上( $a_{i}$ 更小)，而因为以 $a_{i-1}$ 结尾的子数组有 $i-1$ 个再加上 $a_{i}$ 自己, 所以转移为 $dp_{i} = dp_{i-1} + i$。

如果 $a_{i} \geq a_{i-1}$, 说明以 $a_{i-1}$ 结尾的子数组中的LDS就算和 $a_{i}$ 衔接上，因为 $a_{i}$ 更大，所以不会影响LDS的数量，但单独算一个，所以有 $dp_{i} = dp_{i-1} + 1$。

答案为 $\sum{dp}$。

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

void solve(){
    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    ll dp[n];
    memset(dp, 0, sizeof dp);
    dp[0] = 1;
    dp[1] = (a[1] < a[0] ? 3 : 2);

    for(int i = 2; i < n; i++){
        if(a[i - 1] < a[i]){
            dp[i] = dp[i - 1] + 1;
        }
        else{
            dp[i] = dp[i - 1] + i + 1;
        }
    }

    ll ndp = 0;
    for(int i = 0; i < n; i++){
        ndp += dp[i];
    }
    cout << ndp << endl;
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

