#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N = 1e5+1, mod = 1e9;
struct node
{
    int c, ok = 0;
    node *left, *right;
    void make()
    {
        if(ok) return;
        left = new node;
        right = new node;
        ok = 1;
    }
};
struct query{int r, a, b, c, d;};
int n, a[N], R, Q, res=0;
query q[N];
struct presidenIT
{
    node *r[N];
    int cur = 0, L, R;
    void build(node *s,int l,int r)
    {
        if(l==r)
        {
            s->c=a[l];
            return;
        }
        int mid=(l+r)/2;
        s->make();
        build(s->left,l,mid);
        build(s->right,mid+1,r);
        s->c=max(s->left->c,s->right->c);
    }
    void upd(node *s,node *p,int l,int r,int u,int x)
    {
        if(l>u||r<u) return;
        if(l==r)
        {
            s->c=x;
            return;
        }
        int mid=(l+r)/2;
        s->make(); p->make();
        if(u>=l&&u<=mid)
        {
            s->right=p->right;
            upd(s->left,p->left,l,mid,u,x);
        }
        else
        {
            s->left=p->left;
            upd(s->right,p->right,mid+1,r,u,x);
        }
        s->c=max(s->left->c,s->right->c);
    }
    void update(int i,int x)
    {
        r[++cur] = new node;
        upd(r[cur],r[cur-1],L,R,i,x);
    }
    int get(node *s,int l,int r,int u,int v)
    {
        if(l>v||r<u) return 0;
        if(l>=u&&r<=v) return s->c;
        s->make();
        int mid=(l+r)/2;
        return max(get(s->left,l,mid,u,v),get(s->right,mid+1,r,u,v));
    }
    int Max(int u,int v)
    {
        return get(r[cur],L,R,u,v);
    }
    void ver(int x)
    {
        r[++cur] = r[x];
    }
    void reset(int u,int v)
    {
        L = u, R = v;
        r[0] = new node;
        build(r[0],u,v);
    }
}it;

void solve()
{
    forinc(i,1,Q)
    {
        if(q[i].r==1)
        {
            int u = (res*q[i].a+q[i].c)%n+1;
            int k = (res*q[i].b+q[i].d)%mod+1;
            it.update(u,k);
        }
        if(q[i].r==2)
        {
            int u = (res*q[i].a+q[i].c)%n+1;
            int v = (res*q[i].b+q[i].d)%n+1;
            if(u>v) swap(u,v);
            res = it.Max(u,v);
            cout << res << '\n';
        }
        if(q[i].r==3)
        {
            int x = (res*q[i].a+q[i].c)%(it.cur+1);
            it.ver(x);
        }
    }
}
main()
{
//    freopen("vquery.inp","r",stdin);
    cin>>n;
    forinc(i,1,n) cin>>a[i];
    it.reset(1,n);
    cin>>R>>Q;
    forinc(i,1,Q) cin>>q[i].r>>q[i].a>>q[i].b>>q[i].c>>q[i].d;
    while(R--)
    {
        solve();
    }
}
