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
