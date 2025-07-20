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

ll a[501][501], b[501][501], c[501][501][2], d[501][501][2], dp[501][501], v[501][501];
int dirx[4] = {0, 0, 1, -1}, diry[4] = {1, -1, 0, 0};

void solve(){
    int n, m, xs, ys, xt, yt;
    cin >> n >> m >> xs >> ys >> xt >> yt;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> b[i][j];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j < m; j++){
            cin >> c[i][j][0];
            c[i][j + 1][1] = c[i][j][0];
        }
    }

    for(int i = 1; i < n; i++){
        for(int j = 1; j <= m; j++){
            cin >> d[i][j][0];
            d[i + 1][j][1] = d[i][j][0];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            dp[i][j] = INF;
            v[i][j] = 0;
        }
    }

    priority_queue<vector<ll>, vector<vector<ll>>, greater<>> q;
    q.push({0, xs, ys});
    dp[xs][ys] = 0;

    while(!q.empty()){
        auto p = q.top();
        q.pop();

        int x = p[1], y = p[2];
        ll t = p[0];

        if(v[x][y]){
            continue;
        }
        v[x][y] = 1;

        for(int i = 0; i < 4; i++){
            int dx = dirx[i] + x, dy = diry[i] + y;
            if(dx <= 0 || dy <= 0 || dx > n || dy > m){
                continue;
            }

            ll k = a[x][y] + b[x][y], rem = t % k;

            if(i < 2){
                ll ndp = (rem >= a[x][y] ? 0 : a[x][y] - rem); 
                if(dp[dx][dy] > dp[x][y] + ndp + c[x][y][i]){
                    dp[dx][dy] = dp[x][y] + ndp + c[x][y][i];
                    q.push({dp[dx][dy], dx, dy});
                }
            }
            else{   
                ll ndp = (rem < a[x][y] ? 0 : k - rem);
                if(dp[dx][dy] > dp[x][y] + ndp + d[x][y][i - 2]){
                    dp[dx][dy] = dp[x][y] + ndp + d[x][y][i - 2];
                    q.push({dp[dx][dy], dx, dy});
                }
            }
        }
    }

    cout << dp[xt][yt] << endl;
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