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

const int N = 1e6 + 1, M = 2 * N;

void solve(){   
    int n, x, y;
    cin >> n >> y >> x;

    vector<vector<int>> a;
    a.push_back({1, n});
    a.push_back({n, 1});
    a.push_back({1, 1});
    a.push_back({n, n});

    int id = 0, min = (int)1e9;
    for(int i = 0; i < 4; i++){
        if(abs(a[i][0] - x) + abs(a[i][1] - y) < min){
            min = abs(a[i][0] - x) + abs(a[i][1] - y);
            id = i;
        }
    }

    if(id == 0){
        for(int i = 0; i < n - 1; i++){
            cout << "L";
        }
        for(int i = 0; i < n - 1; i++){
            cout << "D";
        }
        int dx = 1, dy = n;
        while(dx != x){
            cout << "R";
            dx++;
        }
        while(dy != y){
            cout << "U";
            dy--;
        }
    }
    else if(id == 1){
        for(int i = 0; i < n - 1; i++){
            cout << "R";
        }
        for(int i = 0; i < n - 1; i++){
            cout << "U";
        }
        int dx = n, dy = 1;
        while(dx != x){
            cout << "L";
            dx--;
        }
        while(dy != y){
            cout << "D";
            dy++;
        }
    }
    else if(id == 2){
        for(int i = 0; i < n - 1; i++){
            cout << "L";
        }
        for(int i = 0; i < n - 1; i++){
            cout << "U";
        }
        int dx = 1, dy = 1;
        while(dx != x){
            cout << "R";
            dx++;
        }
        while(dy != y){
            cout << "D";
            dy++;
        }
    }
    else if(id == 3){
        for(int i = 0; i < n - 1; i++){
            cout << "R";
        }
        for(int i = 0; i < n - 1; i++){
            cout << "D";
        }
        int dx = n, dy = n;
        while(dx != x){
            cout << "L";
            dx--;
        }
        while(dy != y){
            cout << "U";
            dy--;
        }
    }
    cout << "\n";
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
