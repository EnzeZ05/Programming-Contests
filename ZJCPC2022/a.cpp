#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const ld  pi  = 3.14159265358979323846;
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

const int N = 2e5 + 1, M = 2 * N;

void solve(){ 
    int a, b;
    cin >> a >> b;

    if(a > b){
        if((a - b) % 2 == 0){
            cout << 1 << endl;
        }
        else{
            cout << 2 << endl;
        }
    }
    else if(b > a){
        if((b - a) % 2){
            cout << 1 << endl;
        }
        else{
            int min = b - a;
            for(int i = 1; i * i <= b - a; i++){
                if((b - a) % i == 0){
                    if(i % 2){
                        min = chmin(min, (b - a) / i);
                    }

                    int x = (b - a) / i;
                    if(x % 2){
                        min = chmin(min, (b - a) / x);
                    }
                }
            }
            cout << chmin(3, min) << endl;
        }
    }
    else{
        cout << 0 << endl;
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
