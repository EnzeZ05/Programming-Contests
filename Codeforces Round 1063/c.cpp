#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const ld pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = 1e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}
 
void solve(){
    int n;
    cin >> n;

    int a[2][n], minl[n], maxl[n], minr[n], maxr[n];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        minl[i] = minr[i] = (int)1e9;
    }
    minl[0] = a[0][0];
    minr[n - 1] = a[1][n - 1];

    maxl[0] = a[0][0];
    maxr[n - 1] = a[1][n - 1];

    for(int i = 1; i < n; i++){
        minl[i] = chmin(minl[i - 1], a[0][i]);  
        maxl[i] = chmax(maxl[i - 1], a[0][i]);
    }

    for(int i = n - 2; i >= 0; i--){
        minr[i] = chmin(minr[i + 1], a[1][i]);
        maxr[i] = chmax(maxr[i + 1], a[1][i]);
    }

    vector<int> best(2 * n + 2, 0);

    for(int i = 0; i < n; i++){
        int ml = chmin(minl[i], minr[i]);
        int mr = chmax(maxl[i], maxr[i]);
        best[mr] = chmax(best[mr], ml);
    }

    ll ans = 0, run = 0;
    for(int i = 1; i <= 2 * n; i++){
        run = chmax(run, (ll)best[i]);
        ans += run;
    }
    cout << ans << "\n";
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