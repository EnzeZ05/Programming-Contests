## A. Serval and String Theory ##

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
int cnt = 0;
void solve(){
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;
 
    string t = s;
    reverse(t.begin(), t.end());

    if(m == 0 || n == 1){
        cout << (s >= t ? "No" : "Yes") << endl;
    }
    else{
        vector<int> a(26);
        for(int i = 0; i < n; i++){
            a[s[i] - 'a']++;
        }

        int x = 0;
        for(int i = 0; i < 26; i++){
            if(a[i]){
                x++;
            }
        }
        cout << (x > 1 ? "Yes" : "No") << endl;
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

## B - Serval and Final MEX ##

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

    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }  

    vector<vector<int>> b;
    while(1){
        int flag = 0;
        for(int i = 0; i < a.size(); i++){
            if(!a[i]){
                if(i && !a[i - 1]){
                    a[i - 1] = 1;
                    a.erase(a.begin() + i);
                    b.push_back({i - 1, i});
                    break;
                }
                else if(i + 1 < a.size() && !a[i + 1]){
                    a[i + 1] = 1;
                    a.erase(a.begin() + i);
                    b.push_back({i, i + 1});
                }
                else if(i){
                    a[i - 1] = 1;
                    a.erase(a.begin() + i);
                    b.push_back({i - 1, i});
                }
                else if(i + 1 < a.size()){
                    a[i + 1] = 1;
                    a.erase(a.begin() + i);
                    b.push_back({i, i + 1});
                }
                flag = 1;
            }
        }
        if(!flag){
            b.push_back({0, a.size() - 1});
            break;
        }
    }

    cout << b.size() << endl;
    for(int i = 0; i < b.size(); i++){
        cout << b[i][0] + 1 << " " << b[i][1] + 1 << "\n";
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

## C - Serval and The Formula ##

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
    ll x, y;
    cin >> x >> y;

    if(x == y){
        cout << -1 << endl;
    }
    else{
        if(x + y == (x ^ y)){
            cout << 0 << endl;
        }
        else{
            for(ll i = 1; i < 63; i++){
                if((1ll << i) - chmax(x, y) >= 0){
                    cout << (1ll << i) - chmax(x, y) << endl;
                    return;
                }
            }
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

## D - Serval and Kaitenzushi Buffet ##

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
    int n, k;
    cin >> n >> k;

    priority_queue<int, vector<int>, less<>> q;
    int a[n + 1];

    ll sum = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        q.push(a[i]);

        if((n - i + 1) % (k + 1) == 0){
            sum += q.top();
            q.pop();
        }
    }
    cout << sum << endl;
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

## E - Serval and Modulo  ##

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
int d[N * 10];

void solve(){
    int n;
    cin >> n;

    int a[n], b[n];
    ll A = 0, B = 0;

    for(int i = 0; i < n; i++){
        cin >> a[i];
        A += a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
        B += b[i];
    }

    auto get = [&](int mod) -> int{
        for(int i = 0; i < n; i++){
            d[a[i] % mod]++;
        }

        for(int i = 0; i < n; i++){
            d[b[i]]--;
            if(d[b[i]] < 0){
                d[b[i]] = 0;
                for(int j = 0; j < n; j++){
                    d[a[j] % mod] = 0;
                }
                return 0;
            }
        }

        for(int i = 0; i < n; i++){
            d[a[i] % mod] = 0;
        }
        return 1;
    };

    if(A == B){
        if(!get(11451411)){
            cout << -1 << "\n";
            return;
        }
        cout << 11451411 << "\n";
    }
    else{
        for(ll i = 1; i * i <= A - B; i++){
            if((A - B) % i == 0){
                if(get(i)){
                    cout << i << "\n";
                    return;
                }
                else if(i < N * 10 && get((A - B) / i)){
                    cout << (A - B) / i << "\n";
                    return;
                }
            }
        }
        cout << -1 << "\n";
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
