/*
https://judge.yosupo.jp/problem/point_add_rectangle_sum
*/
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define int long long
#define all(a) a.begin(),a.end()
#define pb push_back

using namespace std;
const int N = 3e5+2;

struct query
{
    int t, X, Y, U, V, w;
}Q[N];
int n, q, x[N], y[N], w[N];
vector<int> rrhX, rrhY;

struct bit2D
{
    int m, n;
    vector<int> node[N], bit[N];
    void fakeUpd(int x,int y)
    {
        for(; x<=m; x+=x&-x)
            node[x].pb(y);
    }
    void fakeGet(int x,int y)
    {
        for(; x; x-=x&-x)
            node[x].pb(y);
    }
    void fakeGet(int u,int v,int x,int y)
    {
        fakeGet(x,y);
        fakeGet(u-1,y);
        fakeGet(x,v-1);
        fakeGet(u-1,v-1);
    }
    void reset()
    {
        forinc(i,1,m)
        {
            node[i].pb(n+10);
            sort(all(node[i]));
            node[i].erase(unique(all(node[i])),node[i].end());
            bit[i].resize(node[i].size()+3);
        }
    }
    void update(int x,int Y,int val)
    {
        for(; x<=m; x+=x&-x)
            for(int y = lower_bound(all(node[x]),Y)-node[x].begin()+1;y<=node[x].size();y+=y&-y)
                bit[x][y-1] += val;
    }
    int get(int x,int Y)
    {
        int res = 0;
        for(; x; x-=x&-x)
            for(int y = lower_bound(all(node[x]),Y)-node[x].begin()+1; y; y-=y&-y)
                res += bit[x][y-1];
        return res;
    }
    int Get(int u,int v,int x,int y)
    {
        return get(x,y) - get(u-1,y) - get(x,v-1) + get(u-1,v-1);
    }
    /// Đặt giới hạn hàng, cột
    /// fakeupd tất cả các giá trị sẽ upd
    /// fakeget tất cả các giá trị sẽ get
    /// sau đó reset lại cây
    /// Sử dụng hàm update và get như bthg
}t;

void enter()
{
    cin >> n >> q;
    forinc(i,1,n)
    {
        cin >> x[i] >> y[i] >> w[i];
        rrhX.pb(x[i]);
        rrhY.pb(y[i]);
    }
    forinc(i,1,q)
    {
        int t, x, y ,w, l, d, r, u;
        cin >> t;
        if(t==1)
        {
            cin >> l >> d >> r >> u;
            r--; u--;
            Q[i] = {1,l,d,r,u};
            rrhX.pb(l);
            rrhX.pb(r);
            rrhY.pb(d);
            rrhY.pb(u);
        }
        else
        {
            cin >> x >> y >> w;
            Q[i] = {0,x,y,0,0,w};
            rrhX.pb(x);
            rrhY.pb(y);
        }
    }
}

void prepare()
{
    sort(all(rrhX));
    sort(all(rrhY));
    rrhX.erase(unique(all(rrhX)),rrhX.end());
    rrhY.erase(unique(all(rrhY)),rrhY.end());

    t.m = rrhX.size(); /**/
    t.n = rrhY.size(); /**/

    forinc(i,1,n)
    {
        int X = lower_bound(all(rrhX),x[i]) - rrhX.begin() + 1;
        int Y = lower_bound(all(rrhY),y[i]) - rrhY.begin() + 1;
        x[i] = X, y[i] = Y;
        t.fakeUpd(X,Y); /**/
    }
    forinc(i,1,q)
    {
        if(Q[i].t==1)
        {
            int l = lower_bound(all(rrhX),Q[i].X) - rrhX.begin() + 1;
            int d = lower_bound(all(rrhY),Q[i].Y) - rrhY.begin() + 1;
            int r = lower_bound(all(rrhX),Q[i].U) - rrhX.begin() + 1;
            int u = lower_bound(all(rrhY),Q[i].V) - rrhY.begin() + 1;
            Q[i] = {1,l,d,r,u};
            t.fakeGet(l,d,r,u); /**/
        }
        else
        {
            int X = lower_bound(all(rrhX),Q[i].X) - rrhX.begin() + 1;
            int Y = lower_bound(all(rrhY),Q[i].Y) - rrhY.begin() + 1;
            Q[i] = {0,X,Y,0,0,Q[i].w};
            t.fakeUpd(X,Y); /**/
        }
    }
    t.reset(); /**/
}

void sol()
{
    forinc(i,1,n) t.update(x[i],y[i],w[i]);
    forinc(i,1,q)
    {
        if(Q[i].t==1)
        {
            int l = Q[i].X;
            int d = Q[i].Y;
            int r = Q[i].U;
            int u = Q[i].V;
            cout << t.Get(l,d,r,u) << '\n';
        }
        else t.update(Q[i].X, Q[i].Y, Q[i].w);
    }
}

main()
{
    //freopen("bit2D.inp","r",stdin);

    enter();
    prepare();
    sol();


}
/*
https://leduythuccs.github.io/2019-05-30-k-thu-t-n-n-c-y-bit2d/
*/
