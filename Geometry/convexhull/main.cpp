#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;
mt19937 Rand(time(0));
using lli = long long;
const int maxN = 1e5;

struct TVector
{
    lli x, y;
    TVector operator - (const TVector& other) const
    {
        return {x - other.x, y - other.y};
    }
    lli operator * (const TVector& other) const
    {
        return x * other.y - y * other.x;
    }
};
using TPoint = TVector;

int n, m;
TPoint p[maxN], q[maxN];
TPoint A;
ofstream f;

void ReadInput()
{
    n = 40;
    for (int i = 0; i < n; ++i)
    {
        p[i].x = (lli)Rand() % 2001 - 1000;
        p[i].y = (lli)Rand() % 2001 - 1000;
    }
}

lli d(const TPoint& a, const TPoint& b)
{
    lli x = a.x - b.x, y = a.y - b.y;
    return x * x + y * y;
}

void GrahamScan()
{
    int t = 0;
    for (int i = 1; i < n; ++i)
        if (p[i].y < p[t].y || (p[i].y == p[t].y && p[i].x < p[t].x))
            t = i;
    A = p[t];
    swap(p[t], p[0]);
    sort(p + 1, p + n + 1, [](const TPoint& B, const TPoint& C)
    {
        lli temp = (B - A) * (C - A);
        if (temp != 0) return temp > 0;
        return d(A, B) < d(A, C);
    });
    for (int i = 0; i < n; ++i)
        f << p[i].x << ' ' << p[i].y << '\n';
}

bool CCW(const TPoint& A, const TPoint& B, const TPoint& C)
{
    return (B - A) * (C - B) > 0;
}

void ConvexHull()
{
    m = 0;
    for (int i = 0; i < n; ++i)
    {
        while (m >= 2 && !CCW(q[m - 2], q[m - 1], p[i]))
            --m;
        q[m++] = p[i];
    }
    f << m << '\n';
    for (int i = 0; i < m; ++i)
        f << q[i].x << ' ' << q[i].y << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ReadInput();
    f.open("CONVEXHULL.TXT");

    f << n << '\n';
    for (int i = 0; i < n; ++i)
        f << p[i].x << ' ' << p[i].y << '\n';
    GrahamScan();
    ConvexHull();

    f.close();
    system("SHOWCONVEXHULL.EXE /3");
}
