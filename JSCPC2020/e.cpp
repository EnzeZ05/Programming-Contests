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
int vis[N], pre[N], nxt[N], del[N];
vector<int> adj[N];

void solve(){
    int n, m, k;
    cin >> n >> m >> k;

    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    queue<pair<int, int>> q;
    q.push({(1 << n) - 1, 0});

    auto get = [&](int mask) -> int{
        int tmp = 0;
        for(int i = 0; i < n; i++){
            if(mask >> i & 1){
                for(auto j : adj[i]){
                    tmp |= 1 << j;
                }
            }
        }
        return tmp;
    };

    auto answer = [&](int mask) -> void{
        vector<vector<char>> a;
        while(mask != (1 << n) - 1){
            int mk = pre[mask], sub = del[mask];

            vector<char> b;
            for(int i = 0; i < n; i++){
                if(sub >> i & 1){
                    b.push_back((char)(i + 'a'));
                }
            }
            a.push_back(b);
            mask = mk;
        }

        cout << a.size() << endl;
        for(int i = (int)a.size() - 1; i >= 0; i--){
            for(auto A : a[i]){
                cout << A;
            }
            cout << '\n';
        }
    };

    for(int i = 0; i < 1 << n; i++){
        vis[i] = (int)1e9;
        nxt[i] = get(i);
    }

    while(!q.empty()){
        auto p = q.front();
        q.pop();

        int mask = p.first, s = p.second;
        if(s > 100){
            continue;
        }
        if(mask == 0){
            answer(mask);
            return;        
        }

        int bits = __popcount(mask);
        for(int i = mask; ; i = mask & (i - 1)){
            if(i == mask || bits - __popcount(i) > k){
                if(i == 0){
                    break;
                }
                continue;
            }

            int mk = nxt[i];
            if(vis[mk] > s + 1){
                pre[mk] = mask;
                vis[mk] = s + 1;
                del[mk] = mask ^ i;
                q.push({mk, s + 1});
            }

            if(i == 0){
                break;
            }
        }
    }

    cout << -1 << endl;
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
