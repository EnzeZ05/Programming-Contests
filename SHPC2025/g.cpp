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
    int n;
    cin >> n;

    int id = n + 1;
    while(1){
        int flag = 0;
        for(int i = 2; i * i <= id; i++){
            if(id % i == 0){
                flag = 1;
            }
        }
        if(!flag){
            break;
        }
        id++;
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cout << i * id + j << " ";
        }
        cout << endl;
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
