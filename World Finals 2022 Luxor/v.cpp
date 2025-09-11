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

const int N = 1e5 + 1, M = 2 * N;

struct Point{
    double x, y;
}p[N], stk[N];
int n, tp;

inline double cross(Point a, Point b, Point c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool cmp(Point a, Point b){
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}

inline void convex_hull(){
    sort(p, p + n, cmp);
    tp = 0;

    for(int i = 0; i < n; i++){
        while(tp > 1 && cross(stk[tp - 1], stk[tp], p[i]) <= 0){
            tp--;
        }
        stk[++tp] = p[i];
    }

    int lim = tp;
    for(int i = n - 2; i >= 0; i--){
        while(tp > lim && cross(stk[tp - 1], stk[tp], p[i]) <= 0){
            tp--;
        }
        stk[++tp] = p[i];
    }
}

void solve(){
    int n1, n2;
    cin >> n1;

    vector<int> a(n1), pt;
    for(int i = 0; i < n1; i++){
        cin >> a[i];
        pt.push_back(a[i]);
        pt.push_back(a[i] + 1);
    }

    cin >> n2;
    vector<int> b(n2);
    for(int i = 0; i < n2; i++){
        cin >> b[i];
        pt.push_back(b[i]);
        pt.push_back(b[i] + 1);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    pt.push_back(1);
    sort(pt.begin(), pt.end());
    pt.erase(unique(pt.begin(), pt.end()), pt.end());
    
    auto calc = [&](const vector<int>& a, int p, int op) -> double{
        int l = lower_bound(a.begin(), a.end(), p) - a.begin();
        int r = upper_bound(a.begin(), a.end(), p) - a.begin();
        if(op == 1){
            return (l + 0.5 * (r - l)) / a.size();
        }
        else{
            return (a.size() - r + 0.5 * (r - l)) / a.size();
        }
    };

    double d1 = 0, d2 = 0;
    for(auto A : a){
        d1 += calc(b, A, 1);
    }
    for(auto B : b){
        d2 += calc(a, B, 1);
    }

    if(d2 * a.size() > d1 * b.size()){
        swap(a, b);
    }

    n = pt.size();
    for(int i = 0; i < pt.size(); i++){
        int P = pt[i];
        p[i].x = calc(a, P, 2);
        p[i].y = calc(b, P, 2);
    }

    convex_hull();
    double ansx = INF, ansy = 0, cut = 0.5;

    for(int i = 2; i <= tp; i++){
        double l = chmin(stk[i].x, stk[i - 1].x), r = chmax(stk[i].x, stk[i - 1].x);
        double slope = (stk[i].y - stk[i - 1].y) / (stk[i].x - stk[i - 1].x);

        if(l <= cut && cut <= r){
            ansy = chmax(ansy, stk[i].y + (cut - stk[i].x) * slope);
        }

        l = chmin(stk[i].y, stk[i - 1].y), r = chmax(stk[i].y, stk[i - 1].y);
        if(l <= cut && cut <= r){
            ansx = chmin(ansx, stk[i].x + (cut - stk[i].y) / slope);
        }
    }

    cout << fixed << setprecision(6) << 1 - ansy << " " << 1 - ansx << "\n";
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
