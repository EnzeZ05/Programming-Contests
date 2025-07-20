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

vector<string> h = {
    "######",
    "##..##",
    "#....#",
    "#....#",
    "##..##",
    "######"
};

double A[4][4], B[4][4];

void gauss(){
    int c, r;
    for(c = 1, r = 1; c <= 2; c++){
        int t = r;
        for(int i = r + 1; i <= 2; i++){
            if(fabs(B[i][c]) > fabs(B[t][c])){
                t = i;
            }
        }

        if(fabs(B[t][c]) < 1e-9){
            continue;
        }

        for(int i = c; i <= 2 + 1; i++){
            swap(B[t][i], B[r][i]);
        }
        for(int i = 2 + 1; i >= c; i--){
            B[r][i] /= B[r][c];
        }

        for(int i = r + 1; i <= 2; i++){
            if(fabs(B[i][c]) > 1e-9){
                for(int j = 2 + 1; j >= c; j--){
                    B[i][j] -= B[r][j] * B[i][c];
                }
            }
        }
        r++;
    }

    for(int i = 2; i > 0; i--){
        for(int j = i + 1; j <= 2; j++){
            B[i][2 + 1] -= B[i][j] * B[j][2 + 1];
        }
    }
}

void solve(){ 
    int n, m;
    cin >> n >> m;

    vector<string> s;
    int a = 0, b = 0;

    for(int i = 0; i < n; i++){
        string t;
        cin >> t;
        s.push_back(t);
        for(int j = 0; j < m; j++){
            if(t[j] == '#'){
                a++;
            }
        }
    }
 
    for(int i = 0; i < n - 5; i++){
        for(int j = 0; j < m - 5; j++){
            int c = 0;
            for(int ii = i; ii <= i + 5; ii++){
                for(int jj = j; jj <= j + 5; jj++){
                    if(s[ii][jj] == h[ii - i][jj - j]){
                        c++;
                    }
                }
            }
            if(c == 36){
                b++;
            }
        }
    }

    //146x + 100y = a
    //24x + 12y = b
    B[1][1] = 146;
    B[1][2] = 100;
    B[1][3] = a;

    B[2][1] = 24;
    B[2][2] = 12;
    B[2][3] = b * 12;

    gauss();
    cout << fixed << setprecision(0) << fabs(B[1][3]) << " " << fabs(B[2][3]) << endl;
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
