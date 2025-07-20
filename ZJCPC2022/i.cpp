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

vector<int> manacher(string s){
    char b[s.length() * 2 + 1];
    int k = 0;
    
    b[k++] = '^', b[k++] = '#';
    for(int i = 0; i < s.length(); i++){
        b[k++] = s[i], b[k++] = '#';
    }
    b[k++] = '$';
    
    vector<int> a(k);
    
    int mid = 0, r = 0;
    for(int i = 1; i < k; i++){
        a[i] = (i < r ? chmin(a[(mid << 1) - i], r - i) : 1);
        
        while(b[i - a[i]] == b[i + a[i]]){
            a[i]++;
        }
        if(i + a[i] > r){
            r = i + a[i];
            mid = i;
        }
    }
    return a;
} // mapping: i -> 2 * i + 2 

void solve(){ 
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    auto z = manacher(s);
    // for(auto Z : z){
    //     cout << Z << " ";
    // }
    // cout << endl;

    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        l--, r--;

        if(z[l + r + 2] >= (r - l + 1) || (r - l + 1) % 2 == 0){
            cout << "Budada" << endl;
        }
        else{
            cout << "Putata" << endl;
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
