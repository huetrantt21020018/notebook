#include <bits/stdc++.h>
using namespace std;
int main()
{
    freopen("rectangles.inp","r",stdin);
    freopen("rectangles.out","w",stdout);
    int m,n;
    cin>>m>>n;
    long long res=0;
    for(int w=1;w<m;++w)
        for(int h=1;h<n;++h)
    {
        int sl=(m-w)*(n-h),dem=0;
        for(int a=1;a<=h;++a)
        {
            int delta=w*w-4*a*(h-a);
            if(delta<0) continue;
            else
            {
                int c1=(w+sqrt(delta))/2;
                int c2=(w-sqrt(delta))/2;
                if(c1>0)
                {
                    int re=c1*c1-w*c1+a*(h-a);
                    if(re==0) ++dem;
                }
                if(c2>0&&c2!=c1)
                {
                    int re=c2*c2-w*c2+a*(h-a);
                    if(re==0) ++dem;
                }
            }
        }
        res+=dem*sl;
    }
    cout<<res;
}
