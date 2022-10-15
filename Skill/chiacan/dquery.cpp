#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define getb(i) ((i-1)/t+1)
#define db(i) ((i-1)*t+1)
#define cb(i) (i*t)
using namespace std;
const int N=50000;
int n,a[N],ma[N],res,l=0,r=0,d[1000001],t,test;
struct tv
{
    int l,r,id,kq;
};
tv q[50000000];
void add(int i)
{
    if(!d[a[i]]) ++res;
    ++d[a[i]];
}
void rev(int i)
{
    --d[a[i]];
    if(!d[a[i]]) --res;
}
bool ss1(tv a,tv b)
{
    if(getb(a.l)!=getb(b.l)) return(getb(a.l)<getb(b.l));
    return (a.r<b.r);
}
bool ss2(tv a,tv b)
{
    return(a.id<b.id);
}
main()
{
    //freopen("dquery.inp","r",stdin);
    cin>>n;
    t=sqrt(n);
    forinc(i,1,n) cin>>a[i];
    cin>>test;
    forinc(i,1,test) {cin>>q[i].l>>q[i].r; q[i].id=i;}
    sort(q+1,q+test+1,ss1);
    forinc(i,1,test)
    {
        while(l<q[i].l) rev(l++);
        while(l>q[i].l) add(--l);
        while(r<q[i].r) add(++r);
        while(r>q[i].r) rev(r--);
        q[i].kq=res;
    }
    sort(q+1,q+test+1,ss2);
    forinc(i,1,test) cout<<q[i].kq<<"\n";
}
