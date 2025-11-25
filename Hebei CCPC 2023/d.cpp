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

int a[N];

void solve(){ // substact some numbers (minimized) so they xor to 0
    int n;
    cin >> n;

    int nim = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        nim ^= a[i];
    }

    int min = (int)1e9;
    for(int i = 0; i < n; i++){
        min = chmin(min, abs(a[i] - (a[i] ^ nim)));

        nim ^= a[i];
        for(int j = 0; j < n; j++){
            if(i == j){
                continue;
            }
            min = chmin(min, a[i] + abs(a[j] - (a[j] ^ nim)));
        }
        nim ^= a[i];
    }
    cout << min << "\n";
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