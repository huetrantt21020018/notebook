/*
Đặt hố :
    Các cạnh đi ra từ s -> cap = oo
    Tìm lát cắt hẹp nhất gần làng -> c2
Đặt bia
    các cạnh có hố -> cap = oo
    Thu hồi trọng số các cạnh khác
    Tìm lát cắt hẹp nhất
*/

#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define int long long
#define pb push_back
using namespace std;
const int N=1001,MAX=1e15;
int n,m,s,t,e[N][N],E[N][N];
int dd[N],ss,flowval,pre[N];
vector<int> id[N][N];
bool findpath()
{
    queue<int> q;
    q.push(s);
    ++ss;
    dd[s]=ss;
    while(!q.empty())
    {
        int u=q.front(); q.pop();
        forinc(v,1,n) if(dd[v]!=ss&&e[u][v]>0)
        {
            dd[v]=ss;
            q.push(v);
            pre[v]=u;
            if(v==t) return true;
        }
    }
    return false;
}
void incflow()
{
    int u=t,flow=MAX;
    while(u!=s)
    {
        flow=min(flow,e[pre[u]][u]);
        u=pre[u];
    }
    u=t;
    flowval+=flow;
    while(u!=1)
    {
        e[pre[u]][u]-=flow;
        e[u][pre[u]]+=flow;
        u=pre[u];
    }
}
void latcatS(vector<int> &A)
{
    vector<int> X, Y;
    queue<int> q;
    q.push(s);
    ++ss;
    dd[s]=ss;
    while(!q.empty())
    {
        int u=q.front(); q.pop();
        X.pb(u);
        forinc(v,1,n) if(dd[v]!=ss&&e[u][v]>0)
        {
            dd[v]=ss;
            q.push(v);
        }
    }
    forinc(i,1,n) if(dd[i]!=ss) Y.pb(i);
    for(int u:X) for(int v:Y)
    {
        if(id[u][v].size()&&!e[u][v])
        {
            for(int i:id[u][v]) A.pb(i);
            e[u][v] = e[v][u] = MAX;
        }
    }
}
void latcatT(vector<int> &A)
{
    vector<int> X, Y;
    queue<int> q;
    q.push(t);
    ++ss;
    dd[t]=ss;
    while(!q.empty())
    {
        int u=q.front(); q.pop();
        Y.pb(u);
        forinc(v,1,n) if(dd[v]!=ss&&e[v][u]>0)
        {
            dd[v]=ss;
            q.push(v);
        }
    }
    forinc(i,1,n) if(dd[i]!=ss) X.pb(i);
    for(int u:X) for(int v:Y)
    {
        if(id[u][v].size()&&!e[u][v])
        {
            for(int i:id[u][v]) A.pb(i);
            E[u][v] = E[v][u] = MAX;
            e[u][v] = e[v][u] = MAX;
        }
    }
}
main()
{
    freopen("tiger.inp","r",stdin);
    freopen("tiger.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    forinc(i,1,m)
    {
        int u,v;
        cin>>u>>v;
        E[u][v]++;
        E[v][u]++;
        id[u][v].pb(i);
        id[v][u].pb(i);
    }
    vector<int> A, B;
    s = 1, t = n;
    forinc(u,1,n) forinc(v,1,n) e[u][v] = E[u][v];
    forinc(u,1,n) if(e[s][u]) e[s][u] = e[u][s] = MAX;
    while(findpath()) incflow();
    latcatT(A);

    s = 1, t = n;
    forinc(u,1,n) forinc(v,1,n) e[u][v] = E[u][v];
    while(findpath()) incflow();
    latcatS(B);
    cout << A.size() << ' ' << B.size() << '\n';
    for(int i:A) cout << i << ' ';
    cout << '\n';
    for(int i:B) cout << i << ' ';
}

