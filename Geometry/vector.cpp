#include <bits/stdc++.h>
using namespace std;
struct point
{
    int x, y;
    bool operator < (point o) {
        if(x != o.x) return x < o.x;
        return y < o.y;
    }
};
struct Vector
{
    int x, y;
    Vector(int a,int b): x(a), y(b) {}
    Vector operator + (Vector a) {
        return Vector(x+a.x, y+a.y);
    }
    Vector operator - (Vector a){
        return Vector(x-a.x, y-a.y);
    }
    Vector operator * (Vector a){
        return Vector(x*a.x, y*a.y);
    }
    Vector Rotate(double cor){
		Vector o(0,0);
		o.x = x*cos(cor) - y*sin(cor);
		o.y = x*sin(cor) + y*cos(cor);
		return o;
	}
    double len(){
        return hypot(x, y);
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

int main()
{
    //freopen("angle.inp","r",stdin);
    int test; cin >> test;
    while(test--)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Vector a(x1,y1), b(x2,y2);
        double cos = 1.0*dot(a,b)/(a.len()*b.len());
        cout <<setprecision(6) << fixed<< acos(cos) << '\n';
    }
}
