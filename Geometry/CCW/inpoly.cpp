#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
#define int long long

using namespace std;

const int N = 5e3+5;

struct Vector{int x,y;};
struct Point{int x,y;};

Point a[N], B;

int n, m;

int ccw(Vector a,Vector b)
{
    return a.x*b.y - b.x*a.y;
}

int _ccw(Vector a,Vector b)
{
    int ret = a.x*b.y - b.x*a.y;
    if(ret<0) return -1;
    if(ret>0) return 1;
    return 0;
}

int cungphia(Point O, Point A, Point B,Point C)
{
    // ktra OB, OC co cung phia so voi OA ko
    Vector OA = {A.x-O.x, A.y-O.y};
    Vector OB = {B.x-O.x, B.y-O.y};
    Vector OC = {C.x-O.x, C.y-O.y};
    int ret = _ccw(OA,OB) * _ccw(OA,OC);
    if(ret<0) return -1;
    if(ret>0) return 1;
    return 0;
}

int tronggoc(Point O, Point A, Point B,Point C)
{
    // ktra OC co nam trong goc AOB ko (duoc nam tren canh)
    int ss = cungphia(O, A, B, C);
    if(ss==-1) return 0;
    ss = cungphia(O, B, A, C);
    if(ss==-1) return 0;
    return 1;
}
int trongtamgiac(Point A, Point B, Point C, Point D)
{
    // ktra OD co nam trong tam gia ABC ko
    if(!tronggoc(A, B, C, D)) return 0;
    if(!tronggoc(B, A, C, D)) return 0;
    if(!tronggoc(C, B, A, D)) return 0;
    return 1;
}

bool cungphuong(Point O, Point A, Point B)
{
    Vector OA = {A.x-O.x, A.y-O.y};
    Vector OB = {B.x-O.x, B.y-O.y};
    return _ccw(OA, OB)==0;
}

int Left(Point x)
{
    int l = 2, r = n, ret = 0;
    // vi tri xa nhat ma trong goc ko chua x
    while(l<=r)
    {
        int mid = (l+r)/2;
        if(!tronggoc(a[1],a[2],a[mid],x))
        {
            ret = mid;
            l = mid+1;
        }
        else r = mid-1;
    }
    return ret;
}
int dis(Point A, Point B)
{
    int X = A.x - B.x;
    int Y = A.y - B.y;
    return X*X + Y*Y;
}
main()
{
    freopen("inpoly.inp","r",stdin);
    freopen("inpoly.out","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n;
    forinc(i,1,n) cin >> a[i].x >> a[i].y;

    cin >> m;
    forinc(i,1,m)
    {
        cin >> B.x >> B.y;
        if(cungphuong(a[1],a[2],B)||cungphuong(a[1],a[n],B)||!tronggoc(a[1],a[2],a[n],B))
        {
            cout << 0 << '\n';
            continue;
        }
        if(n<=3)
        {
            if(cungphuong(a[2],a[3],B)) cout << 0 << '\n';
            else if(trongtamgiac(a[1],a[2],a[3],B)) cout << 1 << '\n';
            else cout << 0 << '\n';
            continue;
        }
        int l = Left(B), r = l+1;
        if(cungphuong(a[1],a[l],B))
        {
            if(dis(a[1],B) < dis(a[1],a[l])) cout << 1 << '\n';
            else cout << 0 << '\n';
            continue;
        }
        if(cungphuong(a[1],a[r],B))
        {
            if(dis(a[1],B) < dis(a[1],a[r])) cout << 1 << '\n';
            else cout << 0 << '\n';
            continue;
        }
        if(cungphuong(a[l],a[r],B))
        {
            cout << 0 << '\n';
            continue;
        }
        if(trongtamgiac(a[1],a[l],a[r],B)) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}

