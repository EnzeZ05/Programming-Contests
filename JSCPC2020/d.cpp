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

struct Sieve{
    int n, cnt;
    vector<int> p, p_min, mu;
    Sieve(int _n) : n(_n) {
        p_min.resize(n + 1, 0);
        mu.resize(n + 1, 0);
        init();
    }

    void init(){
        cnt = 0;
        mu[1] = 1;
        for(int i = 2; i <= n; ++i) {
            if(!p_min[i]) {
                mu[i] = -1;
                p.push_back(i);
            }

            for(int pr : p) {
                if(i * pr > n) break;
                p_min[i * pr] = pr;  
                if(i % pr == 0) {
                    break;
                }
                mu[i * pr] = -mu[i];
            }
        }
    }
};

vector<int> a[101];
 
void solve(){
    int n;
    cin >> n;

    Sieve sv(N);
    vector<int> b;
    for(int i = 1; i <= N; i++){
        b.push_back(i);
    }

    int id = 0;
    while(!b.empty()){
        vector<int> c;
        for(int i = 0; i < b.size(); i++){
            if(i + 1 == 1 || !sv.p_min[i + 1]){
                a[id].push_back(b[i]);
            }
            else{
                c.push_back(b[i]);
            }
        }
        b = c;
        id++;
    }

    for(int i = 0; i < n; i++){
        int op, m, k;
        cin >> op >> m >> k;

        if(op == 1){
            int len = 0;
            for(int j = 0; j < id; j++){
                auto it = lower_bound(a[j].begin(), a[j].end(), k);
                if(it != a[j].end() && *it == k){
                    cout << len + (it - a[j].begin()) + 1 << endl;
                    break;
                }
                len += upper_bound(a[j].begin(), a[j].end(), m) - a[j].begin();
            }
        }
        else{
            int len = 0;
            for(int j = 0; j < id; j++){
                int cur = upper_bound(a[j].begin(), a[j].end(), m) - a[j].begin();
                if(len + cur >= k){
                    cout << a[j][k - len - 1] << endl;
                    break;
                }
                len += cur;
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