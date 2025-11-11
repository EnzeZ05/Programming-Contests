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

            int a[n][n];
            for(int i = 0; i < n; i++){
                string s;
                cin >> s;
                for(int j = 0; j < n; j++){
                    a[i][j] = s[j] - '0';
                }
            }

            vector<vector<int>> b, c;

            for(int i = 0; i < n; i++){
                int cnt = 0;
                for(int j = 0; j < n; j++){
                    cnt += a[i][j];
                }
                b.push_back({cnt, i + 1});
            }

            for(int i = 0; i < n; i++){
                int cnt = 0;
                for(int j = 0; j < n; j++){
                    cnt += a[j][i];
                }
                c.push_back({cnt, i + 1});
            }

            sort(b.begin(), b.end());
            sort(c.begin(), c.end());

            const int N = 1001;
            vector<bitset<N>> B(n), C(n);

            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    B[i] |= a[i][j] << j; 
                }
            }

            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    C[i] |= a[j][i] << j; 
                }
            }

            if(!m){
                assert(c.back()[0] >= b[0][0]);
                if(c.back()[0] > b[0][0]){
                    cout << b[0][1] << " " << c.back()[1] << "\n";
                }
                else{
                    for(int i = 0; i < n; i++){
                        for(int j = 0; j < n; j++){
                            if((B[i] ^ C[j]).count() == 0){
                                cout << i + 1 << " " << j + 1 << "\n";
                                goto entry;
                            }
                        }
                    }     
                    assert(false);
                }
            }
            else{
                assert(b.back()[0] >= c[0][0]);
                if(b.back()[0] > c[0][0] || (b.back()[0] == n && c[0][0] == n)){
                    cout << b.back()[1] << " " << c[0][1] << "\n";
                }
                else{
                    for(int i = 0; i < n; i++){
                        for(int j = 0; j < n; j++){
                            if((B[i] ^ C[j]).count()){
                                cout << i + 1 << " " << j + 1 << "\n";
                                goto entry;
                            }
                        }
                    }
                    assert(false);
                }
            }
            entry:;
        }
    }
    else{
        int t;
        cin >> t;

        while(t--){
            int n;
            cin >> n;

            int r = 0, c = 0;
            const int N = 1001;
            bitset<N> a, b;

            for(int i = 0; i < 2; i++){
                string s;
                cin >> s;
                if(i == 0){
                    r = count(s.begin(), s.end(), '1');
                    for(int j = 0; j < n; j++){
                        a |= (s[j] - '0') << j;
                    }
                }
                else{
                    c = count(s.begin(), s.end(), '1');
                    for(int j = 0; j < n; j++){
                        b |= (s[j] - '0') << j;
                    }
                }
            }

            if(r == c){
                if(r == n && c == n){
                    cout << 1 << "\n";
                }
                else{
                    cout << ((a ^ b).count() > 0) << "\n";
                }
            }
            else{
                cout << (r > c) << "\n";
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
