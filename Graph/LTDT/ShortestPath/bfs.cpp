#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N = 1e5+1;
int n, m;
vector<int> ke[N];
int d[N], fre[N], ss;
void bfs(int root)
{
    queue<int> q;
    d[root] = 0;
    fre[root] = ++ss;
    q.push(root);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v:ke[u]) if(fre[v] != ss)
        {
            fre[v] = ss;
            d[v] = d[u]+1;
            q.push(v);
        }
    }
}
main()
{
    cin >> n >> m;
    while(m--)
    {
        int u, v;
        cin >> u >> v;
        ke[u].push_back(v);
    }
    bfs(1);
}
