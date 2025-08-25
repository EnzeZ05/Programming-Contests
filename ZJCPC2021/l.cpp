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

vector<int> Z(const string& s){
    int n = s.length();
    vector<int> z(n); 
    z[0] = n;
 
    for(int i = 1, c = 1, r = 1, len; i < n; i++){
        len = r > i ? chmin(r - i, z[i - c]) : 0;
        while(i + len < n && s[i + len] == s[len]){
            len++;
        }
        if(i + len > r){
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
    return z;
}

void solve(){
    int n;
    cin >> n;

    string t;
    cin >> t;

    if(n == 1){
        cout << "Correct" << "\n";
    }
    else{
        vector<int> z = Z(t);
        for(int i = 1; i < z.size(); i++){
            if(z[i]){
                cout << "Wrong Answer" << "\n";
                return;
            }
        }
        cout << "Correct" << "\n";
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
