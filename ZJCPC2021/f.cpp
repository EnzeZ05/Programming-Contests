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
    int n, m;
    cin >> n >> m;

    if(m % n == 0){
        cout << 0 << "\n";
    }
    else if(n > m){
        cout << n - m << "\n";
    }
    else{
        int ans = (int)1e9;
        for(int i = 1; i <= sqrt(n) + 1; i++){
            int t = (m + i - 1) / i;
            ans = chmin(ans, n - i + t * i - m);

            if(t <= n){
                ans = chmin(ans, n - t + t * i - m);
            }
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
