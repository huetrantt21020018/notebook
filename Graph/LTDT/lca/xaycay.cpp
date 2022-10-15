#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define pb push_back
#define pii pair<int,int>
#define st first
#define nd second
#define all(a) a.begin(),a.end()

using namespace std;

const int N = 1e5+1;

int n, res, logn;
vector<int> ke[N], adj[N];
int tin[N], tout[N], id, P[N][25], h[N];

void DFS(int u,int p)
{
    tin[u] = ++id;
    forinc(i,1,logn) P[u][i] = P[P[u][i-1]][i-1];
    for(int v:ke[u]) if(v!=p)
    {
        h[v] = h[u]+1;
        P[v][0] = u;
        DFS(v,u);
    }
    tout[u] = id;
}

bool anc(int u,int v)
{
    return (tin[u]<=tin[v])&&(tout[u]>=tout[v]);
}
int f[N], cl[N], dd[N], imp;
void sol(int u)
{
    if(dd[u]==imp) f[u] = 1;
    else f[u] = 0;
    cl[u] = imp;
    for(int v:adj[u]) if(cl[v]!=imp)
    {
        sol(v);
        if(dd[u]==imp)
        {
            if(f[v]) res++;
        }
        else f[u]+=f[v];
    }
    if(f[u]>1&&dd[u]!=imp)
    {
        ++res;
        f[u] = 0;
    }
}
int lca(int u,int v)
{
    if(h[u]<h[v]) swap(u,v);
    int del = h[u]-h[v];
    forinc(i,0,logn) if((del>>i)&1) u = P[u][i];
    if(u==v) return u;
    fordec(i,logn,0) if(P[u][i]!=P[v][i])
    {
        u = P[u][i];
        v = P[v][i];
    }
    return P[u][0];
}
int main()
{
    //freopen("613D.inp","r",stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    logn = log2(n);
    forinc(i,1,n-1)
    {
        int u, v;
        cin >> u >> v;
        ke[u].pb(v);
        ke[v].pb(u);
    }
    DFS(1,0);
    int q, k;
    cin >> q;
    while(q--)
    {
        ++imp;
        cin >> k;
        vector<int> w;
        forinc(i,1,k)
        {
            int u;
            cin >> u;
            w.pb(u);
            dd[u] = imp;
        }
        bool ok = 0;
        for(int u:w)
        {
            if(ok) break;
            for(int v:ke[u]) if(dd[v]==imp)
            {
                ok = 1;
                break;
            }
        }
        if(ok)
        {
            cout << "-1\n";
            continue;
        }
        auto cmp=[&](int u,int v){
            return make_pair(tin[u],tout[u])<make_pair(tin[v],tout[v]);
        };

        sort(all(w),cmp);
        vector<int> z;
        forinc(i,1,w.size()-1) z.push_back(lca(w[i-1],w[i]));
        for(int u:z) w.pb(u);
        sort(all(w),cmp);
        w.erase(unique(all(w)),w.end());
        for(int u:w) adj[u].clear();

        stack<int> st;
        for(int i:w)
        {
            while(st.size() && !anc(st.top(),i)) st.pop();
            if(st.size()) adj[st.top()].pb(i);
            st.push(i);
        }
        res = 0;
        for(int i:w) if(cl[i]!=imp) sol(i);
        cout << res << '\n';
    }
}
