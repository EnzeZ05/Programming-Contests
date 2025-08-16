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
    ll p, a, b;
    cin >> p >> a >> b;

    ll q, c, d;
    cin >> q >> c >> d;

    ll m, t;
    cin >> m >> t;


    if(m < p){
        cout << m << "\n";
        return;
    }

    if(b == 0 && d == 0){
        ll l = 0, r = (ll)1e9;
        while(l < r){
            ll mid = l + r >> 1;

            if(a * mid + c * mid > t || mid * p > m + mid * q){
                r = mid;
            }
            else{
                l = mid + 1;
            }
        }

        if(a * l + c * l > t || l * p > m + l * q){
            l--;
        }

        cout << m + l * q - l * p << "\n";
        return;
    }

    while(t){
        ll x = m / p;
        if(a * x + b + c * x + d > t){
            x = (t - b - d) / (a + c);
            if(x <= 0){
                break;
            }
            else{
                m -= x * p;
                t -= a * x + b + c * x + d;
            }
        }
        else{
            m -= x * p;
            t -= a * x + b + c * x + d;
        }

        if(x <= 0){
            break;
        }
        m += x * q;
    }
    cout << m << "\n";
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
