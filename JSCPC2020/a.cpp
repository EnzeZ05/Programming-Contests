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
int p;

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
    int b[31] = {};

    static Mark add(int k){
        Mark m;
        k %= p;
        for(int i = 0; i < p; ++i){
            m.b[i] = (i + k) % p;
        }
        return m;
    }

    static Mark mul(int k){
        Mark m;
        k %= p;
        for(int i = 0; i < p; ++i){
            m.b[i] = (int)((i * 1ll * k) % p);
        }
        return m;
    }

    static ll qpow(ll base, ll exp){
        ll res = 1, b = base % p;
        while(exp){
            if(exp & 1){ 
                res = (res * b) % p;
            }
            b = (b * b) % p;
            exp >>= 1;
        }
        return (int)(res % p);
    }

    static Mark pw(ll k){
        Mark m;
        for(int i = 0; i < p; i++){
            m.b[i] = qpow(i, k);
        }
        return m;
    }

    Mark(){
        for(int i = 0; i < p; i++){
            b[i] = i;
        }
    }

    void modify(const Mark &v){
        int c[31] = {};
        for(int i = 0; i < p; i++){
            c[i] = v.b[b[i]];
        }
        for(int i = 0; i < p; i++){
            b[i] = c[i];
        }
    }
};
 
struct Operation{
    int a[31] = {};
    Operation(int num = -1){
        if(num != -1){
            a[num % p]++;
        }
    }

    void modify(const Mark &v){
        int c[31] = {};
        for(int i = 0; i < p; i++){
            c[v.b[i]] += a[i];
        }
        for(int i = 0; i < p; i++){
            a[i] = c[i];
        }
    }
};
 
Operation operator+(Operation a, Operation b){
    Operation c;
    for(int i = 0; i < p; i++){
        c.a[i] = a.a[i] + b.a[i];
    }
    return c;
}
 
void solve(){
    int n;
    cin >> n >> p;

    SegTree<Operation, Mark> tr(n);
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;
        tr.update(i, Operation(x));
    }

    int q;
    cin >> q;

    for(int i = 0; i < q; i++){
        int op, l, r, x;
        cin >> op >> l >> r >> x;

        if(op == 1){
            tr.range_update(l, r, Mark::add(x));
        }
        else if(op == 2){
            tr.range_update(l, r, Mark::mul(x));
        }
        else if(op == 3){
            tr.range_update(l, r, Mark::pw(x));
        }
        else if(op == 4){
            auto a = tr.query(l, r);
            ll sum = 0;

            for(int j = 0; j < p; j++){
                sum = (sum + Mark::qpow(j, x) * a.a[j] % p) % p;
            }
            cout << sum << endl;
        }
        else{
            auto a = tr.query(l, r);
            ll sum = 1;

            for(int j = 0; j < p; j++){
                if(!a.a[j]){
                    continue;
                }
                sum = sum * Mark::qpow(j, a.a[j]) % p;
            }
            cout << sum << endl;
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