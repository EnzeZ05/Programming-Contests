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

struct HopcroftKarp{
    int l, r;
    vector<vector<int>> g;
    vector<int> pl, pr, d;

    HopcroftKarp(int l, int r)
        : l(l), r(r), g(l),
          pl(l, -1), pr(r, -1), d(l, -1) {}

    void add(int u, int v){
        g[u].push_back(v);
    }

    bool bfs(){
        queue<int> q;
        d.assign(l, -1);

        for(int u = 0; u < l; ++u){
            if(pl[u] == -1){ 
                d[u] = 0;
                q.push(u);
            }
        }

        bool found = false;
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int v : g[u]){
                int u2 = pr[v];    

                if(u2 == -1){
                    found = true;
                }
                else if (d[u2] == -1) {
                    d[u2] = d[u] + 1;
                    q.push(u2);
                }
            }
        }
        return found;
    }

    bool dfs(int u){
        for(int v : g[u]){
            int u2 = pr[v];

            if(u2 == -1 || (d[u2] == d[u] + 1 && dfs(u2))){
                pl[u] = v;
                pr[v] = u;
                return true;
            }
        }

        d[u] = -1;
        return false;
    }

    int HK(){
        int ans = 0;
        while(bfs()){
            for(int u = 0; u < l; ++u){
                if(pl[u] == -1 && dfs(u)){
                    ++ans;
                }
            }
        }
        return ans;
    }
};

void solve(){
    int n;
    cin >> n;

    vector<vector<int>> a, r, c;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        a.push_back({x, y});
    }

    int m;
    cin >> m;

    map<int, vector<int>> mpx, mpy;
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        
        mpx[y].push_back(x);
        mpy[x].push_back(y);
    }

    for(auto& [k, v] : mpx){
        sort(v.begin(), v.end());
    }
    for(auto& [k, v] : mpy){
        sort(v.begin(), v.end());
    }

    sort(a.begin(), a.end());
    for(int i = 1; i < n; i++){
        if(a[i][0] == a[i - 1][0]){
            if(abs(a[i - 1][1] - a[i][1]) == 1){
                cout << -1 << "\n";
                return;
            }

            int x = a[i][0];
            auto L = upper_bound(mpy[x].begin(), mpy[x].end(), a[i - 1][1]) - mpy[x].begin();
            auto R = lower_bound(mpy[x].begin(), mpy[x].end(), a[i][1]) - mpy[x].begin();

            if(L == R){
                r.push_back({a[i][0], a[i - 1][1], a[i][1]});
            }
        }
    }

    auto cmp = [&](const vector<int>& a, const vector<int>& b) -> bool{
        return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
    };

    sort(a.begin(), a.end(), cmp);
    for(int i = 1; i < n; i++){
        if(a[i][1] == a[i - 1][1]){
            if(abs(a[i - 1][0] - a[i][0]) == 1){
                cout << -1 << "\n";
                return;
            }

            int y = a[i][1];
            auto L = upper_bound(mpx[y].begin(), mpx[y].end(), a[i - 1][0]) - mpx[y].begin();
            auto R = lower_bound(mpx[y].begin(), mpx[y].end(), a[i][0]) - mpx[y].begin();

            if(L == R){
                c.push_back({a[i][1], a[i - 1][0], a[i][0]});
            }
        }
    }

    HopcroftKarp hk(r.size(), c.size());

    for(int i = 0; i < c.size(); i++){
        int x = c[i][0], y1 = c[i][1], y2 = c[i][2];
        for(int j = 0; j < r.size(); j++){
            int y = r[j][0], x1 = r[j][1], x2 = r[j][2];

            if(x1 < x && x < x2 && y1 < y && y < y2){
                hk.add(j, i);
            }
        }
    }

    int M = hk.HK();
    cout << c.size() + r.size() - M << "\n";

    vector<int> v1(r.size()), v2(c.size());
    for(int i = 0; i < r.size(); i++){
        if(hk.pl[i] != -1){
            int u = hk.pl[i];
            cout << r[i][0] << " " << c[u][0] << "\n";
            v1[i] = v2[u] = 1;
        }
    }

    for(int i = 0; i < r.size(); i++){
        if(!v1[i]){
            cout << r[i][0] << " " << r[i][1] + 1 << "\n";
        }
    }
    for(int i = 0; i < c.size(); i++){
        if(!v2[i]){
            cout << c[i][1] + 1 << " " << c[i][0] << "\n";
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
