
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
