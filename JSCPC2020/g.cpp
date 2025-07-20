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

// const int N = 1e6 + 1, M = 2 * N;

const int N = 3;
int n;

void mul(ll c[], ll a[], ll b[][N]){
    ll t[N] = {0};
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            t[i] = (t[i] + a[j] * b[j][i] % mod) % mod;
        }
    }
    memcpy(c, t, sizeof t);
}

void mul(ll c[][N], ll a[][N], ll b[][N]){
    ll t[N][N] = {0};
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                t[i][j] = (t[i][j] + a[i][k] * b[k][j]% mod) % mod;
            }
        }
    }
    memcpy(c, t, sizeof t);  
}

void solve(){
    int m;
    cin >> n >> m;

    /*
        [2, 4, 6, 10, 16, 26, 42, 68, 110, 178]
        [4, 16, 36, 100, 256, 676, 1764, 4624, 12100, 31684]
        [6, 36, 32, 44, 64, 104, 164, 264, 424, 684]
        [10, 100, 44, 18, 14, 14, 14, 14, 14, 14]
        [16, 256, 64, 14, 8, 8, 8, 8, 8, 8]
        [26, 676, 104, 14, 8, 8, 8, 8, 8, 8]
        [42, 1764, 164, 14, 8, 8, 8, 8, 8, 8]
        [68, 4624, 264, 14, 8, 8, 8, 8, 8, 8]
        [110, 12100, 424, 14, 8, 8, 8, 8, 8, 8]
        [178, 31684, 684, 14, 8, 8, 8, 8, 8, 8]
    */

    if(chmin(n, m) >= 5){
        cout << 8 << endl;
    }
    else if(n == 4 && m == 4){
        cout << 18 << endl;
    }
    else if(chmin(n, m) == 4){
        cout << 14 << endl;
    }
    else{
        if(n > m){
            swap(n, m);
        }

        ll f[N] = {2, 4, 6};
        ll a[N][N] = {
            {0, 0, 0},
            {1, 0, 1},
            {0, 1, 1}
        };

        if(n == 3){
            if(m <= 6){
                int a[6] = {6, 36, 32, 44, 64, 104};
                cout << a[m - 1] << endl;
                return;
            }
            else{
                ll df[N] = {44, 64, 104};
                ll da[N][N] = {
                    {0, 0, mod - 1},
                    {1, 0, 0},
                    {0, 1, 2}
                };

                memcpy(f, df, sizeof f);
                memcpy(a, da, sizeof a);
                m -= 3;
            }
        }

        m--;
        while(m){ 
            if(m & 1){
                mul(f, f, a);   
            }
            mul(a, a, a);   
            m >>= 1;
        }

        if(n == 2){
            cout << f[0] * f[0] % mod << endl;
        }
        else{
            cout << f[0] << endl;
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
