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

const int N = 2e5 + 10, M = 2 * N;

void solve(){
    int n, a, b;
    cin >> n >> a >> b;

    cout << "Yes" << "\n";
    if(n == 1){
        cout << 0 << "\n";
    }
    else{
        int x1 = a, y1 = b, l = 1, r = -1;
        cout << n - 1 << "\n";
        while(x1 > 1 && y1 < n){
            x1--, y1++;
            cout << x1 << " " << y1 << " " << l << " " << r << "\n";
            l++, r--;
        }

        int x2 = a, y2 = b;
        l = -l, r = -r;

        while(x2 < n && y2 > 1){
            x2++, y2--;
            cout << x2 << " " << y2 << " " << l << " " << r << "\n";
            l--, r++;
        }

        int x3 = chmin(x1, x2), y3 = chmin(y1, y2);
        l = -l;

        while(x3 > 1 && y3 > 1){
            x3--, y3--;
            cout << x3 << " " << y3 << " " << l << " " << r << "\n";
            l++, r++;
        }

        int x4 = chmax(x1, x2), y4 = chmax(y1, y2);
        l = -l, r = -r;
        while(x4 < n && y4 < n){
            x4++, y4++;
            cout << x4 << " " << y4 << " " << l << " " << r << "\n";
            l--, r--;
        }
    }
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
