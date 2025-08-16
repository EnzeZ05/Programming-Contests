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
 
void solve(){
    int n, k;
    cin >> n >> k;

    vector<vector<int>> a;
    for(int i = 0; i < n; i++){
        int t, l, w;
        cin >> t >> l >> w;
        a.push_back({t, l, w});
    }

    auto check = [&](ll mid) -> bool{
        ll t = k;

        for(int i = 0; i < n; i++){
            ll x = a[i][0], y = a[i][1], z = a[i][2];
            
            ll l = 0, r = (int)1e9 + 1;
            while(l < r){
                ll mmid = l + r >> 1;
                if(mmid * x + (mmid - 1) / y * z >= mid){
                    r = mmid;
                }
                else{
                    l = mmid + 1;
                }
            }
            if(l * x + (l - 1) / y * z > mid){
                l--;
            }
            t -= l;

            if(t <= 0){
                break;
            }
        }
        return t <= 0;
    };

    ll l = 0, r = INF; 
    while(l < r){
        ll mid = l + r >> 1;

        if(check(mid)){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }

    cout << l << "\n";
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
