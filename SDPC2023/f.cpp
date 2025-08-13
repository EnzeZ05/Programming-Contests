#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ld  = long double;
using i128 = __int128_t;

const double  pi  = 3.14159265358979323846;
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

const int N = 2e5 + 10, M = 2 * N;

template<class Operation, class Mark>
struct SegTree{
    const int n;
    vector<Operation> op;
    vector<Mark> mrk;
 
    SegTree(int n) : n(n), op(4 << __lg(n)), mrk(4 << __lg(n)){
        function<void(int, int, int)> build = [&](int u, int l, int r){
            op[u] = Operation();
            if(l == r) return;
            int mid = l + r >> 1;
            build(u << 1, l, mid);
            build(u << 1 | 1, mid + 1, r);
            pushup(u);
        };
 
        build(1, 1, n);
    }
 
    void pushup(int u){
        op[u] = op[u << 1] + op[u << 1 | 1];
    }
 
    void modify(int u, const Mark &mk){
        op[u].modify(mk);
        mrk[u].modify(mk);
    }
 
    void pushdown(int u){
        modify(u << 1, mrk[u]);
        modify(u << 1 | 1, mrk[u]);
        mrk[u] = Mark();
    }
 
    void update(int u, int l, int r, int x, const Operation &v){
        if(l == r){
            op[u] = v;
            return;
        }
        int m = (l + r) >> 1;
        pushdown(u);
 
        if(x <= m){
            update(u << 1, l, m, x, v);
        } 
        else{
            update(u << 1 | 1, m + 1, r, x, v);
        }
        pushup(u);
    }
 
    void update(int u, const Operation &v){
        update(1, 1, n, u, v);
    }
 
    Operation query(int u, int l, int r, int x, int y){
        if(x <= l && r <= y) {
            return op[u];
        }
        
        int m = (l + r) >> 1;
        Operation cur;
        pushdown(u);
        if(x <= m){
            cur = query(u << 1, l, m, x, y);
        }
        if(y > m){
            cur = cur + query(u << 1 | 1, m + 1, r, x, y);
        }
        return cur;
    }
 
    Operation query(int l, int r){
        return query(1, 1, n, l, r);
    }
 
    void range_update(int u, int l, int r, int x, int y, const Mark &v){
        if(l >= x && r <= y){
            modify(u, v);
            return;
        }
 
        int m = (l + r) >> 1;
        pushdown(u);
        if(x <= m){
            range_update(u << 1, l, m, x, y, v);
        }
        if(y > m){
            range_update(u << 1 | 1, m + 1, r, x, y, v);
        }
        pushup(u);
    }
 
    void range_update(int l, int r, const Mark &v){
        return range_update(1, 1, n, l, r, v);
    }
};
 
struct Mark{
    ll add = 1;
    Mark(ll p = 1){
        add = p;
    }
    void modify(const Mark &v){
        add *= v.add;
        add %= mod;
    }
};
 
struct Operation{
    ll dp = 0;
    Operation(ll p = 0){
        dp = p;
    }

    void modify(const Mark &v){
        if(v.add){
            dp *= v.add;
            dp %= mod;
        }
    }
};
 
Operation operator+(Operation a, Operation b){
    return {(a.dp + b.dp) % mod};
}

void solve(){
    int n;
    cin >> n;

    vector<vector<int>> a;
    vector<int> b;

    for(int i = 0; i < n; i++){
        int l, r, c;
        cin >> l >> r >> c;
        a.push_back({l, r, c});

        b.push_back(l);
        b.push_back(r);
    }   

    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    SegTree<Operation, Mark> tr1(b.size() + 10), tr2(b.size() + 10);

    for(int i = 0; i < n; i++){
        a[i][0] = lower_bound(b.begin(), b.end(), a[i][0]) - b.begin() + 1;
        a[i][1] = lower_bound(b.begin(), b.end(), a[i][1]) - b.begin() + 1;
    }

    auto cmp = [&](const vector<int>& a, const vector<int>& b) -> bool{
        return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
    };

    sort(a.begin(), a.end(), cmp);

    tr1.update(1, 1);
    tr2.update(1, 1);

    ll ans = 1;
    for(int i = 0; i < n; i++){
        int l = a[i][0] + 1, r = a[i][1] + 1, c = a[i][2];
        if(c == 0){
            ll ndp = tr2.query(1, l - 1).dp;
            tr2.range_update(1, l - 1, 2);
            tr1.update(r, tr1.query(r, r).dp + ndp);
            ans = (ans + ndp) % mod;
        }
        else{
            ll ndp = tr1.query(1, l - 1).dp;
            tr1.range_update(1, l - 1, 2);
            tr2.update(r, tr2.query(r, r).dp + ndp);
            ans = (ans + ndp) % mod;
        }
    }

    cout << ans << "\n";
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
