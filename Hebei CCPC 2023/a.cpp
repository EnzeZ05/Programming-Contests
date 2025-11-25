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

const int N = (int)1e6 + 1;

struct Convex{
    struct Point{
        ld x, y;
        Point operator + (const Point &o) const{ 
            return { x + o.x, y + o.y }; 
        }
        Point operator - (const Point &o) const{ 
            return { x - o.x, y - o.y }; 
        }
    };

    static ld cross(Point a, Point b, Point c){
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
    static ld cross(Point v, Point w){ 
        return v.x * w.y - v.y * w.x;
    }

    static bool cmp(Point a, Point b){
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    }

    static vector<Point> convex_hull(vector<Point> p, bool remove_collinar = true){
        sort(p.begin(), p.end(), cmp);
        p.erase(unique(p.begin(), p.end(), [](Point A, Point B){ 
            return A.x == B.x && A.y == B.y; }), p.end()
        );
        
        int n = (int)p.size();
        if (n <= 1) return p;

        vector<Point> st;
        st.reserve(n + 1);

        for (int i = 0; i < n; i++){
            while ((int)st.size() >= 2){
                int s = (int)st.size();
                ld cr = cross(st[s - 2], st[s - 1], p[i]);
                if(remove_collinar ? cr <= 0 : cr < 0){
                    st.pop_back();
                }
                else break;
            }
            st.push_back(p[i]);
        }

        int lim = (int)st.size();
        for(int i = n - 2; i >= 0; i--){
            while((int)st.size() > lim){
                int s = (int)st.size();
                ld cr = cross(st[s - 2], st[s - 1], p[i]);
                if(remove_collinar ? cr <= 0 : cr < 0){
                    st.pop_back();
                }
                else{
                    break;
                }
            }
            st.push_back(p[i]);
        }

        if(!st.empty()){
            st.pop_back(); 
        }
        return st;
    }

    static void rotate_(vector<Point> &p){
        if(p.empty()){
            return;
        }
        int id = 0;
        for(int i = 1; i < (int)p.size(); i++){
            if(p[i].y < p[id].y || (p[i].y == p[id].y && p[i].x < p[id].x)){ 
                id = i;
            }
        }
        rotate(p.begin(), p.begin() + id, p.end());
    }

    static vector<Point> get_vectors(const vector<Point> &p){
        int n = (int)p.size();
        vector<Point> e(n);
        for(int i = 0; i < n; i++){
            e[i] = p[(i + 1) % n] - p[i];
        }
        return e;
    }

    static vector<Point> minkowski(vector<Point> A, vector<Point> B){ // CCW
        if(A.empty() || B.empty()){ 
            return {};
        }
        rotate_(A);
        rotate_(B);

        vector<Point> a = get_vectors(A);
        vector<Point> b = get_vectors(B);

        vector<Point> S;
        S.reserve(a.size() + b.size() + 1);
        S.push_back(A[0] + B[0]);

        int i = 0, j = 0, n = (int)a.size(), m = (int)b.size();
        while(i < n || j < m){
            Point v = (i < n ? a[i] : Point{0, 0});
            Point w = (j < m ? b[j] : Point{0, 0});
            ld cr = cross(v, w);

            if(j == m || (i < n && cr > 0)){
                S.push_back(S.back() + v); i++;
            } 
            else if (i == n || cr < 0){
                S.push_back(S.back() + w); j++;
            } 
            else{
                S.push_back({S.back().x + v.x + w.x, S.back().y + v.y + w.y});
                i++; j++;
            }
        }

  
        if(S.size() >= 2 && S.front().x == S.back().x && S.front().y == S.back().y){
            S.pop_back();
        }

        auto col = [](Point a, Point b, Point c){ 
            return cross(a, b, c) == (ld)0; 
        };

        vector<Point> R;
        R.reserve(S.size());

        for(auto &pt : S){
            R.push_back(pt);
            while (R.size() >= 3 && col(R[R.size() - 3], R[R.size() - 2], R.back())) {
                R.erase(R.end() - 2);
            }
        }
        if(R.size() >= 3 && col(R[R.size() - 2], R.back(), R[0])){
            R.pop_back();
        }
        if(R.size() >= 3 && col(R.back(), R[0], R[1])){
            R.erase(R.begin());
        }
        return R; 
    }
};

void solve(){
    int n, m;
    cin >> n >> m;

    vector<Convex::Point> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
    }

    auto on_segment = [&](Convex::Point A, Convex::Point B, Convex::Point P) -> bool {
        if(fabsl(Convex::cross(A, B, P)) > 1e-9){
            return false;
        }
        return (min(A.x, B.x) - 1e-9 <= P.x && P.x <= max(A.x, B.x) + 1e-9 &&
                min(A.y, B.y) - 1e-9 <= P.y && P.y <= max(A.y, B.y) + 1e-9);
    };

    a = Convex::convex_hull(a, false);
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;

        Convex::Point p(x, y);
        int len = a.size();

        if(len == 1){
            cout << (p.x == a[0].x && p.y == a[0].y ? "YES\n" : "NO\n");
            continue;
        }

        if(len == 2){
            cout << (on_segment(a[0], a[1], p) ? "YES\n" : "NO\n");
            continue;
        }

        int inside = 1;
        for(int j = 1; j <= len; j++){
            if(Convex::cross(a[j - 1], a[j % len], p) < 0){
                inside = 0;
            }
        }

        cout << (inside ? "YES\n" : "NO\n");
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