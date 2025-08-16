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
    string s;
    cin >> s;

    if(s[0] == s.back()){
        cout << 0 << "\n";
    }
    else{
        for(int i = 0; i < s.size() - 1; i++){
            if(s[i] == s[i + 1]){
                cout << i + 1 << "\n";
                return;
            }
        }
        cout << -1 << "\n";
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
