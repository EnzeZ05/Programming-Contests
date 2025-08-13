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
 
void solve(){   
    int n;
    cin >> n;

    ll a[n], f1 = 0, f2 = 0, sum = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] < 0){
            f1 = 1;
        }
        if(a[i] > 0){
            f2 = 1;
        }
        sum += abs(a[i]);
    }

    if(n == 1){
        cout << a[0] << "\n";
    }
    else if(f1 && f2){
        cout << sum << "\n";
    }
    else if(f2){
        ll max = 0;
        for(int i = 0; i < n; i++){
            if(a[i] < a[(i + 1) % n]){
                max = chmax(max, sum - a[i] - a[(i + 1) % n] + abs(a[i] - a[(i + 1) % n]));
            }
        }

        if(max == 0){
            max = sum - a[0] - a[1];
        }
        cout << max << "\n";
    }
    else{
        ll max = 0;
        for(int i = 0; i < n; i++){
            if(a[i] > a[(i + 1) % n]){
                max = chmax(max, sum + a[i] + a[(i + 1) % n] + abs(a[i] - a[(i + 1) % n]));
            }
        }

        if(max == 0){
            max = sum + a[0] + a[1];
        }
        cout << max << "\n";
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
