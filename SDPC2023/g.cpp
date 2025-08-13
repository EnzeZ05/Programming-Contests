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

const int N = 3e5 + 10, M = 2 * N;

void solve(){
    int n;
    cin >> n;

    int a[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    map<ll, vector<ll>> mp;
    for(int i = 0; i < n; i++){
        mp[a[i] - i].push_back(a[i]);
    }

    for(auto& [k, v] : mp){
        sort(v.begin(), v.end(), greater<>());
    }

    ll sum = 0;
    for(auto& [k, v] : mp){
        for(int i = 1; i < v.size(); i += 2){
            if(v[i] + v[i - 1] > 0){
                sum += v[i] + v[i - 1];
            }
        }
    }
    cout << sum << "\n";
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
