#include <bits/stdc++.h>
using namespace std;

const double noSol = -LLONG_MAX, inf = LLONG_MAX;
const double pi = atan(1) * 4, esp = 1e-12;

struct point
{
    int x, y;
    point(int x, int y): x(x), y(y) {}
    const bool operator < (point o) {
        if(x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator == (point o) {
        return x == o.x && y == o.y;
    }
};

struct pointd
{
    double x, y;
    pointd(double x, double y): x(x), y(y) {}
    const bool operator < (pointd o) {
        if(x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator == (pointd o) {
        return x == o.x && y == o.y;
    }
};

pointd identical(inf, inf);
pointd parallel(noSol, inf);

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

    line(point a, point b)
    {
        if(a.x > b.x || (a.x == b.x && a.y > b.y))
        {
            swap(a.x, b.x);
            swap(a.y, b.y);
        }

        A = b.y - a.y;
        B = a.x - b.x;
        C = -(A*a.x + B*a.y);

        int gcd = __gcd(__gcd(A, B), C);
        A /= gcd; B /= gcd; C /= gcd;
        if(A<0 || (A==0&&B<0)) A = -A, B = -B, C = -C;
    }

    // giao diem 2 duong thang
    pointd operator + (line o)
    {
        int D = A*o.B - o.A*B;
        int Dx = o.C*B - C*o.B;
        int Dy = o.A*C - A*o.C;
        if(!D)
        {
            if(!Dx) return identical;
            return parallel;
        }
        return pointd(1.0 * Dx/D, 1.0 * Dy/D);
    }

    double dist(point I)
    {
        int ts = A*I.x + B*I.y + C;
        int ms2 = A*A + B*B;
        return 1.0 * abs(ts) / sqrt(ms2);
    }

    void prinf()
    {
        cout << A << ' ' << B << ' ' << C << endl;
    }
};

struct lined
{
    double A, B, C;

    lined (pointd a, pointd b)
    {
        if(a.x > b.x || (a.x == b.x && a.y > b.y))
        {
            swap(a.x, b.x);
            swap(a.y, b.y);
        }

        A = b.y - a.y;
        B = a.x - b.x;
        C = -(A*a.x + B*a.y);

        double g = sqrt(A*A + B*B);
        A /= g; B /= g; C /= g;
        if(A<0 || (A==0 && B<0)) A = -A, B = -B, C = -C;
    }

    // giao diem 2 duong thang
    pointd operator + (lined o)
    {
        double D = A*o.B - o.A*B;
        double Dx = o.C*B - C*o.B;
        double Dy = o.A*C - A*o.C;
        if(abs(D) < esp)
        {
            if(abs(Dx) < esp) return identical;
            return parallel;
        }
        return pointd(1.0 * Dx/D, 1.0 * Dy/D);
    }

    double dist(point I)
    {
        double ts = A*I.x + B*I.y + C;
        double ms2 = A*A + B*B;
        return 1.0 * abs(ts) / sqrt(ms2);
    }

    void prinf()
    {
        cout << A << ' ' << B << ' ' << C << endl;
    }
};

struct Vector
{
    int x, y;
    Vector(int a,int b): x(a), y(b) {}
    Vector(point A, point B): x(B.x-A.x), y(B.y-A.y) {}

    Vector operator + (Vector a) {
        return Vector(x+a.x, y+a.y);
    }
    Vector operator - (Vector a){
        return Vector(x-a.x, y-a.y);
    }
    Vector operator * (int a){
        return Vector(x*a, y*a);
    }
    Vector operator * (Vector a){
        return Vector(x*a.x, y*a.y);
    }

    double len(){
        return hypot(x, y);
    }

    void print() {
        cout << x << ' ' << y << endl;
    }
};

struct Vectord
{
    double x, y;
    Vectord(double a,double b): x(a), y(b) {}
    Vectord(pointd A, pointd B): x(B.x-A.x), y(B.y-A.y) {}

    Vectord operator + (Vectord a) {
        return Vectord(x+a.x, y+a.y);
    }
    Vectord operator - (Vectord a){
        return Vectord(x-a.x, y-a.y);
    }
    Vectord operator * (double a){
        return Vectord(x*a, y*a);
    }
    Vectord operator * (Vectord a){
        return Vectord(x*a.x, y*a.y);
    }

    Vectord Rotate(double cor){
        Vectord o(0,0);
        o.x = x*cos(cor) - y*sin(cor);
        o.y = x*sin(cor) + y*cos(cor);
        return o;
    }

    double len(){
        return sqrt(x*x + y*y);
    }

    void standard() {
        double d = hypot(x, y);
        x /= d;
        y /= d;
    }

    void print() {
        cout << x << ' ' << y << endl;
    }
};

int dot(Vector a, Vector b)
{
    Vector c = a*b;
    return c.x + c.y;
}
int ccw(Vector a, Vector b)
{
    return a.x*b.y - a.y*b.x;
}

double dist(pointd A, pointd B)
{
    return Vectord(A, B).len();
}
double dist(point A, point B)
{
    return Vector(A, B).len();
}

double alpha(Vector a, Vector b)
{
    double cos = 1.0 * dot(a,b) / (a.len()*b.len());
    return acos(cos);
}

double area(vector<pointd> &v)
{
    v.push_back(v[0]);

    double ret = 0;
    for(int i = 0; i < v.size() - 1; ++i)
        ret += (v[i].x - v[i+1].x) * (v[i].y + v[i+1].y);

    return abs(ret) / 2;
}

int main()
{

}
