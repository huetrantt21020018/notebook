#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N=1e6+1;
struct rec{int x1,y1,x2,y2;}a[N];// tọa độ các HCN
struct data{int x,y1,y2,tp;}b[2*N]; // các đoạn cần quan tâm xét theo chiều Oy
struct segment{int cnt,len;}t[4*N]; // cnt : số HCN đang mở | len : độ dài trong cây con t[]
bool cmp(data a,data b)
{
    if(a.x!=b.x) return a.x<b.x;
    return a.tp<b.tp;//xét đóng HCN trước
}
int n,m,nx,ny;
vector<int> rrhx,rrhy;
int X[N],Y[N];
long long res;
void upd(int s,int l,int r,int u,int v,int tp)
{
    if(l>v||r<u) return;
    if(l>=u&&r<=v)
    {
        t[s].cnt+=tp;
        if(t[s].cnt>0) t[s].len=Y[r]-Y[l-1];
        else t[s].len=t[2*s].len+t[2*s+1].len;
        return;
    }
    int mid=(l+r)/2;
    upd(2*s,l,mid,u,v,tp);
    upd(2*s+1,mid+1,r,u,v,tp);
    if(t[s].cnt==0) t[s].len=t[2*s].len+t[2*s+1].len;
}
main()
{
    freopen("lica.inp","r",stdin);
    freopen("lica.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    forinc(i,1,n)
    {
        cin>>a[i].x1>>a[i].y1>>a[i].x2>>a[i].y2;
        rrhx.push_back(a[i].x1);
        rrhx.push_back(a[i].x2);
        rrhy.push_back(a[i].y1);
        rrhy.push_back(a[i].y2);
    }
    sort(rrhx.begin(),rrhx.end());
    sort(rrhy.begin(),rrhy.end());
    rrhx.erase(unique(rrhx.begin(),rrhx.end()),rrhx.end());
    rrhy.erase(unique(rrhy.begin(),rrhy.end()),rrhy.end());
    forinc(i,1,n)
    {
        int z;
        z=lower_bound(rrhx.begin(),rrhx.end(),a[i].x1)-rrhx.begin()+1;
        X[z]=a[i].x1; a[i].x1=z;
        z=lower_bound(rrhx.begin(),rrhx.end(),a[i].x2)-rrhx.begin()+1;
        X[z]=a[i].x2; a[i].x2=z;
        z=lower_bound(rrhy.begin(),rrhy.end(),a[i].y1)-rrhy.begin()+1;
        Y[z]=a[i].y1; a[i].y1=z;
        z=lower_bound(rrhy.begin(),rrhy.end(),a[i].y2)-rrhy.begin()+1;
        Y[z]=a[i].y2; a[i].y2=z;
        b[++m]={a[i].x1,a[i].y1,a[i].y2,1};
        b[++m]={a[i].x2,a[i].y1,a[i].y2,-1};
    }
    nx=rrhx.size(), ny=rrhy.size();
    sort(b+1,b+m+1,cmp);
    forinc(i,1,m)
    {
        long long sq=1ll*t[1].len*(X[b[i].x]-X[b[i-1].x]);
        //cout<<b[i].x<<' '<<b[i].y1<<' '<<b[i].y2<<' '<<b[i].tp<<endl;
        //cout<<t[1].len<<' '<<X[b[i].x]<<' '<<X[b[i-1].x]<<endl;
        res+=sq;
        upd(1,1,ny,b[i].y1+1,b[i].y2,b[i].tp);
        //cout<<t[2].len<<' '<<t[3].len<<endl;
    }
    cout<<res;
}
