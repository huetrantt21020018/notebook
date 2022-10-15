#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
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
int main()
{
    frac a(3,-1);
    a.prinf();
}
