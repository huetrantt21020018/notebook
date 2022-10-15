// https://codeforces.com/group/FLVn1Sc504/contest/274493/problem/E
// CSP 3.12.20
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define pb push_back

const int N = 1e5+5;
int n, S[N], V[N];
vector<pii> ke[N];
int f[N], d[N];

struct convexhull_min
{
typedef pair<int,int> line;
#define a first
#define b second
const int inf = 1e9+7;
    int top;
    vector<line> st;
    vector<pair<int,line> > his;

    convexhull_min(int n) : top(0), st(n+5), his(0) {};

    int F(int i,int x)
    {
    	if(i > top) return inf;
        return st[i].a * x + st[i].b;
    }
    bool leave(line a,line b,line c)
    {
        if(b.a == c.a) return b.b >= c.b;
		double A = 1.0*(b.b-a.b)/(a.a-b.a);
        double B = 1.0*(c.b-b.b)/(b.a-c.a);
        return A>=B;
    }

    int Find_pos(line i)
    {
        int l = 2, r = top, ret = top; // no pos -> top unchange
        while(l<=r)
		{
			int m = (l+r)/2;
            if(leave(st[m-1],st[m],i))
			{
                ret = m-1;
                r = m - 1;
			}
			else l = m+1;
		}
		return ret;
    }
    void AddLine(int a,int b)
    {
    	line new_line = {a, b};
		int old_top = top;
        top = Find_pos(new_line)+1;
        line changed = st[top];
		st[top] = new_line;
		his.push_back({old_top, changed});
    }
    int GetMin(int x)
    {
		int l = 1, r = top, id = 1;
		while(l<=r)
		{
			int m = (l+r)/2;
            if(F(m,x) <= F(m+1,x))
			{
                id = m;
                r = m - 1;
			}
			else l = m + 1;
		}
		return F(id,x);
    }
    void rollback()
    {
        if(his.size())
		{
            int old_top = his.back().first;
            line changed = his.back().second;
            his.pop_back();
            st[top] = changed;
            top = old_top;
		}
    }
};

#define st first
#define nd second
void DFS(int u,int par,convexhull_min &C)
{
	for(pii i : ke[u]) if(i.st != par)
	{
		int v = i.st, c = i.nd;
        d[v] = d[u] + c;
        f[v] = C.GetMin(V[v]) + d[v]*V[v] + S[v];
        C.AddLine(-d[v], f[v]);
        DFS(v, u, C);
        C.rollback();
	}
}

main()
{
	//freopen("input.txt","r",stdin);

    cin >> n;
    forinc(i,1,n-1)
    {
    	int u, v, c;
    	cin >> u >> v >> c;
    	ke[u].push_back({v,c});
    	ke[v].push_back({u,c});
    }
    convexhull_min C(n+1);
    C.AddLine(0,0);
    forinc(i,2,n) cin >> S[i] >> V[i];
    DFS(1,0,C);
    forinc(i,2,n) cout << f[i] << ' ';
}