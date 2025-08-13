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

const int N = 3e5 + 10, M = 2 * N;

void solve(){
    int n;
    cin >> n;

    vector<vector<ll>> a, b;
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;

        a.push_back({x, y});
    }

    int l = 0, r = (int)1e9 + 1;
    while(l < r){
        int mid = l + r >> 1;

        priority_queue<vector<ll>, vector<vector<ll>>, less<>> q;
        for(int i = 0; i < n; i++){
            if(a[i][0] < mid){
                b.push_back(a[i]);
            }
            else{
                q.push({a[i][0] + a[i][1], a[i][0], a[i][1]});
            }
        }

        auto cmp = [&](const vector<ll>& a, const vector<ll>& b) -> bool{
            return a[1] > b[1];
        };
        sort(b.begin(), b.end(), cmp);

        int flag = b.empty();
        for(int i = 0; i < b.size(); i++){
            if(q.empty()){
                break;
            }

            auto p = q.top();
            q.pop();

            if(p[2] > b[i][1]){
                
            }
            else{
                p[1] -= (b[i][1] - p[2]);
                if(p[1] >= mid){
                
                }
                else{
                    break;
                }
            }

            if(i == b.size() - 1){
                flag = 1;
            }
        }
        b.clear();

        if(!flag){
            r = mid;
        }
        else{
            l = mid + 1;
        }
    }
    cout << l - 1 << "\n";
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
