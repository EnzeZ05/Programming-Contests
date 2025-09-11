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

const int N = 2e5 + 1, M = 2 * N;

void solve(){
    int a, b, c;
    cout << "1 0 0\n" << flush;
    cin >> a;

    cout << "0 1 0\n" << flush;
    cin >> b;

    cout << "0 0 1\n" << flush;
    cin >> c;

    int abc;
    cout << "1 1 1\n" << flush;
    cin >> abc;

    int abbccc;
    cout << "1 2 3\n" << flush;
    cin >> abbccc;

    if(a + b + c == abc || a + b + b + c + c + c == abbccc){
        cout << a << " " << b << " " << c << "\n" << flush;
    }
    else{
        if(abc - b - c == abbccc - b - b - c - c - c){
            cout << abc - b - c << " " << b << " " << c << "\n" << flush;
        }
        else{
            if(abc - a == (abbccc - a - c) / 2 && (abbccc - a - c) % 2 == 0){
                cout << a << " " << abc - a - c << " " << c << "\n" << flush;  
            }
            else{
                cout << a << " " << b << " " << abc - a - b << "\n" << flush;
            }
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
