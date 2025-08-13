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
unordered_map<int, priority_queue<vector<ll>, vector<vector<ll>>, greater<>>> q;

void solve(){
    int g;
    cin >> g;

    map<ll, ll> mp;
    for(int i = 0; i < g; i++){
        int id, x;
        cin >> id >> x;
        mp[id] += x;
    }    

    int n;
    cin >> n;

    vector<int> a(n);

    vector<vector<pair<int, int>>> rw(n);
    for(int i = 0; i < n; i++){
        int m;
        cin >> m;

        a[i] = m;
        for(int j = 0; j < m; j++){
            int id, x;
            cin >> id >> x;
            q[id].push({x, i});
        }

        int flag = (m == 0);

        cin >> m;
        for(int j = 0; j < m; j++){
            int id, x;
            cin >> id >> x;

            if(flag){
                mp[id] += x;
            }
            else{
                rw[i].push_back({id, x});
            }
        }
    }

    queue<pair<ll, int>> qd;
    for(auto& [k, v] : mp){
        qd.push({v, k});
    }
 
    int ans = 0;
    while(!qd.empty()){
        auto p = qd.front();
        qd.pop();

        ll u = p.first, id = p.second;
        map<int, int> vis;

        while(!q[id].empty()){
            auto p = q[id].top();
            if(u >= p[0]){
                q[id].pop();

                a[p[1]]--;
                if(a[p[1]] == 0){
                    for(auto& [x, y] : rw[p[1]]){
                        mp[x] += y;
                        vis[x] = 1;
                    }
                }
            }
            else{
                break;
            }
        }

        for(auto& [x, y] : vis){
            qd.push({mp[x], x});
        }
    }

    for(int i = 0; i < n; i++){
        ans += !a[i];
    }
    cout << ans << "\n";
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
