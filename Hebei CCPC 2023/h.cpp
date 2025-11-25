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

struct CartesianTree{
    int n;
    vector<int> a, l, r;

    CartesianTree(int _n) : n(_n), a(_n), l(_n, -1), r(_n, -1){

    }

    int work(){
        stack<int> s;
        for(int i = 0; i < n; i++){
            int last = -1;
            while(!s.empty() && a[s.top()] < a[i]){ //max
                last = s.top();
                s.pop();
            }
            if(!s.empty()){
                r[s.top()] = i;
            }
            if(last != -1){
                l[i] = last;
            }
            s.push(i);
        }

        int rt = 0;
        while(!s.empty()){
            rt = s.top();
            s.pop();
        }
        return rt;
    }
};

void solve(){
    int n;
    cin >> n;

    CartesianTree tr(n);
    for(int i = 0; i < n; i++){
        cin >> tr.a[i];
    }

    int root = tr.work();

    ll ans = 0;
    auto work = [&](auto& self, int u) -> map<int, int>{
        map<int, int> mpl, mpr;
        if(tr.l[u] != -1){
            mpl = self(self, tr.l[u]);
        }
        if(tr.r[u] != -1){
            mpr = self(self, tr.r[u]);
        }

        auto it = mpl.find(0);
        if(it != mpl.end()){
            ans += it->second;
        }

        it = mpr.find(0);
        if(it != mpr.end()){
            ans += it->second;
        }

        if(tr.a[u] == 0){
            ans++;
        }

        if(mpl.size() < mpr.size()){
            swap(mpl, mpr);
        }

        for(auto& [k, v] : mpr){
            if(k <= tr.a[u]){
                it = mpl.find(tr.a[u] - k);
                if(it != mpl.end()){
                    ans += v * 1ll * it->second;
                }
            }
        }

        for(auto& [k, v] : mpr){
            mpl[k] += v;
        }
        mpl[tr.a[u]]++;
        return mpl;
    };

    work(work, root);
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