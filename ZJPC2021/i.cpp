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

const int N = 2e5 + 10, M = 2 * N;

void solve(){
    // 1, 4 -> (1, 2)
    // 2, 5 -> (1, 3)
    // 3, 6 -> (2, 3)
    // 8

    int n = 6;
    vector<int> a;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;

        if(s == "true"){
            a.push_back(1);
        }
        else{
            a.push_back(0);
        }
    }

    int A = a[0] ^ a[3], B = a[1] ^ a[4], C = a[2] ^ a[5];
    int cnt = 0;
    if(A + B + C == 0){
        cnt = 8;
    } 
    else if(A + B + C == 1){
        cnt = 6;
    }
    else if(A + B + C == 2){
        cnt = 5;
    }
    else{
        cnt = 4;
    }
    cout << cnt << "\n";
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
