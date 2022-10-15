// CSP 8.11.20
#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N = 1005;

struct IT2D
{
    int n, m; // n hàng m cột
    vector<vector<int> > t;
    IT2D(int n,int m) : n(n), m(m), t(4*n,vector<int>(4*m,0)) {}
    ///____________Cực đại hóa ô(x,y) trong bảng với k____________
    void updc(int s1,int s,int l,int r,int i,int x)
    {
        if(l>i||r<i) return;
        if(l==r)
        {
            t[s1][s]=max(t[s1][s],x);
            return;
        }
        int mid=(l+r)/2;
        updc(s1,2*s,l,mid,i,x);
        updc(s1,2*s+1,mid+1,r,i,x);
        t[s1][s]=max(t[s1][2*s],t[s1][2*s+1]);
    }
    void upd(int s,int l,int r,int x,int y,int c)
    {
        if(l>x||r<x) return;
        updc(s,1,1,m,y,c);
        if(l==r) return;
        int mid=(l+r)/2;
        upd(2*s,l,mid,x,y,c);
        upd(2*s+1,mid+1,r,x,y,c);
    }
    void update(int x,int y,int c)
    {
        upd(1,1,n,x,y,c);
    }
    /// ____________Lấy max trong hcn(x,y)-(u-v)____________
    int getc(int s1,int s,int l,int r,int u,int v)
    {
        if(l>v||r<u) return 0;
        if(l>=u&&r<=v) return t[s1][s];
        int mid=(l+r)/2;
        return max(getc(s1,2*s,l,mid,u,v),getc(s1,2*s+1,mid+1,r,u,v));
    }
    int get(int s,int l,int r,int x,int y,int u,int v)
    {
        if(l>u||r<x) return 0;
        if(l>=x&&r<=u) return getc(s,1,1,m,y,v);
        int mid=(l+r)/2;
        return max(get(2*s,l,mid,x,y,u,v),get(2*s+1,mid+1,r,x,y,u,v));
    }
    int Max(int x,int y,int u,int v)
    {
        return get(1,1,n,x,y,u,v);
    }
};
int main()
{
    int n = 5, m = 6;
    IT2D it(n,m);
    it.update(2,3,3);
    it.update(2,5,4);
    it.update(4,4,5);
    cout << it.Max(1,1,4,5);
}

/* tham khảo thêm :
https://sites.google.com/site/kc97ble/container/segment-tree-2d
*/
