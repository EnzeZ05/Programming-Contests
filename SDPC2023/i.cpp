#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
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

const int N = 3e5 + 10, M = 2 * N;

void solve(){
    int A, B;
    cin >> A >> B;

    vector<vector<int>> a, b;
    a.push_back({0});
    a.push_back({1, 4});
    a.push_back({2, 5, 8});
    a.push_back({3, 6, 9, 12});

    b.push_back({0});
    b.push_back({2, 3, 5, 6});
    b.push_back({4, 5, 6, 7, 8, 9, 10, 11, 12});
    b.push_back({6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});

    for(int i = 0; i <= 3; i++){
        for(int j = 0; j < a[i].size(); j++){
            if(a[i][j] != A){
                continue;
            }
            for(int k = 0; k < b[3 - i].size(); k++){
                if(b[3 - i][k] == B){
                    cout << "Yes" << "\n";
                    return;
                }
            }
        }
    }
    cout << "No" << "\n";
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
