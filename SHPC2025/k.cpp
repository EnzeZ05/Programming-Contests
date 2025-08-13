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

template <typename T>
struct Z{
    static const T Mod = (T)1e9 + 7;
    T num;
 
    Z() : num(0) {}
 
    Z(T n) : num(n % Mod) {
        if (num < 0) num += Mod;
    }
 
    Z operator+(const Z& other) const{
        T res = num + other.num;
        if (res >= Mod) res -= Mod;
        return Z(res);
    }
 
    Z operator-(const Z& other) const{
        T res = num - other.num;
        if (res < 0) res = (res + Mod) % Mod;
        return Z(res);
    }
 
    Z operator*(const Z& other) const{
        return Z(num * other.num % Mod);
    }
 
    Z operator/(const Z& other) const{
        return *this * qpow(other, Mod - 2);
    }
 
    bool operator >=(const Z& other) const{
        return num >= other.num;
    }
 
    bool operator <=(const Z& other) const{
        return num <= other.num;
    }
 
    bool operator >(const Z& other) const{
        return num > other.num;
    }
 
    bool operator <(const Z& other) const{
        return num < other.num;
    }
 
    friend constexpr bool operator==(Z a, Z b){
        return a.num == b.num;
    }
 
    friend constexpr bool operator!=(Z a, Z b){
        return a.num != b.num;
    }
 
    constexpr Z &operator*=(Z z) &{
        num = 1LL * num * z.num % Mod;
        return *this;
    }
 
    constexpr Z &operator+=(Z z) &{
        num = (num + z.num + Mod) % Mod;
        return *this;
    }
 
    constexpr Z &operator-=(Z z) &{
        num = (num - z.num + Mod) % Mod;
        return *this;
    }
 
    constexpr Z &operator/=(Z z) &{
        return *this *= inverse(z);
    }
 
    static Z qpow(const Z& v, T k){
        T val = v.num;
        T ret = 1;
        for(k %= Mod - 1; k > 0; k >>= 1, val = val * val % Mod){
            if(k & 1){
                ret = ret * val % Mod;
            }
        }
        return Z(ret);
    }
 
    static Z inverse(const Z& v){
        return qpow(v, Mod - 2);
    }
 
    friend ostream& operator<<(ostream& os, const Z& z){
        os << z.num;
        return os;
    }
};

Z<ll> dp[N][2];

void solve(){
    Z<ll> p, q, r;
    cin >> p.num >> q.num >> r.num;
    p /= 1000, q /= 1000, r /= 1000;

    int n;
    cin >> n;
    
    ll a[n + 1], sum = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
    }

    dp[0][0] = 1;
    Z<ll> P = 1;

    for(int i = 1; i <= n; i++){
        ll x = 0, y = 0;
        if(sum < 80){
            x = chmin(a[i], 80 - sum);
            y = a[i] - x;
        }
        else{
            x = 0;
            y = a[i];
        }
        sum += a[i];

        Z<ll> e = p + q - p * q;
        Z<ll> zero = Z<ll>::qpow(P - p, x) * Z<ll>::qpow(P - e, y);
        Z<ll> X = Z<ll>(x) * p * (x ? Z<ll>::qpow(P - p, x - 1) : 0) * Z<ll>::qpow(P - e, y);
        Z<ll> Y = Z<ll>(y) * e * (y ? Z<ll>::qpow(P - e, y - 1) : 0) * Z<ll>::qpow(P - p, x);
        Z<ll> one = X + Y;

        dp[i][0] = dp[i - 1][0] * zero;
        dp[i][1] = dp[i - 1][0] * one + dp[i - 1][1] * (P - r) * zero; 
    }

    for(int i = 1; i <= n; i++){
        cout << dp[i - 1][0] + dp[i - 1][1] - dp[i][0] - dp[i][1] << '\n';
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
