#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define pb push_back
#define pii pair<int,int>
#define st first
#define nd second
using namespace std;
const int N=101;
int n,m,k,e[N][N];
int d[N][N],T[N][N];
void bellman_ford()
{
    forinc(k,1,n)
    forinc(u,1,n)
    forinc(v,1,n) if(d[u][v] > d[u][k]+d[k][v])
    {
        d[u][v] = d[u][k]+d[k][v];
        T[u][v] = T[u][k];
    }
}
int main()
{
    //freopen("graph.inp","r",stdin);
	cin>>n>>m>>k;
	forinc(u,1,n)
	{
		forinc(v,1,n) d[u][v] = e[u][v] = 1e9;
		e[u][u] = d[u][u] = 0;
	}
	forinc(i,1,m)
	{
		int u,v,c;
		cin>>u>>v>>c;
		e[u][v] = e[v][u] = min(e[u][v],c);
		d[u][v] = d[v][u] = e[u][v];
		T[u][v] = v;
		T[v][u] = u;
	}
	bellman_ford();
    while(k--)
    {
        int tp,u,v;
        cin>>tp>>u>>v;
        if(tp==0) cout<<d[u][v]<<'\n';
        else
        {
            vector<int> trace;
            while(u!=v)
            {
                trace.pb(u);
                u=T[u][v];
            }
            cout<<trace.size()+1<<' ';
            for(int x:trace) cout<<x<<' ';
            cout<<v<<'\n';
        }
    }
}
