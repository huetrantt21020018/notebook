#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
#define fordec(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
const int N = 3e5+1;
int n, k, a[N];
int x[N], y[N], ma[N];
deque<int> Ma, Mi;
void push(int i)
{
    while(!Ma.empty()&&a[Ma.back()]<=a[i]) Ma.pop_back();
    Ma.push_back(i);
    while(!Mi.empty()&&a[Mi.back()]>=a[i]) Mi.pop_back();
    Mi.push_back(i);
}
void pop(int i)
{
    if(!Ma.empty()&&Ma.front()==i) Ma.pop_front();
    if(!Mi.empty()&&Mi.front()==i) Mi.pop_front();
}
int Max() {return a[Ma.front()];}
int Min() {return a[Mi.front()];}
int main()
{
    //freopen("kdiff.inp","r",stdin);

    cin >> n >> k;
    forinc(i,1,n) cin >> a[i];

    int j = 1;
    forinc(i,1,n)
    {
        push(i);
        while(Max()-Min()>k)
        {
            pop(j);
            ++j;
        }
        x[i] = i-j+1;
        ma[i] = max(ma[i-1],x[i]);
        y[i] = j-1;
    }
    int res = 0;
    forinc(i,1,n) res = max(res,x[i]+ma[y[i]]);
    cout << res;
}
