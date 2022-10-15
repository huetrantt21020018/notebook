// CTP 15.03.21

#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N = 1e5+1;
struct bitsum
{
    int n;
    vector<int> t;
    bitsum(int n) : n(n), t(n+1) {}
    void upd(int i,int x)
    {
        for(; i <= n; i += i&-i) t[i] += x;
    }
    int get(int i)
    {
        int kq = 0;
        for(; i > 0; i -= i&-i) kq += t[i];
        return kq;
    }
    int Find(int k)
    {
        int p = 1;
        while(p * 2 <= n) p *= 2;
        int x = 0;
        for(; p > 0; p /= 2)
        {
            int y = x + p;
            if(y <= n && t[y] < k) x = y, k -= t[y];
            // x = con lớn nhất có tổng (1...x) nhỏ hơn k
        }
        return x;
    }
};
struct bitmax
{
    int n;
    vector<int> t;
    bitmax(int n) : n(n), t(n+1) {}
    void upd(int i,int x)
    {
        for(; i<=n; i+=i&-i) t[i] = max(t[i], x);
    }
    int get(int i)
    {
        int kq = 0;
        for(; i>0; i-=i&-i) kq = max(kq, t[i]);
        return kq;
    }
};
int main()
{
    bitsum s(5);
    bitmax t(5);
    s.upd(1,5); s.upd(2,4);
    cout << s.get(3) << '\n';
    t.upd(1,5); t.upd(2,4);
    cout << t.get(3);
}
