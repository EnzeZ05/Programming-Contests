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

void solve(){
    int n;
    cin >> n;

    ll a[n + 1];
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    ll p[n + 1];
    p[0] = 0;

    for(int i = 1; i <= n; i++){
        p[i] = p[i - 1] + a[i];
    }
    sort(p + 1, p + n);

    ll acc = 0;
    for(int i = n; i >= 1; i--){
        acc += p[n - i];
        cout << (n - i + 1) * p[n] - acc << " \n"[i == 1]; 
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
