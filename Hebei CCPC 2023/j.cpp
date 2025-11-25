#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const double pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = (ll)4e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = 4;

struct Matrix{
    int size;
    vector<vector<ll>> mat;

    Matrix(int s) : size(s), mat(s, vector<ll>(s, 0)) {}

    static Matrix identity(int s){
        Matrix res(s);
        for(int i = 0; i < s; ++i){
            res.mat[i][i] = 1;
        }
        return res;
    }

    Matrix operator*(const Matrix& other) const{
        Matrix res(size);
        for(int i = 0; i < size; ++i){
            for(int k = 0; k < size; ++k){
                if(mat[i][k]){ 
                    for(int j = 0; j < size; ++j){
                        res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % mod;
                    }
                }
            }
        }
        return res;
    }
};

void solve(){ 
    ll n, m;
    cin >> n >> m;

    if(n * m % 3 != 0){
        cout << 0 << "\n";
        return;
    }

    int s = 1 << n;
    Matrix mat(s);

    for(int i = 0; i < s; i++){
        auto dfs = [&](auto& self, int r, int mask1, int mask2, int mask) -> void{
            if(r == n){
                if(mask1 == s - 1){
                    mat.mat[mask][mask2]++;
                    return;
                }
            }

            if(mask1 >> r & 1){
                self(self, r + 1, mask1, mask2, mask);
                return;
            }

            // cha tou dp   
            if(r && !(mask2 >> (r - 1) & 1) && !(mask2 >> r & 1)){
                self(self, r + 1, mask1 | 1 << r, (mask2 | (1 << (r - 1)) | (1 << r)), mask);
            }
            if(r + 1 < n && !(mask2 >> (r + 1) & 1) && !(mask2 >> r & 1)){
                self(self, r + 1, mask1 | 1 << r, (mask2 | (1 << (r + 1)) | (1 << r)), mask);
            }
            if(r + 1 < n && !(mask1 >> (r + 1) & 1) && !(mask2 >> r & 1)){
                self(self, r + 2, (mask1 | (1 << r) | (1 << (r + 1))), mask2 | (1 << r), mask);
            }
            if(r + 1 < n && !(mask1 >> (r + 1) & 1) && !(mask2 >> (r + 1) & 1)){
                self(self, r + 2, (mask1 | (1 << r) | (1 << (r + 1))), mask2 | (1 << (r + 1)), mask);
            }
        };

        dfs(dfs, 0, i, 0, i);
    }

    Matrix dp = Matrix::identity(s);
    while(m){
        if(m & 1){
            dp = dp * mat;
        }
        mat = mat * mat;
        m >>= 1;
    }

    cout << dp.mat[0][0] << "\n";
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