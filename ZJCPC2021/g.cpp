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

struct DSU{
    vector<int> node, size, a;
 
    DSU(){}
    DSU(int n){
        init(n);
    }
 
    void init(int n){
        node.resize(n);
        size.resize(n);
 
        for(int i = 0; i < n; i++){
            node[i] = i;
        }
    }
 
    int find(int x){
        return x == node[x] ? x : node[x] = find(node[x]);
    }
 
    void erase(int x){
        size[find(x)] -= 1;
        node[x] = x;
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

int dirx[6] = {-1, -1, 0, 0, 1, 1}, diry[6] = {1, 0, 1, -1, 0, -1};

void solve(){
    map<pair<int, int>, int> mp;
    int id = 0;

    int n;
    cin >> n;

    vector<vector<int>> q;
    auto get = [&](int x, int y) -> void{
        if(!mp.count({x, y}));
        mp[{x, y}] = id++;

        for(int i = 0; i < 6; i++){
            int dx = x + dirx[i], dy = y + diry[i];
            if(!mp.count({dx, dy})){
                mp[{dx, dy}] = id++;
            }
        }
    };


    for(int i = 0; i < n; i++){
        int op, x, y;
        cin >> op >> x >> y;
        q.push_back({op, x, y});

        get(x, y);
    }

    DSU dsu(id);

    for(int i = 0; i < n; i++){
        int op = q[i][0], x = q[i][1], y = q[i][2];
        if(op == 1){
            int walls = 6, a = mp[{x, y}];
            for(int j = 0; j < 6; j++){
                int dx = x + dirx[j], dy = y + diry[j], b = mp[{dx, dy}];
                if(dsu.get(b)){
                    dsu.heuristic_merge(a, b);
                    dsu.size[dsu.find(a)] -= 1;
                    walls--;
                }
            }
            dsu.size[dsu.find(a)] += walls;
        }
        else{
            cout << dsu.get(mp[{x, y}]) << "\n";
        }
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
