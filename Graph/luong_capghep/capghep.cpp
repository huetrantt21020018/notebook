// CSP 16.11.20
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define pb push_back

using namespace std;

const int N = 1e5+5;

struct CapGhep
{
    int nx, ny;
    vector<int> adj[N];
    int X[N], Y[N];
    int dd[N], selX[N], selY[N], ss;
    vector<int> S, resX, resY;
    bool found;
    /// ____________Số lượng đỉnh 2 phía lần lượt là nx, ny____________
    void init(int n,int m)
    {
        nx = n, ny = m;
        S.clear();
        forinc(i,1,nx) S.push_back(i);
        found = 0; ss = 0;
    }
    void AddEdge(int u,int v) {adj[u].push_back(v);}
    void DFS(int x)
    {
        for (int y: adj[x])
        {
            if (dd[y] == ss) continue;
            dd[y] = ss;
            if (X[y] == 0) found = 1;
            else DFS(X[y]);
            if (found)
            {
                X[y] = x;
                Y[x] = y;
                return;
            }
        }
    }
    /// ____________Cặp ghép cực đại____________
    int BipartiteMatching()
    {
        /// ____________Trả về số cặp ghép cực đại____________
        int bm = 0;
        for(;;)
        {
            int osz = S.size();
            ++ss;
            for (int i = S.size() - 1; i >= 0; --i)
            {
                found = 0;
                DFS(S[i]);
                if (found)
                {
                    ++bm;
                    S[i] = S.back();
                    S.pop_back();
                }
            }
            if(osz == S.size()) break;
        }
        return bm;
    }
    void prinfBiMatch()
    {
        cout << BipartiteMatching() << '\n';
        forinc(x,1,nx) if(Y[x]) cout << x << ' ' << Y[x] << '\n';
    }
    /// ____________Tập phủ đỉnh nhỏ nhất____________
    int VertexCover()
    {
        /// ____________Trả về số đỉnh phủ____________
        int sz = BipartiteMatching();
        forinc(x,1,nx) selX[x] = 0;
        forinc(y,1,ny) if(X[y]) selX[X[y]] = 1;
        forinc(y,1,ny) if(dd[y]==ss)
        {
            resY.push_back(y);
            if(X[y]) selX[X[y]] = 0;
        }
        forinc(x,1,nx) if(selX[x]) resX.push_back(x);
        return sz;
    }
    void PrinfVertCov()
    {
        int res = VertexCover();
        cout << res << '\n';
        for(int x:resX) cout << x << ' ';
        cout << '\n';
        for(int y:resY) cout << y << ' ';
        cout << '\n';
    }
    /// ____________Tập độc lập cực đại____________
    int IndependentSet()
    {
        /// ____________Trả về độ lớn tập đỉnh phủ____________
        int sz = nx + ny - BipartiteMatching();
        forinc(y,1,ny) selY[y] = (dd[y]!=ss);
        forinc(x,1,nx) selX[x] = 1;
        forinc(y,1,ny) if (dd[y]!=ss && X[y]) selX[X[y]] = 0;
        forinc(x,1,nx) if (selX[x]) resX.push_back(x);
        forinc(y,1,ny) if (selY[y]) resY.push_back(y);
        return sz;
    }
    void PrinfIndSet()
    {
        int res = IndependentSet();
        cout << resX.size() << ' ' << resY.size()  << '\n';
        for(int x:resX) cout << x << ' ';
        cout << '\n';
        for(int y:resY) cout << y << ' ';
        cout << '\n';
    }
    /// konig kc97ble
}bm;
int main()
{
    int m, n, k;
    cin >> m >> n >> k;
    bm.init(m,n);
    forinc(i,1,k)
    {
        int u, v;
        cin >> u >> v;
        bm.AddEdge(u,v);
    }
    bm.PrinfIndSet();
}
