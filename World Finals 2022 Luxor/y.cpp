#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
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

const int N = 1e6 + 1, M = 2 * N;

void solve(){
    string s;
    cin >> s;

    if(count(s.begin(), s.end(), '0') == s.size() || count(s.begin(), s.end(), '1') == s.size()){
        cout << s[0] << "\n";
    }
    else if(s[0] != s.back()){
        cout << s[0] << s.back() << "\n";
    }
    else{
        cout << s[0] << (s[0] == '1' ? '0' : '1') << s.back() << "\n";
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
