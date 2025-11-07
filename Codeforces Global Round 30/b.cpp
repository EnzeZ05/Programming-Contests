#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const ld pi = 3.14159265358979323846;
const int mod = (int)1e9 + 7;
const ll INF = 1e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = (int)2e5 + 1, M = N * 10;
 
void solve(){
    int n;
    cin >> n;

    int a[n];
    
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a, a + n);

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if((a[j] % a[i]) % 2 == 0){
                cout << a[i] << " " << a[j] << "\n";
                return;
            }
        }
    }
    cout << -1 << "\n";
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