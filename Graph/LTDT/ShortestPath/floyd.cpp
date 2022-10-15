#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define pb push_back
#define pii pair<int,int>
#define st first
#define nd second
using namespace std;
const int N=101;
int n, m, k, e[N][N];
int dd[N][N], d[N], pre[N], in[N];
vector<int> ke[N];
void floyd(int rt)
{
    forinc(i,1,n) d[i] = 1e9, pre[i] = in[i] = 0;
    queue<int> q;
    q.push(rt);
    d[rt] = 0; in[rt] = 1;
    while(!q.empty())
    {
        int u = q.front(); q.pop();
        in[u] = 0;
        for(int v:ke[u]) if(d[v] > d[u]+e[u][v])
        {
            pre[v] = u;
            d[v] = d[u] + e[u][v];
            if(!in[v])
            {
                in[v] = 1;
                q.push(v);
            }
        }
    }
}
int main()
{
    //freopen("floyd.inp","r",stdin);
	cin >> n >> m >> k;
	memset(e,127,sizeof e);
	forinc(i,1,m)
	{
		int u, v, c;
		cin >> u >> v >> c;
		e[u][v] = e[v][u] = min(e[u][v], c);
		if(!dd[u][v])
        {
            dd[u][v] = dd[v][u] = 1;
            ke[u].pb(v);
            ke[v].pb(u);
        }
	}
    while(k--)
    {
        int tp, u, v;
        cin >> tp >> u >> v;
        floyd(u);
        if(tp == 0) cout << d[v] << '\n';
        else
        {
            stack<int> trace;
            while(v)
            {
                trace.push(v);
                v = pre[v];
            }
            cout << trace.size() << ' ';
            while(!trace.empty())
            {
                cout << trace.top() << ' ';
                trace.pop();
            }
            cout << '\n';
        }
    }
}
