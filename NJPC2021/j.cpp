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

const int N = 1e5 + 1, M = 2 * N;

unordered_map<ll, ll> mp;
vector<ll> pr;

void prime(ll x){
    for(int i = 2; i <= x / i; i++){
        if(x % i == 0){
            pr.push_back(i);
            while(x % i == 0){
                x /= i;
            }
        }
    }
    if(x > 1){
        pr.push_back(x);
    }
}

ll get(ll x, ll y){
    return x * 1e9 + y;
}

ll dfs(ll x, ll y){
    if(mp[get(x, y)]){
        return mp[get(x, y)];
    }
    if(y - x == 1){
        return mp[get(x, y)] = x - 1;
    }
    if(x == 1){
        return mp[get(x, y)] = 0;
    }

    ll ans = x - 1;
    for(auto p : pr){
        if((y - x) % p == 0){
            ll d = x % p;
            ans = chmin(ans, chmin(d + 1 + dfs(x / p, y / p), p - d + 1 + dfs(x / p + 1, y / p + 1)));
        }   
    }

    return mp[get(x, y)] = ans;
}
 
void solve(){   
    mp.clear();
    pr.clear();

    ll x, y;
    cin >> x >> y;

    if(x > y){
        swap(x, y);
    }
    prime(y - x);
    cout << dfs(x, y) << endl;
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
