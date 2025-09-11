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
    int n, m;
    cin >> n >> m;

    if(n & 1){
        n -= 1;
    }
    if(m & 1){
        m -= 1;
    }

    if(n == 0){
        if(m % 4 == 2){
            m -= 2;
        }
        if(m == 4 || m == 8){
            cout << "LLLL\n";
        }
        else{
            cout << "LRL";
            for(int i = 0; i < (m - 6) / 2; i++){
                cout << (i % 2 == 0 ? 'L' : 'R');
            }
            cout << "LRL";
            for(int i = 0; i < (m - 6) / 2; i++){
                cout << (i % 2 == 0 ? 'L' : 'R');
            }
        }
    }
    else if(m % 4 == 0){
        for(int i = 0; i < m / 2 - 1; i++){
            cout << (i % 2 == 0 ? 'R' : 'L');
        }
        cout << 'R';
        for(int i = 0; i < n / 2; i++){
            cout << 'S';
        }
        for(int i = 0; i < m / 2 - 1; i++){
            cout << (i % 2 == 0 ? 'R' : 'L');
        }
        cout << 'R';
        for(int i = 0; i < n / 2; i++){
            cout << 'S';
        }
    }
    else{
        if(n == 2){
            cout << "SR";
            for(int i = 0; i < m / 2; i++){
                cout << (i % 2 == 0 ? 'R' : 'L');
            }
            cout << "RS";
            for(int i = 0; i < m / 2 - 2; i++){
                cout << (i % 2 == 0 ? 'R' : 'L');
            }
        }
        else{
            int k = m - 4;
            for(int i = 0; i < k / 2; i++){
                cout << (i % 2 == 0 ? 'R' : 'L');
            }
            cout << 'L';
            for(int i = 0; i < (n - 4) / 2; i++){
                cout << 'S';
            }
            cout << "RR";
            for(int i = 0; i < (n - 4) / 2 + 2; i++){
                cout << 'S';
            }
            cout << "RS";
            for(int i = 0; i < k / 2 - 1; i++){
                cout << (i % 2 == 0 ? 'L' : 'R');
            }
            cout << "RS"; 
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
