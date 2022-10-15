#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)

using namespace std;
const int N = 1e5+1;

struct Graph
{
#define pii pair<int,int>
#define st first
#define nd second
	int n, weight, inf;
	vector<vector<pii>> g;
	Graph(int n) : n(n), weight(0), inf(1e9) {
        g.assign(n+1,vector<pii>());
	}
    void AddEdge(int u,int v,int c)
    {
        g[u].push_back({v,c});
        g[v].push_back({u,c});
    }
    int mst()
    {
        priority_queue<pii,vector<pii>,greater<pii> > heap;
        vector<int> d(n+1,inf);
        vector<bool> mst(n+1,0);
        heap.push({d[1]=0,1});
        while(!heap.empty())
		{
            while(!heap.empty() && mst[heap.top().nd]) heap.pop();
            if(heap.empty()) break;
            int dmin = heap.top().st;
            int u = heap.top().nd;
            mst[u] = 1; weight += dmin;
            heap.pop();
            for(pii i:g[u])
			{
				int v = i.st, c = i.nd;
				if(d[v] > c) heap.push({d[v] = c, v});
			}
		}
		return weight;
    }
};

int main()
{
//	freopen("qbmst.inp","r",stdin);

	int n, m;
    cin >> n >> m;
    Graph g(n);
    forinc(i,1,m)
    {
    	int u, v, c;
    	cin >> u >> v >> c;
        g.AddEdge(u,v,c);
    }
    cout << g.mst();
}