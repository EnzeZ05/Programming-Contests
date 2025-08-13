#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = 1e18;

template <typename T>
T chmax(T a, T b){
    return a > b ? a : b;
} 

template <typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = 2e5 + 10, M = 2 * N;
 
void solve(){
    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    string t = "114514";

    auto DP = [&](string s) -> void{
        vector<vector<int>> dp1(n, vector<int>(2, (int)1e9)), dp2(n, vector<int>(2, -(int)1e9));
        if(s[n - 1] == '?'){
            dp1[n - 1][0] = dp1[n - 1][1] = 0;
            dp2[n - 1][0] = dp2[n - 1][1] = 0;
        }
        else{
            dp1[n - 1][s[n - 1] - '0'] = 0;
            dp2[n - 1][s[n - 1] - '0'] = 0;
        }

        for(int i = n - 2; i >= 0; i--){
            if(s[i] == '?'){
                if(s[i + 1] == '?'){
                    dp1[i][0] = chmin(dp1[i + 1][0], dp1[i + 1][1] + 1);
                    dp1[i][1] = chmin(dp1[i + 1][1], dp1[i + 1][0] + 1);
                    dp2[i][0] = chmax(dp2[i + 1][0], dp2[i + 1][1] + 1);
                    dp2[i][1] = chmax(dp2[i + 1][1], dp2[i + 1][0] + 1);
                }
                else if(s[i + 1] == '0'){
                    dp1[i][0] = chmin(dp1[i + 1][0], dp1[i + 1][1] + 1);
                    dp1[i][1] = chmin(dp1[i + 1][1], dp1[i + 1][0] + 1);
                    dp2[i][0] = chmax(dp2[i + 1][0], dp2[i + 1][1] + 1);
                    dp2[i][1] = chmax(dp2[i + 1][1], dp2[i + 1][0] + 1);

                }
                else{
                    dp1[i][0] = chmin(dp1[i + 1][0], dp1[i + 1][1] + 1);
                    dp1[i][1] = chmin(dp1[i + 1][1], dp1[i + 1][0] + 1);
                    dp2[i][0] = chmax(dp2[i + 1][0], dp2[i + 1][1] + 1);
                    dp2[i][1] = chmax(dp2[i + 1][1], dp2[i + 1][0] + 1);
                }
            }
            else if(s[i] == '0'){
                dp1[i][0] = chmin(dp1[i + 1][1] + 1, dp1[i + 1][0]);
                dp2[i][0] = chmax(dp2[i + 1][1] + 1, dp2[i + 1][0]);
            }
            else{  
                dp1[i][1] = chmin(dp1[i + 1][0] + 1, dp1[i + 1][1]);
                dp2[i][1] = chmax(dp2[i + 1][0] + 1, dp2[i + 1][1]);
            }
        }

        string S = s;
        if(dp1[0][s[0] - '0'] > k || dp2[0][s[0] - '0'] < k){
            return;
        }
        else{
            int cnt = 0;
            for(int i = 1; i < n; i++){
                int flag = 0;
                for(int j = 0; j <= 1; j++){
                    if(S[i] != '?' && S[i] - '0' != j){
                        continue;
                    }

                    int ddp = (S[i - 1] - '0') != j;
                    int l = dp1[i][j], r = dp2[i][j];
                    if(l > k - cnt - ddp || r < k - cnt - ddp){
                        continue;
                    }
                    S[i] = (char)('0' + j);
                    cnt += ddp;
                    flag = 1;
                    break;
                }
                if(!flag){
                    return;
                }
            }
            if(t == "114514" || S < t){
                t = S;
            }
        }
    };

    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            string ds = s;
            if(ds[0] == '?'){
                ds[0] = (char)('0' + i);
            }
            if(ds[n - 1] == '?'){
                ds[n - 1] = char('0' + j);
            }
            DP(ds);
        }
    }

    if(t == "114514"){
        cout << "Impossible" << "\n";
    }
    else{
        cout << t << "\n";
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
