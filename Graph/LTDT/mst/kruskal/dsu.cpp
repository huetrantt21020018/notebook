#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
const int N = 1e5+1;
int p,x,y,z;
using namespace std;

struct DSU
{
	int n;
    vector<int> id;
    DSU(int n) : n(n)
    {
        id.resize(n+1,-1);
    }
    int root(int u)
    {
        return (id[u]<0 ? u : (id[u]=root(id[u])));
    }
    void join(int u,int v)
    {
        if((u=root(u)) == (v=root(v))) return;
        if(id[u] > id[v]) swap(u,v);
        id[u] += id[v];
        id[v] = u;
    }
};

main()
{
    //freopen("ioibin.inp","r",stdin);
    cin>>p;
    DSU dsu(N-1);
    while(p--)
    {
        cin>>x>>y>>z;
        if(z==1) dsu.join(x,y);
        else cout<<(dsu.root(x)==dsu.root(y))<<"\n";
    }
}
