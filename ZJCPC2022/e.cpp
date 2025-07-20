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
double dp[1001][10][10], ndp[10];

void solve(){ 
    int n, H, S;
    cin >> n >> H >> S;

    vector<double> p(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> p[i];
        p[i] /= 100;
    }

    int k;
    cin >> k;
    vector<int> t(n + 1);
    for(int i = 0; i < k; i++){
        int x;
        cin >> x;
        t[x] = 1;
    }

    int t1, t2;
    cin >> t1 >> t2;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= H; j++){
            for(int k = 0; k <= S; k++){
                dp[i][j][k] = INF;
            }
        }
    }

    if(t1 >= t2 || !S){
        for(int i = n; i >= 1; i--){
            for(int j = 2; j <= H; j++){
                if(j > 2){
                    dp[i][j][S] = 1 + p[i] * dp[i + 1][j][S] + (1 - p[i]) * dp[i][j - 1][S];
                }
                else{
                    dp[i][j][S] = dp[i + 1][j][S] + (1 - p[i]) * t2 / p[i] + 1 / p[i];
                }
            }
        }
    }
    else{
        for(int i = 1; i <= H; i++){
            for(int j = 0; j <= S; j++){
                dp[n + 1][i][j] = 0;
            }
        }

        for(int i = n; i >= 1; i--){
            if(t[i]){ 
                double _[10];
                for(int j = 0; j < 10; j++){
                    _[j] = INF;
                }
                for(int j = 2; j <= H; j++){ 
                    ndp[j] = dp[i + 1][j][S] + (1 - p[i]) * t1 / p[i] + 1 / p[i];
                    for(int k = 2; k < j; k++){
                        ndp[k] = ndp[j] + (j - k) * t1; 
                    }
                    for(int k = j + 1; k <= H; k++){ 
                        ndp[k] = 1 + p[i] * dp[i + 1][k][S] + (1 - p[i]) * ndp[k - 1];
                    }
                    for(int k = 2; k <= H; k++){
                        _[k] = chmin(_[k], ndp[k]);
                    }
                }

                for(int j = 2; j <= H; j++){
                    for(int k = 0; k <= S; k++){
                        dp[i][j][k] = _[j];
                    }
                }
            }
            else{
                for(int j = 2; j <= H; j++){
                    if(j == 2){
                        for(int k = 0; k <= S; k++){
                            if(k == 0){
                                dp[i][j][0] = dp[i + 1][j][0] + (1 - p[i]) * t2 / p[i] + 1 / p[i];
                            }
                            else{
                                dp[i][j][k] = p[i] * dp[i + 1][j][k] + (1 - p[i]) * (dp[i][j][k - 1] + t1) + 1; 
                            }
                        }
                    }
                    else{
                        for(int k = 1; k <= S; k++){
                            dp[i][j][k] = p[i] * dp[i + 1][j][k] + (1 - p[i]) * dp[i][j - 1][k] + 1;
                        }
                    }
                }       
            }
        }
    }
    cout << setprecision(20) << dp[1][H][S] << endl;
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
