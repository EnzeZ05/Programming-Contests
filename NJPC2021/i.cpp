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
    ll H;
    int n, m;
    cin >> H >> n;

    vector<vector<int>> a;
    a.push_back({0, 0, 1});

    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        a.push_back({x, y, 1});
    }

    cin >> m;
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        a.push_back({x, y, 2});
    }

    sort(a.begin(), a.end());
    unordered_map<ll, int> dp;

    ll z = 2 * H;
    
    for(int i = a.size() - 1; i >= 0; i--){
        int x = a[i][0], y = a[i][1], op = a[i][2];
        if(op == 1){
            dp[(x + y) % z] = dp[(z + x - y) % z] = chmax(dp[(x + y) % z], dp[(z + x - y) % z]);
        }
        else{
            dp[(x + y) % z] += 1;
            dp[(z + x - y) % z] += 1;
        }
    }

    cout << dp[0] << "\n";
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
