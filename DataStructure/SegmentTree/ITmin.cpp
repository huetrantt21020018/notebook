#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
const int N = 1e5+1, MAX = 2e9;
int n;
struct ITmin
{
    int T[4*N], lz[4*N], L, R;
    /// ____________Truy vấn tăng____________
    void build_inc(int s,int l,int r)
    {
        if(l==r)
        {
            T[s] = 0;
            return;
        }
        int mid = (l+r)/2;
        build_inc(2*s,l,mid);
        build_inc(2*s+1,mid+1,r);
        T[s] = min(T[2*s], T[2*s+1]);
    }
    void transInc(int s)
    {
        if(lz[s]!=0)
        {
            lz[2*s] += lz[s];
            lz[2*s+1] += lz[s];
            T[2*s] += lz[s];
            T[2*s+1] += lz[s];
            lz[s] = 0;
        }
    }
    /// tăng các số trong đoạn (u-v) lên val
    void _updateInc(int s,int l,int r,int u,int v,int val)
    {
        if(l>v || r<u) return;
        if(l>=u && r<=v)
        {
            T[s] += val;
            lz[s] += val;
            return;
        }
        int mid = (l+r)/2;
        transInc(s);
        _updateInc(2*s,l,mid,u,v,val);
        _updateInc(2*s+1,mid+1,r,u,v,val);
        T[s] = min(T[2*s], T[2*s+1]);
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
        T[s] = min(T[2*s], T[2*s+1]);
    }
    void update_inc(int u,int v,int val)
    {
        if(u==v) updateInc(1,1,n,u,val);
        else _updateInc(1,1,n,u,v,val);
    }
    void reset_inc(int l,int r)
    {
        L = l, R = r;
        build_inc(1,l,r);
    }
    /// ____________Truy vấn cập nhật lấy min____________
    void build_min(int s,int l,int r)
    {
        lz[s] = MAX;
        if(l==r)
        {
            T[s] = MAX;
            return;
        }
        int mid = (l+r)/2;
        build_min(2*s,l,mid);
        build_min(2*s+1,mid+1,r);
        T[s] = min(T[2*s], T[2*s+1]);
    }
    void transMin(int s)
    {
        if(lz[s]!=MAX)
        {
            lz[2*s] = min(lz[2*s],lz[s]);
            lz[2*s+1] = min(lz[2*s+1],lz[s]);
            T[2*s] = min(T[2*s], lz[s]);
            T[2*s+1] = min(T[2*s+1], lz[s]);
            lz[s] = MAX;
        }
    }
    /// lấy min các số trong đoạn (u-v) với val
    void _updateMin(int s,int l,int r,int u,int v,int val)
    {
        if(l>v || r<u) return;
        if(l>=u && r<=v)
        {
            T[s] = min(T[s], val);
            lz[s] = min(lz[s], val);
            return;
        }
        int mid = (l+r)/2;
        transMin(s);
        _updateMin(2*s,l,mid,u,v,val);
        _updateMin(2*s+1,mid+1,r,u,v,val);
        T[s] = min(T[2*s], T[2*s+1]);
    }
    /// lấy min ai với val
    void updateMin(int s,int l,int r,int i,int val)
    {
        if(l>i || r<i) return;
        if(l==r)
        {
            T[s] = min(T[s], val);
            return;
        }
        int mid = (l+r)/2;
        updateMin(2*s,l,mid,i,val);
        updateMin(2*s+1,mid+1,r,i,val);
        T[s] = min(T[2*s], T[2*s+1]);
    }
    void update_min(int u,int v,int val)
    {
        if(u==v) updateMin(1,1,n,u,val);
        else _updateMin(1,1,n,u,v,val);
    }
    void reset_min(int l,int r)
    {
        L = l, R = r;
        build_min(1,l,r);
    }
    /// ____________Lấy min trong đoạn (u-v)____________
    int getmi(int s,int l,int r,int u,int v)
    {
        if(l>v || r<u) return MAX;
        if(l>=u && r<=v) return T[s];
        transInc(s);
        ///transMin(s);
        int mid = (l+r)/2;
        return min(getmi(2*s,l,mid,u,v), getmi(2*s+1,mid+1,r,u,v));
    }
    int get(int u,int v)
    {
        return getmi(1,1,n,u,v);
    }
}it1, it2;
int main()
{
    /// Tùy bài toán mà thay đổi
    /// Nếu upd đoạn phải trans làm getmi
    n = 5;
    it1.reset_inc(1,n);
    it1.update_inc(1,1,5);
    it1.update_inc(2,4,3);
    cout << it1.get(1,4) << endl;

    it2.reset_min(1,n);
    it2.update_min(1,3,3);
    it2.update_min(2,5,6);
    //it2.update_min(3,3,2);
    cout << it2.get(1,5) << endl;
}
