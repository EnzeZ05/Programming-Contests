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
    int n = 8;
    vector<vector<int>> a;
    for(int i = 0; i < n; i++){
        int x, y, z;
        cin >> x >> y >> z;
        a.push_back({x, y, z});
    }

    auto calc = [&](int i, int j) -> ll{
        return (a[i][0] - a[j][0]) * (a[i][0] - a[j][0]) + (a[i][1] - a[j][1]) * (a[i][1] - a[j][1]) + (a[i][2] - a[j][2]) * (a[i][2] - a[j][2]);
    };

    map<ll, ll> mp;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mp[calc(i, j)]++;
        }
    }

    vector<ll> b, c = {8, 8, 24, 24};
    for(auto& [k, v] : mp){
        b.push_back(v);
    }
    sort(b.begin(), b.end());

    if(b == c){
        cout << "Yes" << "\n";
    }
    else{
        cout << "No" << "\n";
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
