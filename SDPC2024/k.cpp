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
    int n;
    cin >> n;

    cout << "Yes" << "\n";
    int a[n][n];

    a[0][0] = 1, a[0][1] = 2;
    a[1][0] = 3, a[1][1] = 4;

    int r = 2, c = 2, id = 5;
    for(int i = n - 2; i > 0; i--){
        for(int j = 0; j < c; j++){
            a[j][c] = id;
        }
        ++id;
        for(int j = 0; j < r + 1; j++){
            a[r][j] = id;
        }
        ++id, ++r, ++c;
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << a[i][j] << " \n"[j == n - 1];
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
