#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

constexpr int N = 1 << 18;
constexpr int inf = 1 << 30;

i64 lcm[N];
i64 sum[N];
int tag[N];

void pull(int p) {
    if (lcm[2 * p] > inf) {
        lcm[p] = lcm[2 * p];
    } else if (lcm[2 * p + 1] > inf) {
        lcm[p] = lcm[2 * p + 1];
    } else {
        lcm[p] = std::lcm(lcm[2 * p], lcm[2 * p + 1]);
    }
    sum[p] = sum[2 * p] + sum[2 * p + 1];
}

void build(int p, int l, int r, std::vector<int> &a) {
    tag[p] = 0;
    if (r - l == 1) {
        lcm[p] = sum[p] = a[l];
        return;
    }
    
    int m = (l + r) / 2;
    build(2 * p, l, m, a);
    build(2 * p + 1, m, r, a);
    pull(p);
}

void assign(int p, int l, int r, int v) {
    lcm[p] = v;
    sum[p] = i64(r - l) * v;
    tag[p] = v;
}

void push(int p, int l, int r) {
    int m = (l + r) / 2;
    if (tag[p]) {
        assign(2 * p, l, m, tag[p]);
        assign(2 * p + 1, m, r, tag[p]);
        tag[p] = 0;
    }
}

void rangeAssign(int p, int l, int r, int x, int y, int v) {
    if (l >= y || r <= x) {
        return;
    }
    if (l >= x && r <= y) {
        return assign(p, l, r, v);
    }
    int m = (l + r) / 2;
    push(p, l, r);
    rangeAssign(2 * p, l, m, x, y, v);
    rangeAssign(2 * p + 1, m, r, x, y, v);
    pull(p);
}

i64 rangeGcd(int p, int l, int r, int x, int y, int v) {
    if (l >= y || r <= x) {
        return 0;
    }
    if (l >= x && r <= y) {
        if (v % lcm[p] == 0) {
            return sum[p];
        }
        if (sum[p] % (r - l) == 0 && sum[p] / (r - l) == lcm[p]) {
            assign(p, l, r, std::gcd<int>(lcm[p], v));
            return sum[p];
        }
    }
    int m = (l + r) / 2;
    push(p, l, r);
    i64 ans = rangeGcd(2 * p, l, m, x, y, v) + rangeGcd(2 * p + 1, m, r, x, y, v);
    pull(p);
    return ans;
}

void solve() {
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    build(1, 0, n, a);
    
    for (int i = 0; i < q; i++) {
        int o, l, r, x;
        std::cin >> o >> l >> r >> x;
        l--;
        
        if (o == 0) {
            rangeAssign(1, 0, n, l, r, x);
        } else {
            std::cout << rangeGcd(1, 0, n, l, r, x) << "\n";
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
