#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const ld pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = 1e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = (int)1e5;
 
void solve(){
    string s;
    cin >> s;

    if(s == "first"){
        int t;
        cin >> t;

        while(t--){
            int n, m;
            cin >> n >> m;

            int a[n][n], one = 0;
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    cin >> a[i][j];
                    one += a[i][j];
                }
            }

            vector<vector<int>> b, c;
            int b1 = 0, b2 = 0, c1 = 0, c2 = 0;

            for(int i = 0; i < n; i++){
                int cnt = 0;
                for(int j = 0; j < m; j++){
                    cnt += a[i][j];
                }
                b.push_back({cnt, i});
                
                if(cnt & 1){
                    b1 = 1;
                }
                else{
                    b2 = 1;
                }
            }

            for(int i = 0; i < m; i++){
                int cnt = 0;
                for(int j = 0; j < n; j++){
                    cnt += a[j][i];
                }
                c.push_back({cnt, i});
                
                if(cnt & 1){
                    c1 = 1;
                }
                else{
                    c2 = 1;
                }
            }

            auto print = [&](const vector<vector<int>>& a, int par) -> void{
                 for(int i = 0; i < a.size(); i++){
                    if(a[i][0] % 2 == par){
                        cout << a[i][1] + 1 << " ";
                        break;
                    }
                }
            };
 
            if(m){
                assert((b1 && c1) || (b2 && c2));
                if(b1 && c1){
                    print(b, 1);
                    print(c, 1);
                }
                else{
                    print(b, 0);
                    print(c, 0);
                }
            }
            else{
                assert((b1 && c2) || (b2 && c1));
                if(b1 && c2){
                    print(b, 1);
                    print(c, 0);
                }
                else{
                    print(b, 0);
                    print(c, 1);
                }
            }
        }
    }
    else{
        int t;
        cin >> t;

        while(t--){
            int n;
            cin >> n;

            int cnt = 0;
            for(int i = 0; i < 2 * n; i++){
                int x;
                cin >> x;
                cnt += x;
            }

            cout << !(cnt & 1) << "\n";
        }
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