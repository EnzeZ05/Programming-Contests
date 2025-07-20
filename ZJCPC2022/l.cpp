#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const ld  pi  = 3.14159265358979323846;
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

const int N = 2e5 + 1, M = 2 * N;

void solve(){ 
    int n;
    cin >> n;

    vector<double> a(n);
    double exp = 0;
    int max = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        exp += a[i];
    }
    sort(a.begin(), a.end());
    max = n - (upper_bound(a.begin(), a.end(), exp / n) - a.begin());

    for(int i = n - 1; i >= 1; i--){
        exp -= a[i];
        double A = exp / i;
        max = chmax(max, i - (int)(upper_bound(a.begin(), a.end(), A) - a.begin()));
    }
    cout << max << endl;
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
