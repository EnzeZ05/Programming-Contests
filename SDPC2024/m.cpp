#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
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

const int N = 1e5 + 10, M = 2 * N;

template<typename T>
struct Point{
    T x, y;
    ld eps;

    Point() : x(0), y(0), eps(1e-9) {}
    Point(T x, T y) : x(x), y(y), eps(1e-9) {}

    void set_eps(T eps){
        this->eps = eps;
    }

    Point operator+ (const Point& b){
        return Point(x + b.x, y + b.y);
    }

    Point operator- (const Point& b){
        return Point(x - b.x, y - b.y);
    }

    Point operator- (){
        return Point(-x, -y);
    }

    Point operator* (T t) const{
        return Point(x * t, y * t);
    }

    Point operator/ (T t) const{
        return Point(x / t, y / t);
    }

    Point &operator+=(Point p) &{
        x += p.x;
        y += p.y;
        return *this;
    }

    Point &operator-=(Point p) &{
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point &operator*=(T v) &{
        x *= v;
        y *= v;
        return *this;
    }

    Point &operator/=(T v) &{
        x /= v;
        y /= v;
        return *this;
    }

    Point &operator=(const Point& b) &{
        x = b.x;
        y = b.y;
        return *this;
    }

    friend Point operator+ (const Point& a, const Point& b){
        return {a.x + b.x, a.y + b.y};
    }

    friend Point operator- (const Point& a, const Point& b){
        return {a.x - b.x, a.y - b.y};
    }

    friend bool operator==(Point a, Point b){
        return a.x == b.x && a.y == b.y;
    }

    int sign(T x){
        if(fabs(x) < eps){
            return 0;
        }
        if(x < 0){
            return -1;
        }
        return 1;
    }

    bool cmp(T x, T y){
        if(fabs(x - y) > eps){
            return 0;
        }
        return 1;
    }

    bool cmp(const Point& a, const Point& b){
        return cmp(a.x, b.x) && cmp(a.y, b.y);
    }

    T dot(const Point& a, const Point& b){
        return a.x * b.x + a.y * b.y;
    }

    T square(Point a){
        return dot(a, a);
    }

    T cross(const Point& a, const Point& b){
        return a.x * b.y - a.y * b.x;
    }

    T cross(const Point& a, const Point& b, const Point& p){
        return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
    }

    T get_len(const Point& a){
        return sqrt(dot(a, a));
    }

    T get_angle(const Point& a, const Point& b){
        return acos(dot(a, b) / get_len(a) / get_len(b));
    }

    T area(const Point& a, const Point& b, const Point& c){
        return cross(b - a, c - a);
    }

    Point rotate(const Point& a, T angle){ //两个点就 b - a (b按a转)
        T dx = a.x * cos(angle) + a.y * sin(angle); 
        T dy = -a.x * sin(angle) + a.y * cos(angle);
        return Point(dx, dy);
    }

    Point intersect(const Point& p, const Point& v, const Point& q, const Point& w){
        Point u = p - q;
        T t = cross(w, u) / cross(v, w);
        return p + v * t;
    }

    T point_dist(const Point& a, const Point& b){
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    T line_dist(const Point& a, const Point& b, const Point& p){
        Point u = b - a, v = p - a;
        return fabs(cross(u, v)) / get_len(u);
    }

    T get_slope(const Point& a, const Point& b){
        if(b.y == a.y) return INF;
        if(b.x == a.x) return 0;
        return (b.y - a.y) / (b.x - a.x);
    }

    T circle_intersect(const Point& p1, const Point& p2, const T r1, const T r2){
        ld d = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));

        if(d > r1 + r2 || d + chmin(r1, r2) <= chmax(r1, r2)){
            return 0;
        }
        else if(d == r1 + r2){
            return 1;
        }
        else{
            return 2;
        }
    }

    T seg_dist(const Point& a, const Point& b, const Point& p){
        if(a == b){
            return get_len(p - a);
        }
        Point u = b - a, v = p - a, w = p - b;

        if(sign(dot(u, v)) < 0){
            return get_len(v);
        }
        if(sign(dot(u, w)) > 0){
            return get_len(w);
        }
        return line_dist(a, b, p);
    }

    Point projection(const Point& a, const Point& b, const Point& p){
        Point v = b - a;
        return a + v * dot(v, p - a) / dot(v, v);
    }

    bool on_segment(const Point& a, const Point& b, const Point& p){
        bool u = sign(cross(p - a, p - b)) == 0;
        bool v = sign(dot(p - a, p - b)) <= 0;
        return u && v;
    }

    bool seg_intersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2){
        T c1 = cross(a2 - a1, b1 - a1), c2 = cross(a2 - a1, b2 - a1);
        T c3 = cross(b2 - b1, a2 - b1), c4 = cross(b2 - b1, a1 - b1);
        return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0;
    }
};

ll dp[1001][1001], ndp[1001][1001];
int a[1001], dl[501], dr[501];
Point<ll> p[1001];

void solve(){
    int n;
    cin >> n;

    vector<int> b;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i + n] = a[i];

        b.push_back(a[i]); 
    }

    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        p[i] = p[i + n] = Point<ll>(x, y);
    }

    Point<ll> pt;
    
    int m = n * 2;
    for(int i = 0; i < m; i++){
        for(int j = i + 1; j < chmin(m, i + n); j++){
            ndp[i][j] = pt.cross(p[i], p[j]);
            ndp[j][i] = -ndp[i][j];
        }
    }

    for(int i = 0; i < m; i++){
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        for(int j = 0; j < m; j++){
            dp[i][j] = 0;
        }
    }

    for(int len = 1; len < n; len++){
        for(int l = 0; l + len < m; l++){
            int r = l + len;
            if(a[l] == a[r]){
                if(r - l >= 3){
                    dp[l][r] = chmax(dp[l][r], dp[l + 1][r]);
                    dp[l][r] = chmax(dp[l][r], dp[l][r - 1]);

                    for(int k = l + 1; k < r; k++){
                        dl[a[k]] = dr[a[k]] = -1;
                    }
                    for(int k = l + 1; k < r; k++){
                        if(dl[a[k]] == -1){
                            dl[a[k]] = k;
                        }
                        dr[a[k]] = k;
                    }

                    for(int k = l + 1; k < r; k++){
                        if(dl[a[k]] != -1){
                            int L = dl[a[k]];
                            dp[l][r] = chmax(dp[l][r], dp[L][k] - ndp[k][L] + ndp[l][L] + ndp[k][r] + ndp[r][l]);
                        }
                        if(dr[a[k]] != -1){
                            int R = dr[a[k]];
                            dp[l][r] = chmax(dp[l][r], dp[k][R] - ndp[R][k] + ndp[l][k] + ndp[R][r] + ndp[r][l]);
                        }
                    }
                }  
                else{
                    dp[l][r] = chmax(dp[l][r], ndp[r][l] + ndp[l][l + 1] + ndp[l + 1][r]);
                }
            }
            else{
                dp[l][r] = chmax(dp[l + 1][r], dp[l][r - 1]);
            }
        }
    }

    ll ans = 0;
    for(int i = 0; i + n - 1 < m; i++){
        ans = chmax(ans, dp[i][i + n - 1]);
    }
    cout << ans << "\n";
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
