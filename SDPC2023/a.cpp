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
    ll k;
    cin >> n >> k;

    map<ll, ll> mp;
    vector<ll> a;
    for(int i = 0; i < n; i++){
        int u, v;
        cin >> u >> v;
        mp[u] += v;

        a.push_back(u);
    }

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    if(mp[a[0]] > k * a[0]){
        cout << "No" << "\n";
    }
    else{
        for(int i = 1; i < a.size(); i++){
            mp[a[i]] += mp[a[i - 1]];
            if(a[i] * k < mp[a[i]]){
                cout << "No" << "\n";
                return;
            }
        }
        cout << "Yes" << "\n";
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
