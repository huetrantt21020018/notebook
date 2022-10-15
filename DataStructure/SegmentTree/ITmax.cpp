#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
const int N = 1e5+1, MIN = -2e9;
int n;
struct ITmax
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
        T[s] = max(T[2*s], T[2*s+1]);
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
        T[s] = max(T[2*s], T[2*s+1]);
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
        T[s] = max(T[2*s], T[2*s+1]);
    }
    void update_inc(int u,int v,int val)
    {
        if(u==v) updateInc(1,L,R,u,val);
        else _updateInc(1,L,R,u,v,val);
    }
    void reset_inc(int l,int r)
    {
        L = l, R = r;
        build_inc(1,l,r);
    }
    /// ____________Truy vấn cập nhật lấy max____________
    void build_max(int s,int l,int r)
    {
        lz[s] = MIN;
        if(l==r)
        {
            T[s] = MIN;
            return;
        }
        int mid = (l+r)/2;
        build_max(2*s,l,mid);
        build_max(2*s+1,mid+1,r);
        T[s] = max(T[2*s], T[2*s+1]);
    }
    void transmax(int s)
    {
        if(lz[s]!=MIN)
        {
            lz[2*s] = max(lz[2*s],lz[s]);
            lz[2*s+1] = max(lz[2*s+1],lz[s]);
            T[2*s] = max(T[2*s], lz[s]);
            T[2*s+1] = max(T[2*s+1], lz[s]);
            lz[s] = MIN;
        }
    }
    /// lấy max các số trong đoạn (u-v) với val
    void _updatemax(int s,int l,int r,int u,int v,int val)
    {
        if(l>v || r<u) return;
        if(l>=u && r<=v)
        {
            T[s] = max(T[s], val);
            lz[s] = max(lz[s], val);
            return;
        }
        int mid = (l+r)/2;
        transmax(s);
        _updatemax(2*s,l,mid,u,v,val);
        _updatemax(2*s+1,mid+1,r,u,v,val);
        T[s] = max(T[2*s], T[2*s+1]);
    }
    /// lấy max ai với val
    void updatemax(int s,int l,int r,int i,int val)
    {
        if(l>i || r<i) return;
        if(l==r)
        {
            T[s] = max(T[s], val);
            return;
        }
        int mid = (l+r)/2;
        updatemax(2*s,l,mid,i,val);
        updatemax(2*s+1,mid+1,r,i,val);
        T[s] = max(T[2*s], T[2*s+1]);
    }
    void update_max(int u,int v,int val)
    {
        if(u==v) updatemax(1,L,R,u,val);
        else _updatemax(1,L,R,u,v,val);
    }
    void reset_max(int l,int r)
    {
        L = l, R = r;
        build_max(1,l,r);
    }
    /// ____________Lấy max trong đoạn (u-v)____________
    int getma(int s,int l,int r,int u,int v)
    {
        if(l>v || r<u) return MIN;
        if(l>=u && r<=v) return T[s];
        ///transInc(s);
        ///transmax(s);
        int mid = (l+r)/2;
        return max(getma(2*s,l,mid,u,v), getma(2*s+1,mid+1,r,u,v));
    }
    int get(int u,int v)
    {
        return getma(1,L,R,u,v);
    }
}it1, it2;
int main()
{
    /// Tùy bài toán mà thay đổi
    /// Nếu upd đoạn phải trans làm getma
    /// luôn phải reset trc khi dùng it
    n = 5;
    it1.reset_inc(1,n);
    it1.update_inc(1,3,5);
    it1.update_inc(2,4,3);
    cout << it1.get(1,4) << endl;

    it2.reset_max(1,n);
    it2.update_max(1,3,3);
    it2.update_max(2,5,6);
    it2.update_max(3,3,2);
    cout << it2.get(1,5) << endl;
}

