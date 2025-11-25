#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const double pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = (ll)4e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = (int)1e6 + 1;
 
void solve(){ 
    int n, m;
    cin >> n >> m;

    map<string, string> mp;
    for(int i = 0; i < n; i++){
        string s, t;
        cin >> s >> t;
        mp[s] = t;
    }

    for(int i = 0; i < m; i++){
        string s;
        cin >> s;
        if(!mp.count(s)){
            cout << "NULL\n";
        }
        else{
            cout << mp[s] << "\n";
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