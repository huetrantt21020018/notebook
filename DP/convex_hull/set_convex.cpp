#include<bits/stdc++.h>
using namespace std;
#define forinc(a,b,c) for(int a=b, _c=c; a<=_c; ++a)

const int N=200005;
int n,a[N],s[N];
const int INF=2e18;
int mode=0;
struct line
{
    mutable int a,b;
    mutable double k;
    bool operator<(const line &p)const
    {
        return mode? k<p.k : a<p.a;
    }
};

double G(line x,line y)
{
    return 1.0*(x.b-y.b)/(y.a-x.a);
}

struct hull_max
{
    multiset<line> st;
    int s() { return st.size(); }
    int bad(auto x,auto y)
    {
        if(y==end(st)) return x->k=INF, 0;
        if(x->a==y->a) x->k=(x->b>=y->b?INF:-INF);
        else x->k=G(*x,*y);
        return x->k>=y->k;
    }
    void add(int a,int b)
    {
        line new_;
        new_.a = a,new_.b=b;
        new_.k = 0;
        auto z = st.insert(new_), x = z++, y = x;
        while(bad(x,z)) z=st.erase(z);
        if(x!=begin(st) && bad(--x,y))
            bad(x,st.erase(y));
        while((y=x) != begin(st) && bad(--x,y))
            bad(x,st.erase(y));
    }
    int que(int x)
    {
        mode=1;
        line new_;
        new_.a = new_.b=-INF;
        new_.k = x;
        auto pos = st.lower_bound(new_);
        mode = 0;
        if(pos == end(st)) return -INF;
        return (pos->a * x + pos->b);
    }
}p;

int main()
{
    cin>>n;
    forinc(i,1,n) cin>>a[i], a[i]+=a[i-1];

    forinc(i,1,n) s[i]=s[i-1]+a[i];

    p.add(0,0);
    int ans=0;
    forinc(i,1,n)
    {
        ans = max(ans, p.que(-i)+s[i]);
        p.add(a[i], -s[i]+i*a[i]);
    }
    cout<<ans;
}
