/// mincut-maxflow
/// jobset voi14

#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define pii pair<int,int>
#define st first
#define nd second
using namespace std;
const int N = 505, add = 1e6, inf = 1e9+add;
int n, m, a[N], sum;

struct MaxFlow
{
	int n, s, t, FlowVal = 0, ss;
	vector<int> dd, pre;
	vector<vector<pii> > E;
	vector<pii> trace;

	MaxFlow(int n,int s,int t) : n(n), s(s), t(t)
	{
		dd.resize(n+3);
		pre.resize(n+3);
		E.resize(n+3);
		forinc(i,0,n+1) E[i].resize(n+3);
	}

	void AddEdge(int u,int v,int cap) {E[u][v].st += cap; E[u][v].nd = 1;}

	bool FindPath()
	{
		dd[s] = ++ss;
		queue<int> q; q.push(s);
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			forinc(v,1,n) if(dd[v]!=ss && E[u][v].st>0)
			{
				dd[v] = ss;
				pre[v] = u;
				q.push(v);
				if(v==t) return 1;
			}
		}
		return 0;
	}

	void IncFlow()
	{
		int u = t, MaxFlow = inf;
		while(u!=s)
		{
			MaxFlow = min(MaxFlow, E[pre[u]][u].st);
			u = pre[u];
		}
		FlowVal += MaxFlow;
		u = t;
		while(u!=s)
		{
			E[pre[u]][u].st -= MaxFlow;
			E[u][pre[u]].st += MaxFlow;
			u = pre[u];
		}
	}
	int MinCut()
	{
		while(FindPath()) IncFlow();
		vector<int> X, Y;
		// X = tập đỉnh đến đc từ S
		// Y = tập đỉnh đến đc T
		queue<int> q;
		q.push(s);
		dd[s] = ++ss;
		while(!q.empty())
		{
			int u=q.front(); q.pop();
			X.push_back(u);
			forinc(v,1,n) if(dd[v]!=ss && E[u][v].st>0)
			{
				dd[v]=ss;
				q.push(v);
			}
		}
		forinc(i,1,n) if(dd[i] != ss) Y.push_back(i);
		for(int u:X) for(int v:Y)
		{
			// Có cạnh nối X-Y -> cắt
			if(E[u][v].nd) trace.push_back({u,v});
		}
		return FlowVal;
	}
};

main()
{
	//freopen("jobset.inp","r",stdin);

    cin >> n;
    MaxFlow luong(n+1,0,n+1);
    forinc(i,1,n)
    {
    	cin >> a[i];
    	a[i] += add;
    	sum += a[i];
    	luong.AddEdge(0,i,a[i]);
    	luong.AddEdge(i,n+1,add);
    }
    cin >> m;
    forinc(i,1,m)
    {
        int u, v;
        cin >> u >> v;
        luong.AddEdge(u,v,inf);
    }
    cout << sum - luong.MinCut() << '\n';
    //for(pii i:luong.trace) cout << i.st << ' ' << i.nd << endl;
}
