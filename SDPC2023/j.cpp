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
    int n, m, q;
    ll V;
    cin >> n >> m >> q >> V;
    
    vector<DSU> dsu;
    DSU any(n + 1);

    for(int i = 0; i < 61; i++){
        DSU uf(n + 1);
        dsu.push_back(uf);
    }

    int msb = 0, lsb = -1;
    for(int i = 0; i < 61; i++){
        if(V >> i & 1){
            msb = i;
            if(lsb == -1){
                lsb = i;
            }
        }
    }

    for(int i = 0; i < m; i++){
        int u, v;
        ll w;
        cin >> u >> v >> w;

        any.heuristic_merge(u, v);
        if(w < V){
            continue;
        }
        else{
            for(int j = 60; j > msb; j--){
                if(w >> j & 1){
                    dsu[j].heuristic_merge(u, v);
                }
            }
            for(int j = msb; j >= lsb; j--){
                if(!(V >> j & 1) && (w >> j & 1)){
                    dsu[j].heuristic_merge(u, v);
                }
                else if((V >> j & 1) && !(w >> j & 1)){
                    break;
                }
                else if(j == lsb && (w >> j & 1)){
                    dsu[j].heuristic_merge(u, v);
                }
            }
        }
    }

    for(int i = 0; i < q; i++){
        int u, v;
        cin >> u >> v;

        if(V == 0){
            cout << (any.set(u, v) ? "Yes" : "No") << "\n";
            continue;
        }
        for(int j = lsb; j < 61; j++){
            if(dsu[j].set(u, v)){
                cout << "Yes" << "\n";
                goto entry;
            }
        }

        cout << "No" << "\n";
        entry:;
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
