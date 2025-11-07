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

bool can(const string& s, const string& t, int K, vector<int>& id){
    int n = s.size();
    if(s[0] != t[0]){
        return false;
    }

    id.assign(n, 0);
    id[0] = 0;

    for(int i = 1; i < n; i++) {
        int L = chmax(0, chmax(id[i - 1], i - K));
        int j = L;
        for(; j <= i; j++){
            if(s[j] == t[i]){
                id[i] = j;
                break;
            }
        }
        if(j > i){
            return false; 
        }
    }
    return true;
}
 
void solve(){
    int n, k;
    cin >> n >> k;

    string s, t;
    cin >> s >> t;

    if(s == t){
        cout << 0 << "\n";
        return;
    }

    vector<string> op;
    vector<int> id(n), best(n);

    int l = 0, r = k, K = -1;
    while(l <= r){
        int mid = l + r >> 1;
        if(can(s, t, mid, id)){
            r = mid - 1;
            best = id;
            K = mid;
        }
        else{
            l = mid + 1;
        }
    }

    if(s[0] != t[0] || K == -1 || K > k){
        cout << -1 << "\n";
        return;
    }

    cout << K << "\n";
    for(int i = 1; i <= K; i++){
        string c(n, '#');
        for(int j = 0; j < n; j++){
            int idx = chmax(best[j], j - i);
            c[j] = s[idx];
        }
        cout << c << "\n";
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