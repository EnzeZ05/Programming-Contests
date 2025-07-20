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
    string s;
    cin >> s;

    string t = s;
    int id = 1;
    for(int i = 2; i < s.size(); i++){
        if(s[i - 2] == 'c' && s[i - 1] == 'j' && s[i] == 'b'){
            t.insert(t.begin() + i + id, ',');
            id++;
        }
    }
    cout << t << endl;
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
