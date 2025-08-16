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

template <typename T>
struct Fenwick{
    int n;
    vector<T> a;
    
    Fenwick(int n = 0){
        init(n);
    }
    
    void init(int len){
        n = len;
        a.assign(n + 1, T{});
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
 
void solve(){
    int n, k;
    cin >> n >> k;

    vector<vector<int>> a;
    vector<int> b;

    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        a.push_back({l, r});
        b.push_back(l);
        b.push_back(r);
    }

    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    auto cmp = [&](const vector<int>& a, const vector<int>& b) -> bool{
        return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
    };
    sort(a.begin(), a.end(), cmp);

    Fenwick<ll> fw(2 * n + 2);
    ll dp[n];

    for(int i = 0; i < a.size(); i++){
        int l = lower_bound(b.begin(), b.end(), a[i][0]) - b.begin() + 2;
        int r = lower_bound(b.begin(), b.end(), a[i][1]) - b.begin() + 2;

        ll ndp = chmax(0ll, k - (i - fw.query(l - 1)));
        dp[i] = (i ? dp[i - 1] : 1) * ndp % mod;
        fw.add(r, 1);
    }
    cout << dp[n - 1] << "\n";
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
