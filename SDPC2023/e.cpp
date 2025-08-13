#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
const int mod = (int)1e9 + 7;
const ll INF = 1e18;

template <typename T>
T chmax(T a, T b){
    return a > b ? a : b;
} 

template <typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = 3e5 + 10, M = 2 * N;

ostream& operator<<(ostream& os, i128 n) {
    if(n == 0){ 
        os << '0'; 
        return os; 
    }
    bool neg = n < 0;
    if (neg) n = -n;

    string s;
    while(n > 0){
        int digit = (int)(n % 10);
        s.push_back(char('0' + digit));
        n /= 10;
    }
    if(neg){
        s.push_back('-');
    }
    reverse(s.begin(), s.end());
    return os << s;
}

void solve(){
    ll N, K, M, A, B;
    cin >> N >> K >> M >> A >> B;

    i128 n = N, k = K, m = M, a = A, b = B;
    if(n % m == 0){
        cout << 0 << "\n";
    } 
    else if(k == 1){
        cout << -1 << "\n";
    }
    else{
        i128 ans = 0;
        i128 t = n;
        while(t){
            t /= k;
            ans += b;
        }

        for(int i = 0; ; i++){
            t = n;
            i128 res = 0;

            for(int j = 0; j < i; j++){
                t /= k;
                res += b;
            }
            if(res >= ans){
                break;
            }
            if(t % m == 0){
                ans = res;
                continue;
            }

            i128 l = t, r = t;
            for(int j = 0; ; j++){
                if(res >= ans){
                    break;
                }
                l = k * l;
                r = k * r + k - 1;
                res += a;

                if(r / m * m >= l){
                    break;
                }
            }
            ans = chmin(ans, res);
        }
        cout << ans << "\n";
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
