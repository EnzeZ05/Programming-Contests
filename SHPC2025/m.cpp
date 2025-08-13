#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
const int mod = (int)1e9 + 7;
const ll  INF = 1e18;

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
    int n;
    ll x, y;
    cin >> n >> x >> y;

    ll a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int max = *max_element(a, a + n);
    ll ans = 0;

    while(max){
        ll sum = 0;
        for(int i = 0; i < n; i++){
            ans += a[i] % 2 * x;
            sum += a[i] / 2;
            a[i] /= 2;
        }

        max = *max_element(a, a + n);
        if(sum == 0 || x <= y / sum){
            ans += sum * x;
        }
        else{
            ans += y;
        }
    }
    cout << ans << endl;
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
