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

struct P{
    int x, y, op;
};

void solve(){ 
    int n;
    cin >> n;

    vector<P> a;

    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        a.push_back({x, y, 1});
    }

    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    a.push_back({sx, sy, 0});
    a.push_back({tx, ty, 0});

    double v1, v2;
    cin >> v1 >> v2;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> q;
    vector<double> dp(n + 3, INF);
    q.push({0, n});
    dp[n] = 0;

    vector<int> v(n + 2);
    while(!q.empty()){
        auto p = q.top();
        q.pop();

        int u = p.second;
        if(v[u]){
            continue;
        }
        v[u] = 1;
        int x = a[u].x, y = a[u].y;
        for(int i = 0; i < a.size(); i++){
            int dx = a[i].x, dy = a[i].y;
            double d = p.first, cur = sqrt((dx - x) * 1.0 * (dx - x) + (dy - y) * 1.0 * (dy - y));

            if(a[u].op == 0){
                d += cur / v1;
            }
            else{
                if(v2 * 3 >= cur){
                    d += cur / v2;
                }
                else{
                    d += 3 + (cur - v2 * 3) / v1;
                }
            }
            if(dp[i] > d){
                dp[i] = d;
                q.push({dp[i], i});
            }
        }
    }

    cout << setprecision(20) <<  dp[n + 1] << endl;
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
