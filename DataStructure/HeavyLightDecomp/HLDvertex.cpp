// CSP 4.12.20

#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;

const int inf = 2e5+5;
int color[inf];

struct SegmentTree{
	int n;
	vector<int> T;
	void init(int nn){
		n = nn;
		T.assign(4*n, inf);
	}
	void upd(int s,int l,int r,int i,int val){
		if(l>i || r<i) return;
		if(l==r){
			T[s] = val;
			return;
		}
		int m = (l+r)/2;
		upd(2*s, l, m, i, val);
		upd(2*s+1, m+1, r, i, val);
		T[s] = min(T[2*s], T[2*s+1]);
	}
	void update(int i,int val){
		upd(1,1,n,i,val);
	}
	int Min(int s,int l,int r,int u,int v){
		if(l>v || r<u) return inf;
		if(l>=u && r<=v) return T[s];
		int m = (l+r)/2;
		return min(Min(2*s, l, m, u, v), Min(2*s+1, m+1, r, u, v));
	}
	int get(int u,int v){
		return Min(1, 1, n, u, v);
	}
};

struct graph{
#define pb push_back
	int n, _time;
	vector<vector<int> > adj;
	vector<int> par, sz, head, tin, tout, x;
	SegmentTree IT;
	graph(int n) : n(n), x(n+1), par(n+1,0), sz(n+1,0), head(n+1,0), tin(n+1,0), tout(n+1,0), adj(n+1,vector<int>()) {}
	void AddEdge(int u,int v){
		adj[u].pb(v);
		adj[v].pb(u);
	}
	void DFS(int u){
		sz[u] = 1;
		int szmax = 0, imax = 0, _size = adj[u].size();
		for(int i=0; i<_size; ++i) {
			int v = adj[u][i];
			if(v != par[u]){
				par[v] = u;
				DFS(v);
				sz[u] += sz[v];
				if(sz[v] > szmax){
					szmax = sz[v];
					imax = i;
				}
			}
		}
		swap(adj[u][0], adj[u][imax]);
	}
	void HLD(int u){
		tin[u] = ++_time;
		x[_time] = u;
		for(int v:adj[u]) if(par[v] == u){
			if(2*sz[v] >= sz[u]) head[v] = head[u];
			else head[v] = v;
			HLD(v);
		}
		tout[u] = _time;
	}
	void build(int root){
		DFS(root);
		_time = 0; head[root] = root;
		HLD(root);
		IT.init(n);
	}
	bool anc(int p,int u){
		return tin[p]<=tin[u] && tin[u]<=tout[p];
	}
	void change(int u){
		color[u] = (1^color[u]);
		if(color[u]) IT.update(tin[u], tin[u]);
		else IT.update(tin[u], inf);
	}
	int GetPath(int u,int v){
		int res = inf;
		while(!anc(head[u], v)){
			res = min(res, IT.get(tin[head[u]], tin[u]));
			u = par[head[u]];
		}
		while(head[u] != head[v]){
			res = min(res, IT.get(tin[head[v]], tin[v]));
			v = par[head[v]];
		}
		res = min(res, IT.get(min(tin[u],tin[v]), max(tin[u],tin[v])));
		if(res<inf) return x[res];
		return -1;
	}
};

int main(){
	freopen("qtree3.txt","r",stdin);

	int n, q;
	cin >> n >> q;
	graph G(n);
	int u, v;
	forinc(i,1,n-1) {
		cin >> u >> v;
		G.AddEdge(u, v);
	}
	G.build(1);
	while(q--){
		int type; cin >> type;
		if(type == 0){
			cin >> u;
			G.change(u);
		}
		else {
			cin >> u;
			cout << G.GetPath(1, u) << '\n';
		}
	}
	
}