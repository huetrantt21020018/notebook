// UET 03.07.22
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
 
typedef long long lli;
typedef pair<int, int> pii;
#define st first
#define nd second
 
const int N = 101;
const lli inf = 1e12;
 
int n, m, k;
 
vector<lli> d;
vector<int> pre;
vector<pii> ke[N];
 
int dijks(int s,int t)
{
	d.assign(n+1, inf);
	pre.assign(n+1, 0);
	
    priority_queue<pii, vector<pii>, greater<pii> > heap;
	heap.push({d[s] = 0, s});
	
	while(!heap.empty())
	{
		lli dmin = heap.top().st;
		int u = heap.top().nd;
		heap.pop();
	
		if(u == t) return dmin;
		if(dmin > d[u]) continue;
		
		for(pii i : ke[u])
		{
			int v = i.st;
			lli c = dmin + i.nd;
		
			if(d[v] > c)
			{
				pre[v] = u;
				heap.push({d[v] = c, v});
			}
		}
	}
	
	return -1;
}
 
void trace(int s,int t)
{
    vector<int> vt;
    while(t)
	{
		vt.push_back(t);
		t = pre[t];
	}
	
	reverse(vt.begin(), vt.end());
	cout << vt.size() << ' ';
	for(int u : vt) cout << u << ' ';
}
 
int main()
{
//	freopen("bonus.inp","r",stdin);
 
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
 
	cin >> n >> m >> k;
	while(m--)
	{
        int u, v, c;
        cin >> u >> v >> c;
        ke[u].push_back({v, c});
        ke[v].push_back({u, c});
	}
    
    while(k--)
	{
        int type, u, v;
        cin >> type >> u >> v;
        lli res = dijks(u, v);
    
        if(type == 0) cout << res;
        else trace(u, v);
        cout << '\n';
	}
} 