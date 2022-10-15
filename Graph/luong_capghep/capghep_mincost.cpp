// https://codeforces.com/group/e2kzH9Ilfm/contest/302365/problem/C
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define pii pair<int,int>
#define st first
#define nd second

using namespace std;
const int maxn = 202;
double inf = 1000111000;
pii b[maxn], w[maxn];
int n, kq[maxn];

struct Hungary // code RR
{
    int nx, ny, maty[maxn], which[maxn];
    double cost[maxn][maxn], fx[maxn], fy[maxn], dist[maxn];
    bool used[maxn];

    void init(int _nx, int _ny)
    {
        nx = _nx;
        ny = _ny;
        memset(fx, 0, sizeof fx);
        memset(fy, 0, sizeof fy);
        for(int i=0; i<=nx; ++i)
            for(int j=0; j<=ny; ++j)
                cost[i][j] = inf;
    }

    void add(int x, int y, double c)
    {
        cost[x][y] = min(cost[x][y],c);
    }

    double mincost()
    {
        for(int x=1; x<=nx; ++x)
        {
            int y0 = 0;
            maty[0] = x;
            for(int y=0; y<=ny; ++y)
            {
                dist[y] = inf + 1;
                used[y] = false;
            }

            do
            {
                used[y0] = true;
                int x0 = maty[y0];
                double delta = inf + 1, y1;

                for(int y=1; y<=ny; ++y) if (!used[y])
                {
                    double curdist = cost[x0][y] - fx[x0] - fy[y];
                    if (curdist < dist[y])
                    {
                        dist[y] = curdist;
                        which[y] = y0;
                    }
                    if (dist[y] < delta)
                    {
                        delta = dist[y];
                        y1 = y;
                    }
                }

                for(int y=0; y<=ny; ++y) if (used[y])
                {
                    fx[maty[y]] += delta;
                    fy[y] -= delta;
                }
                else dist[y] -= delta;

                y0 = y1;
            }
            while (maty[y0] != 0);

            do
            {
                int y1 = which[y0];
                maty[y0] = maty[y1];
                y0 = y1;
            }
            while (y0);
        }
//      return -fy[0]; // nếu luôn đảm bảo có bộ ghép đầy đủ
        double ret = 0;
        for(int y=1; y<=ny; ++y)
        {
            int x = maty[y];
            if (cost[x][y] < inf) ret += cost[x][y];
            kq[x] = y;
        }
        return ret;
    }
} hungary;
double dist(pii a,pii b)
{
    int X = a.st - b.st;
    int Y = a.nd - b.nd;
    return sqrt(X*X + Y*Y);
}
int main()
{
//    freopen("conect.inp","r",stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    hungary.init(n,n);
    forinc(i,1,n) cin >> b[i].st >> b[i].nd;
    forinc(i,1,n) cin >> w[i].st >> w[i].nd;
    forinc(i,1,n) forinc(j,1,n) hungary.add(i,j,dist(b[i],w[j]));
    hungary.mincost();
    forinc(i,1,n) cout << kq[i] << '\n';
}

