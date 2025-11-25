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

vector<int> adj[N];

void solve(){
    int n, x, y;
    cin >> n >> x >> y;

    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto bfs = [&](int s) -> vector<int>{
        vector<int> d(n + 1, (int)1e9);
        d[s] = 0;

        queue<int> q;
        q.push(s);

        while(!q.empty()){
            auto u = q.front();
            q.pop();

            for(auto& v : adj[u]){
                if(d[v] > d[u] + 1){
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }    

        return d;
    };

    auto a1 = bfs(x), a2 = bfs(y);
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(a1[i] <= a2[i]){
            cnt++;
        }
    }

    if(cnt * 2 >= n){
        cout << "Alice\n";
    }
    else{
        cout << "Bob\n";
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