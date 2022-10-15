// CSP 17.11.20
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define int long long
#define pii pair<int,int>
#define st first
#define nd second
#define all(a) a.begin(), a.end()

using namespace std;
const int N = 2002;

int m, n, k;

struct frac
{
    int a, b;
    frac (int x,int y): a(x), b(y)
    {
        int gcd = __gcd(a, b);
        a /= gcd; b /= gcd;
        if(b<0) a = -a, b = -b;
    }
    bool operator < (frac o) {
        return a*o.b < b*o.a;
    }
    bool operator == (frac o) {
        return a==o.a && b==o.b;
    }
    frac inverse() {
        return frac(b, a);
    }
    frac operator + (frac o) {
        return frac(a*o.b + b*o.a, b*o.b);
    }
    frac operator - (frac o) {
        return frac(a*o.b - b*o.a, b*o.b);
    }
    frac operator * (frac o) {
        return frac(a*o.a, b*o.b);
    }
    frac operator / (frac o) {
        return frac(a*o.b, b*o.a);
    }
    void prinf(){
        cout << a << ' ' << b << '\n';
    }
};
frac inv(0,0); // invalid

struct point
{
    frac x, y;
    bool operator < (point o) {
        if(x == o.x) return y < o.y;
        return x < o.x;
    }
    bool operator == (point o) {
        return x == o.x && y == o.y;
    }
    bool valid()
    {
        if(!x.b || !y.b) return 0;
        if(x==inv || y==inv) return 0;
        frac r(n+1,1), l(1,1);
        if(r<x || x<l) return 0;
        r = {m+1,1};
        if(r<y || y<l) return 0;
        return 1;
    }
};
struct line
{
    int A, B, C;
    bool operator < (line o) {
        if(A != o.A) return A < o.A;
        if(B != o.B) return B < o.B;
        return C < o.C;
    }
    bool operator == (line o) {
        return A==o.A && B==o.B && C==o.C;
    }
    /// đường thẳng đi qua (x1,y1) và (x2,y2)
    void init(int x1, int y1, int x2, int y2)
    {
        if(x1>x2 || (x1==x2 && y1>y2))
        {
            swap(x1, x2);
            swap(y1, y2);
        }
        A = y2-y1;
        B = x1-x2;
        C = A*x1 + B*y1;
        int gcd = __gcd(__gcd(A, B), C);
        A /= gcd; B /= gcd; C /= gcd;
        if(A<0 || (A==0&&B<0)) A = -A, B = -B, C = -C;
    }
    /// line a + line b = giao điểm 2 đường thẳng a, b
    point operator + (line o)
    {
        int D = A*o.B - o.A*B;
        int Dx = C*o.B - o.C*B;
        int Dy = A*o.C - o.A*C;
        if(!D) return {inv,inv};
        frac x(Dx, D);
        frac y(Dy, D);
        return {x, y};
    }
    void prinf()
    {
        cout << A << ' ' << B << ' ' << C << endl;
    }
};
struct segment
{
    line E;
    vector<point> inc;
    bool operator < (segment o) {
        return E < o.E;
    }
    bool operator == (segment o) {
        return E == o.E;
    }
};

struct geometry
{
    vector<segment> a;
    vector<point> p;
    int ver, seg;
    void AddSeg(int x1, int y1, int x2, int y2)
    {
        segment b;
        b.E.init(x1, y1, x2, y2);
        b.inc.clear();
        a.push_back(b);
    }
    void process()
    {
        sort(all(a));
        a.erase(unique(all(a)),a.end());

        for(int i=0; i<a.size(); ++i)
            for(int j=0; j<i; ++j)
            {
                point x = a[i].E + a[j].E;
                if(!x.valid()) continue;
                p.push_back(x);
                a[i].inc.push_back(x);
                a[j].inc.push_back(x);
            }
        sort(all(p));
        p.erase(unique(all(p)), p.end());
        ver = p.size();
        for(segment i:a)
        {
            sort(all(i.inc));
            i.inc.erase(unique(all(i.inc)),i.inc.end());
            seg += i.inc.size()-1;
            continue;
            i.E.prinf();
            cout << i.inc.size() << endl;
            for(point x:i.inc)
            {
                x.x.prinf(); x.y.prinf();
                cout << "\n";
            }
            cout << "\n-----\n";
        }
    }

}G;

int getx(int a)
{
    if(a<=n) return a;
    if(a<=m+n) return n+1;
    if(a<=m+2*n) return n+1-(a-(m+n+1));
    return 1;
}
int gety(int a)
{
    if(a<=n) return 1;
    if(a<=m+n) return a-n;
    if(a<=m+2*n) return m+1;
    return m+1-(a-(m+2*n+1));
}

main()
{
    freopen("gateau.inp","r",stdin);
    freopen("gateau.out","w",stdout);

    cin >> m >> n >> k;
    forinc(i,1,k)
    {
        int a, b;
        cin >> a >> b;
        if(a==b) continue;
        int x1 = getx(a), y1 = gety(a);
        int x2 = getx(b), y2 = gety(b);
//        cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
        G.AddSeg(x1, y1, x2, y2);
    }
    G.AddSeg(1,1,n+1,1);
    G.AddSeg(n+1,1,n+1,m+1);
    G.AddSeg(n+1,m+1,1,m+1);
    G.AddSeg(1,m+1,1,1);
    G.process();
    cout << G.seg - G.ver + 1;
}




/**
CT euler
Đồ thị phẳng liên thông
n đỉnh m cạnh
chia mp thành m-n+2 phần
*/
