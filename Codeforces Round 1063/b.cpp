#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const ld pi = 3.14159265358979323846L;
const int mod = 998244353;
const ll INF = (ll)1e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}

bool cover(int l, int r, int i, int val, const vector<int> &p){
    if(l >= r) return false;
    if(!(l < i && i < r)) return false;
    int pl = p[l], pr = p[r];
    int mn = min(pl, pr), mx = max(pl, pr);
    if(!(mn < val && val < mx)) return false;
    return true;
}

void solve(){
    int n;
    cin >> n;

    vector<int> p(n + 1), pos(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> p[i];
        pos[p[i]] = i;
    }

    string xs;
    cin >> xs;
    string x = " " + xs;

    if(x[1] == '1' || x[n] == '1'){
        cout << -1 << "\n";
        return;
    }

    vector<int> targets;
    for(int i = 2; i <= n - 1; i++){
        if(x[i] == '1') targets.push_back(i);
    }

    if(targets.empty()){
        cout << 0 << "\n";
        return;
    }

    vector<int> pref_min(n + 1), pref_max(n + 1);
    vector<int> suff_min(n + 2), suff_max(n + 2);

    pref_min[0] = n + 1;
    pref_max[0] = 0;
    for(int i = 1; i <= n; i++){
        pref_min[i] = min(pref_min[i - 1], p[i]);
        pref_max[i] = max(pref_max[i - 1], p[i]);
    }

    suff_min[n + 1] = n + 1;
    suff_max[n + 1] = 0;
    for(int i = n; i >= 1; i--){
        suff_min[i] = min(suff_min[i + 1], p[i]);
        suff_max[i] = max(suff_max[i + 1], p[i]);
    }

    for(int i : targets){
        int v = p[i];
        bool has_L_lt = (pref_min[i - 1] < v);
        bool has_L_gt = (pref_max[i - 1] > v);
        bool has_R_lt = (suff_min[i + 1] < v);
        bool has_R_gt = (suff_max[i + 1] > v);
        bool ok = (has_L_lt && has_R_gt) || (has_L_gt && has_R_lt);
        if(!ok){
            cout << -1 << "\n";
            return;
        }
    }

    set<int> cand_idx = {1, n, pos[1], pos[n]};
    vector<pair<int,int>> ops;
    for(int l : cand_idx){
        for(int r : cand_idx){
            if(l < r) ops.push_back({l, r});
        }
    }

    int k = (int)ops.size();
    for(int mask = 0; mask < (1 << k); mask++){
        vector<pair<int,int>> cur;
        for(int j = 0; j < k; j++){
            if(mask >> j & 1){
                cur.push_back(ops[j]);
            }
        }
        if(cur.size() > 5) continue;

        bool all_ok = true;
        for(int idx : targets){
            bool cov = false;
            int v = p[idx];
            for(auto [l, r] : cur){
                if(cover(l, r, idx, v, p)){
                    cov = true;
                    break;
                }
            }
            if(!cov){
                all_ok = false;
                break;
            }
        }

        if(all_ok){
            cout << cur.size() << "\n";
            for(auto [l, r] : cur){
                cout << l << " " << r << "\n";
            }
            return;
        }
    }

    cout << -1 << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
