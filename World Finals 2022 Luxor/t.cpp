#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double pi  = 3.14159265358979323846;
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

const int N = 1e6 + 1, M = 2 * N;
 
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
        if(b.y == a.y) return 0;
        if(b.x == a.x) return INF;
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

    friend std::ostream &operator<<(ostream &os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

void solve(){
    Point<ld> p, p1, p2, p3, p4;
    ld h1, h2;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> h1;

    ld len = p.point_dist(p1, p2);
    Point<ld> v = p2 - p1;
    Point<ld> rev = Point<ld>({-v.y / len, v.x / len});
    p3 = p1 + rev * len;
    p4 = p2 + rev * len;

    Point<ld> c1 = (p1 + p4) / 2;

    Point<ld> q, q1, q2, q3, q4;
    cin >> q1.x >> q1.y >> q2.x >> q2.y >> h2;

    len = p.point_dist(q1, q2);
    v = q2 - q1;
    rev = Point<ld>({-v.y / len, v.x / len});
    q3 = q1 + rev * len;
    q4 = q2 + rev * len;

    Point<ld> c2 = (q1 + q4) / 2;

    vector<Point<ld>> a, b;

    a.push_back(p1);
    a.push_back(p2);
    a.push_back(p4);
    a.push_back(p3);

    b.push_back(q1);
    b.push_back(q2);
    b.push_back(q4);
    b.push_back(q3);

    ld min = INF, eps = 1e-10;

    auto f = [&](const Point<ld>& a, const Point<ld>& b) -> ld{
        ld x = c1.x - a.x, y = c1.y - a.y;
        ld d1 = sqrt(x * x + y * y + h1 * h1);
        ld d2 = p.point_dist(a, b);

        x = c2.x - b.x, y = c2.y - b.y;
        ld d3 = sqrt(x * x + y * y + h2 * h2);
        return d1 + d2 + d3;
    };

    auto search2 = [&](const Point<ld>& a, const Point<ld>& o, const Point<ld>& y) -> ld{
        ld ans = INF;
        ld l = 0, r = 1;
        auto v = y - o;

        while(l + eps < r){
            ld mid = (r - l) / 3.0;
            ld m1 = l + mid;
            ld m2 = m1 + mid;

            ld f1 = f(a, o + v * m1);
            ld f2 = f(a, o + v * m2);
            ans = chmin(ans, chmin(f1, f2));
            if(f1 <= f2){
              r = m2;
            }
            else{
              l = m1;
            }
        }
        return ans;
    };

    auto search1 = [&](Point<ld> a1, Point<ld> b1, Point<ld> a2, Point<ld> b2) -> ld{
       ld l = 0, r = 1, ans = INF;
       auto v = b1 - a1;

       while(l + eps < r){
          ld mid = (r - l) / 3.0;
          ld m1 = l + mid;
          ld m2 = m1 + mid;

          ld f1 = search2(a1 + v * m1, a2, b2);
          ld f2 = search2(a1 + v * m2, a2, b2);
          ans = chmin(ans, chmin(f1, f2));
          if(f1 <= f2){
              r = m2;
          }
          else{
              l = m1;
          }
       }
       return ans;
    };

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            min = chmin(min, search1(a[i], a[(i + 1) % 4], b[j], b[(j + 1) % 4]));
        }
    }

    cout << setprecision(20) << min << "\n";
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
