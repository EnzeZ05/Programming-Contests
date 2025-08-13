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

struct DSU{
    vector<int> node, size;
 
    DSU(){}
    DSU(int n){
        init(n);
    }
 
    void init(int n){
        node.resize(n);
        size.resize(n);
 
        for(int i = 0; i < n; i++){
            node[i] = i;
            size[i] = 1;
        }
    }
 
    int find(int x){
        return x == node[x] ? x : node[x] = find(node[x]);
    }
 
    void erase(int x){
        size[find(x)] -= 1;
        node[x] = x;
    }
 
    void relocate(int x, int y){ //can't be root
        int dx = find(x), dy = find(y);
        if(dx == dy){
            return;
        }
        node[x] = dy;
        size[dx] -= 1;
        size[dy] += 1;
    }
 
    int set(int x, int y){
        return find(x) == find(y);
    }
 
    int merge(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y){
            return 0;
        }
 
        size[x] += size[y];
        node[y] = x;
        return 1;
    }
 
    int heuristic_merge(int x, int y){ 
        x = find(x);
        y = find(y);
        if(size[x] < size[y]){
            swap(x, y);
        }
        return merge(x, y);
    }
 
    int get(int x){
        return size[find(x)];
    }
};
 
void solve(){
    int n, m;
    cin >> n >> m;

    DSU dsu(n + 1);
    vector<vector<int>> a;
    
    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        a.push_back({w, u, v});
    }

    sort(a.begin(), a.end());
    int ans = 0;

    for(int i = m - 1; i >= 0; i--){
        int u = a[i][1], v = a[i][2], w = a[i][0];
        if(w){
            dsu.heuristic_merge(u, v);
        }
        else{
            if(dsu.set(u, v)){
                ans++;
            }
            dsu.heuristic_merge(u, v);
        }
    }
    cout << ans << endl;
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
