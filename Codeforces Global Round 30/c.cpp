#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const ld pi = 3.14159265358979323846;
const int mod = (int)1e9 + 7;
const ll INF = 1e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

const int N = (int)2e5 + 1, M = N * 10;
 
void solve(){
    int n, m;
    cin >> n >> m;

    multiset<int> a;
    vector<int> b(m), c(m);
    vector<pair<int, int>> p, q;

    for(int i = 0; i < n; i++){
        int x;
        cin >> x;

        a.insert(x);
    }

    for(int i = 0; i < m; i++){
        cin >> b[i];
    }

    for(int i = 0; i < m; i++){
        cin >> c[i];
    }

    for(int i = 0; i < m; i++){
        if(c[i]){
            p.push_back({b[i], c[i]});
        }
        else{
            q.push_back({b[i], c[i]});
        }
    }

    sort(p.begin(), p.end());
    sort(q.begin(), q.end());
 
    int cnt = 0;
    for(int i = 0; i < p.size(); i++){
        int hp = p[i].first, c = p[i].second;
        auto it = a.lower_bound(hp);

        if(it != a.end()){
            int v = *it;
            a.erase(it);
            v = chmax(v, c);
            a.insert(v);
            cnt++;
        }
    }
 
    for(int i = 0; i < q.size(); i++){
        int hp = q[i].first, c = q[i].second;
        auto it = a.lower_bound(hp);

        if(it != a.end()){
            int v = *it;
            a.erase(it);
            cnt++;
        }
    }

    cout << cnt << "\n";
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