#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using ld = long double;
using ll = long long;

const ld pi = 3.14159265358979323846;
const int mod = 998244353;
const ll INF = 1e18;

template<typename T>
T chmax(T a, T b){
    return a > b ? a : b;
}

template<typename T>
T chmin(T a, T b){
    return a > b ? b : a;
}
 
void solve(){
    int n;
    cin >> n;

    int q;
    cin >> q;

    vector<vector<int>> a;
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        a.push_back({l, r});
    }

    sort(a.begin(), a.end(), [&](const vector<int>& x, const vector<int>& y){
        if(x[0] != y[0]) return x[0] < y[0];
        return x[1] > y[1];
    });

    vector<vector<int>> b;
    int maxR = -1;

    for(auto &seg : a){
        int L = seg[0], R = seg[1];
        if(R <= maxR){
            continue;
        }
        b.push_back(seg);
        maxR = R;
    }
    a.swap(b);


    int l = 0, r = a.size(), ans = 0;
    while(l < r){
        int mid = l + r >> 1;

        int L = a[mid][0], R = a[mid][1];
        cout << "? " << 1 << " " << R << "\n" << flush;
        int x;
        cin >> x;

        cout << "? " << L << " " << n << "\n" << flush;
        int y;
        cin >> y;

        ans = chmax(ans, chmin(x, y));

        if(x > y){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }

    cout << "! " << ans << "\n" << flush;
} 

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // cout.tie(nullptr);

    int t = 1;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}