#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
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

const int N = 1e6 + 1, M = 2 * N;
 
void solve(){
    int n, m;
    cin >> n >> m;

    map<string, int> mp;
    for(int i = 0; i < m; i++){
        string s, t;
        cin >> s >> t;
        mp[t]++;
    }

    int dp[n + 1], ndp[n + 1];
    memset(dp, 0, sizeof dp);
    memset(ndp, 0, sizeof ndp);

    dp[0] = ndp[0] = 1;
    string s;
    cin >> s;
    s = "#" + s;

    int flag = 0, ans = 0;

    for(int i = 1; i <= n; i++){
        for(int j = i; j >= chmax(1, i - 4); j--){
            string t = s.substr(j, i - j + 1);

            if(j){
                if(mp.count(t)){
                    dp[i] = (dp[i] + dp[j - 1] * mp[t] % 128) % 128;
                    ndp[i] = chmin(2, ndp[i] + ndp[j - 1] * (mp[t] > 1 ? 2 : 1));
                }
            }
        }
    }
    
    if(!ndp[n]){
        cout << "nonono" << endl;
    }
    else if(ndp[n] == 1){
        cout << "happymorsecode" << endl;
    }
    else{
        cout << "puppymousecat" << " " << dp[n] << endl;
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