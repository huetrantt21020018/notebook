// CSP 4.12.20


#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;

const int inf = 1e9+7;


struct SegmentTree{
	int n;
	vector<int> Mi, Ma, lz;
	void init(int nn){
		n = nn;
		Mi.assign(4*n, inf);
		Ma.assign(4*n, -inf);
		lz.assign(4*n, 0);
	}
	void trans(int s){
		if(lz[s]){
			lz[2*s] += lz[s];
			lz[2*s+1] += lz[s];
			if(lz[s]%2){
				swap(Mi[2*s], Ma[2*s]);
				Mi[2*s] = -Mi[2*s]; Ma[2*s] = -Ma[2*s];
			}
			if(lz[s]%2){
				swap(Mi[2*s+1], Ma[2*s+1]);
				Mi[2*s+1] = -Mi[2*s+1]; Ma[2*s+1] = -Ma[2*s+1];
			}
			lz[s] = 0;
		}
	}
	void upd(int s,int l,int r,int u,int v){
		if(l>v || r<u) return;
		if(l>=u && r<=v){
			swap(Mi[s], Ma[s]);
			Mi[s] = -Mi[s], Ma[s] = -Ma[s];
			lz[s]++;
			return;
		}
		trans(s);
		int m = (l+r)/2;
		upd(2*s, l, m, u, v);
		upd(2*s+1, m+1, r, u, v);
		Mi[s] = min(Mi[2*s],Mi[2*s+1]);
		Ma[s] = max(Ma[2*s],Ma[2*s+1]);
	}
	void update(int l,int r){
		upd(1, 1, n, l, r);
	}
	void gans(int s,int l,int r,int i,int val){
		if(l>i || r<i) return;
		if(l==r){
			Mi[s] = Ma[s] = val;
			return;
		}
		trans(s);
		int m = (l+r)/2;
		gans(2*s, l, m, i, val);
		gans(2*s+1, m+1, r, i, val);
		Mi[s] = min(Mi[2*s],Mi[2*s+1]);
		Ma[s] = max(Ma[2*s],Ma[2*s+1]);
	}
	void assign(int i,int val){
		gans(1, 1, n, i, val);
	}
	int Max(int s,int l,int r,int u,int v){
		if(l>v || r<u) return -inf;
		if(l>=u && r<=v) return Ma[s];
		trans(s);
		int m = (l+r)/2;
		return max(Max(2*s, l, m, u, v), Max(2*s+1, m+1, r, u, v));
	}
	int get(int u,int v){
		return Max(1, 1, n, u, v);
	}
};

struct graph{
typedef pair<pair<int,int>,int> ppi;
#define st first
#define nd second
#define pb push_back
	int n, _time;
	vector<vector<int> > adj;
	vector<int> par, sz, head, tin, tout;
	vector<ppi> E; 
	SegmentTree IT;
	graph(int n) : n(n), par(n+1,0), E(1), sz(n+1,0), head(n+1,0), tin(n+1,0), tout(n+1,0), adj(n+1,vector<int>()) {}
	void AddEdge(int u,int v,int w){
		adj[u].pb(v);
		adj[v].pb(u);
		E.push_back({{u,v},w});
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
		for(int v:adj[u]) if(par[v] == u){
			if(2*sz[v] >= sz[u]) head[v] = head[u];
			else head[v] = v;
			HLD(v);
		}
		tout[u] = _time;
	}
	bool anc(int p,int u){
		return tin[p]<=tin[u] && tin[u]<=tout[p];
	}
	void change(int i,int w){
		int u = E[i].st.st, v = E[i].st.nd;
		if(par[u]==v) swap(u,v);
		IT.assign(tin[v],w);
	}
	void UpdEdge(int u,int v){
		while(!anc(head[u],v)){
			IT.update(tin[head[u]], tin[u]);
			u = par[head[u]];
		}
		while(head[u] != head[v]){
			IT.update(tin[head[v]], tin[v]);
			v = par[head[v]];
		}
		IT.update(min(tin[u],tin[v])+1,max(tin[u],tin[v]));
	}
	int GetEdge(int u,int v){
		if(u==v) return 0;
		int res = -inf;
		while(!anc(head[u],v)){
			res = max(res, IT.get(tin[head[u]], tin[u]));
			u = par[head[u]];
		}
		while(head[u] != head[v]){
			res = max(res, IT.get(tin[head[v]], tin[v]));
			v = par[head[v]];
		}
		res = max(res, IT.get(min(tin[u],tin[v])+1,max(tin[u],tin[v])));
		return res;
	}
	void build(int root){
		DFS(root);
		_time = 0; head[root] = root;
		HLD(root);
		IT.init(n);
		forinc(i,1,n-1) change(i, E[i].nd);
	}
};

int main(){
	freopen("qtreex.txt","r",stdin);

	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int test; cin >> test;
	while(test--){
		int n; cin >> n;
		graph G(n);
		int u, v, w;
		forinc(i,1,n-1) {
			cin >> u >> v >> w;
			G.AddEdge(u, v, w);
		}
		G.build(1);
		string type;
		while(cin >> type){
			if(type == "CHANGE"){
				int i, v;
				cin >> i >> v;
				G.change(i,v);
			}
			if(type == "NEGATE"){
				cin >> u >> v;
				G.UpdEdge(u,v);
			}
			if(type == "QUERY"){
				cin >> u >> v;
				cout << G.GetEdge(u,v) << '\n';
			}
			if(type == "DONE") break;
		}
	}
}