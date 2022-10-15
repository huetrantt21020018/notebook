#include <bits/stdc++.h>
using namespace std;
#define forinc(i, a, b) for(int i=a; i<=b; ++i)
#define fordec(i, a, b) for(int i=a; i>=b; --i)
#define forb(i, BS) for(int i=BS._Find_first(); i<BS.size(); i=BS._Find_next(i))
#define forv(a, b) for(auto &a : b)
#define pb push_back
#define all(a) a.begin(),a.end()
#define bit(x,i) ((x>>i)&1)
#define onbit(x,i) (x|(1<<i))
#define offbit(x,i) (x&~(1<<i))
#define fastio ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r){return l+rng()%(r-l+1);}

typedef long long lli;
typedef unsigned long long llu;
typedef pair<lli, lli> line;
#define A first
#define B second

const int N = 1e6 + 5;
const lli inf = 1e18;
const int min_type = 1, max_type = -1;

struct convex_hull
{
    vector<line> st;
    int top, type;
    void init(int n, int t) {
        top = 0;
        type = t;
        st.resize(n+3);
    }
    lli F(int i, lli x) {
        if(i<1 || i>top) return inf * type;
        return st[i].A * x + st[i].B;
    }
    bool xoa(line a, line b, line c) {
        if(b.A == c.A) return 1;
        double A = 1.0 * (b.B-a.B) / (a.A-b.A);
        double B = 1.0 * (c.B-b.B) / (b.A-c.A);
        return A >= B;
    }
    void add(line t) { // y = ax + b
        while(top>1 && xoa(st[top-1], st[top], t)) --top;
        st[++top] = t;
    }
    bool check(int i, lli x) {
        if(F(i, x) <= F(i+1, x) && type == min_type) return 1;
        if(F(i, x) >= F(i+1, x) && type == max_type) return 1;
        return 0;
    }
    lli get(lli x) {
        int l = 1, r = top, id = r;
        while(l <= r) {
            int mid = (l + r) / 2;
            if(check(mid, x)) {
                id = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        return F(id, x);
    }
};

struct IT_convex
{
    int L, R, type;
    vector<convex_hull> T;
    void build(int s, int l, int r) {
        T[s].init(r - l + 1, type);
        if(l==r) return;
        int m = (l+r) / 2;
        build(2*s, l, m);
        build(2*s+1, m+1, r);
    }
    void init(int l, int r, int t) {
        L = l, R = r; type = t;
        T.resize(4*R);
        build(1, l, r);
    }
    void upd(int s, int l, int r, int i, line t) {
        if(l>i || r<i) return;
        T[s].add(t);
        if(l == r) return;
        int m = (l+r) / 2;
        upd(2*s, l, m, i, t);
        upd(2*s+1, m+1, r, i, t);
    }
    void update(int i, lli a, lli b) {
        line t = {a, b};
        upd(1, L, R, i, t);
    }
    lli get(int s, int l, int r, int u, int v, lli x) {
        if(l>v || r<u) return inf * type;
        if(l>=u && r<=v) return T[s].get(x);
        int m = (l + r) / 2;
        if(type == min_type)
            return min(get(2*s, l, m, u, v, x), get(2*s+1, m+1, r, u, v, x));
        else return max(get(2*s, l, m, u, v, x), get(2*s+1, m+1, r, u, v, x));
    }
    lli get(int l, int r, lli x) {
        return get(1, L, R, l, r, x);
    }
} it1, it2;

int n;
lli a[N], s[N];

void readInput()
{
    cin >> n;
    forinc(i, 1, n)
    {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
    }
}

void prepare()
{
    it1.init(0, n, min_type);
    it2.init(0, n, max_type);
    forinc(i, 0, n) it1.update(i, -i, s[i]);
    fordec(i, n, 0) it2.update(i, -i, s[i]);
}

lli solve(int u, int v)
{
    lli l = -4*N, r = 4*N, res = l;
    while(l <= r)
    {
        lli tbc = (l+r) / 2;
        lli pre = it1.get(0, u-1, tbc);
        lli nxt = it2.get(v, n, tbc);
        if(nxt >= pre)
        {
            res = tbc;
            l = tbc + 1;
        }
        else r = tbc - 1;
    }
    return res;
}

int main()
{
    if(fopen("input.txt","r"))
    {
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    }
//    fastio;

    readInput();

    prepare();

	int q, l, r; cin >> q;
	while(q--)
    {
        cin >> l >> r;
        cout << solve(l, r) << '\n';
    }

}
