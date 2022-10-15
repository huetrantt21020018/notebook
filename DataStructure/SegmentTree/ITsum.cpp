#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
const int N = 1e5+1;
int n;
struct ITsum
{
    int T[4*N], lz[4*N], L, R;
    /// ____________Truy vấn tăng____________
    void build(int s,int l,int r)
    {
        if(l==r)
        {
            T[s] = 0;
            return;
        }
        int mid = (l+r)/2;
        build(2*s,l,mid);
        build(2*s+1,mid+1,r);
        T[s] = T[2*s]+T[2*s+1];
    }
    void trans(int s,int l,int r)
    {
        if(lz[s]!=0)
        {
            lz[2*s] += lz[s];
            lz[2*s+1] += lz[s];
            int mid = (l+r)/2;
            T[2*s] += lz[s]*(mid-l+1);
            T[2*s+1] += lz[s]*(r-mid);
            lz[s] = 0;
        }
    }
    /// tăng các số trong đoạn (u-v) lên val
    void _updateInc(int s,int l,int r,int u,int v,int val)
    {
        if(l>v || r<u) return;
        if(l>=u && r<=v)
        {
            T[s] += val*(r-l+1);
            lz[s] += val;
            return;
        }
        int mid = (l+r)/2;
        trans(s,l,r);
        _updateInc(2*s,l,mid,u,v,val);
        _updateInc(2*s+1,mid+1,r,u,v,val);
        T[s] = T[2*s] + T[2*s+1];
    }
    /// tăng i lên val
    void updateInc(int s,int l,int r,int i,int val)
    {
        if(l>i || r<i) return;
        if(l==r)
        {
            T[s] += val;
            return;
        }
        int mid = (l+r)/2;
        updateInc(2*s,l,mid,i,val);
        updateInc(2*s+1,mid+1,r,i,val);
        T[s] = T[2*s] + T[2*s+1];
    }
    void update(int u,int v,int val)
    {
        if(u==v) updateInc(1,1,n,u,val);
        else _updateInc(1,1,n,u,v,val);
    }
    void reset(int l,int r)
    {
        L = l, R = r;
        build(1,l,r);
    }
    /// ____________Lấy tổng trong đoạn (u-v)____________
    int getsum(int s,int l,int r,int u,int v)
    {
        if(l>v || r<u) return 0;
        if(l>=u && r<=v) return T[s];
        trans(s,l,r);
        int mid = (l+r)/2;
        return getsum(2*s,l,mid,u,v)+getsum(2*s+1,mid+1,r,u,v);
    }
    int get(int u,int v)
    {
        return getsum(1,1,n,u,v);
    }
}it;
int main()
{
    /// Tùy bài toán mà thay đổi
    /// Nếu upd đoạn phải trans làm getsum
    n = 5;
    it.reset(1,n);
    it.update(1,4,1);
    it.update(3,5,2);
    it.update(2,2,5);
    cout << it.get(2,4);
}


