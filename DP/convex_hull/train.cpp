// CSP OPEN 02
// WTF ?
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
const int maxn = 1e5 + 5;

int n , m , A , B , C;

struct event{
    int time;
    int type;
    int u , v;
    event(int time , int type , int u , int v):time(time),type(type),u(u),v(v){};
    bool operator < (const event & other){
        return time < other.time;
    };
};

struct point{
    ll x , y;
    point(ll x = 0 , ll y = 0):x(x),y(y){};
    point operator - (const point other){
        return point(x - other.x , y - other.y);
    }
    ll operator * (const point other){
        if(x != 0 && other.y != 0 && abs(x) > 2e18 / abs(other.y)){
            cout << -2;exit(0);
        }
        if(y != 0 && other.x != 0 && abs(y) > 2e18 / abs(other.x)){
            cout << -2;exit(0);
        }
        return x * other.y - y * other.x;
    }
    ll val(int k){
        return x * k + y;
    }
    bool operator < (const point other){
        return mp(x , y) < mp(other.x , other.y);
    }
};

struct hull{
    vector<point> a;
    int pointer = 0;
    ll ask(int x){
        if(a.size() == 0)return (ll)1e18;
        ll res = 1e18;
        for(auto & c : a)res = min(res , c.val(x));
        return res;
        pointer = min(pointer , (int)a.size() - 1);
        while(pointer + 1 < a.size() && a[pointer].val(x) > a[pointer + 1].val(x))pointer++;
        return a[pointer].val(x);
    }
    void add(point x){
        if(a.size() > 0 && a.back() < x)return;
        while(a.size() >= 2 && (x - a.back()) * (a[a.size() - 2] - a.back()) >= 0)a.pop_back();
        a.pb(x);
    }
}s[maxn];

vector<pair<int , point>> add[maxn];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if(fopen("A.INP","r")) {
        freopen("A.INP", "r", stdin);
        freopen("A.OUT", "w", stdout);
    }
    vector<event> val;
    cin >> n >> m >> A >> B >> C;
    val.reserve(m);
    for(int i = 1 ; i <= m ; ++i){
        int u , v , p , q;cin >> u >> v >> p >> q;
        val.pb(event(p , q , u , v));
    }
    ll res = 1e18;
    sort(val.begin(),val.end());
    s[1].add(point(0 , 0));
    int j = 1;
    for(auto & [p , q , u , v] : val){
        while(j <= p){
            for(auto & c : add[j]){
                s[c.first].add(c.second);
            }
            ++j;
        }
        ll ans = s[u].ask(p) + 1ll * A * p * p + B * p + C;
        if(ans > (ll)1e18)continue;
        if(v == n)res = min(res , ans + A * q);
        add[q].pb(mp(v , point(-2 * A * q , ans + 1ll * A * q * q - B * q)));
    }
    if(res == 1e18)res = -1;
    cout << res;
}
