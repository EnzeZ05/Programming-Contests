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
    int n, m, x;
    cin >> n >> m >> x;

    int cnt = 0;
    for(int i = 0; i < n; i++){
        int y;
        cin >> y;
        if(y >= x){
            cnt++;
        }
    }

    for(int i = 0; i < m; i++){
        int y;
        cin >> y;
        if(y <= x){
            cnt++;
        }
    }
    cout << cnt << endl;
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
