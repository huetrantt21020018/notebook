#include <bits/stdc++.h>
#define forinc(i,a,b) for(int i=a;i<=b;++i)
using namespace std;
const int N=200000;
int n,a[N],pos[N],x,type;
vector<int> h;
void upheap(int i)
{
    int j=(i-1)/2;
    if(i==0||a[h[i]]>=a[h[j]]) return;
    swap(h[i],h[j]);
    swap(pos[h[i]],pos[h[j]]);
    upheap(j);
}
void downheap(int i)
{
    int j=2*i+1;
    if(h.size()<=j) return;
    if(h.size()>j+1&&a[h[j]]>a[h[j+1]]) ++j;
    if(a[h[i]]>a[h[j]])
    {
        swap(h[i],h[j]);
        swap(pos[h[i]],pos[h[j]]);
        downheap(j);
    }
}
void push(int i)
{
    h.push_back(i);
    int j=h.size()-1;
    pos[i]=j;
    upheap(j);
}
void pop(int i)
{
    h[i]=h[h.size()-1];
    pos[h[i]]=i;
    h.pop_back();
    downheap(i);
}
main()
{
    freopen("heapuri.inp","r",stdin);
    freopen("heapuri.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    int spt=0;
    forinc(i,1,n)
    {
        cin>>type;
        if(type==1)
        {
            cin>>x;
            a[++spt]=x;
            push(spt);
        }
        if(type==2)
        {
            cin>>x;
            pop(pos[x]);
        }
        if(type==3) cout<<a[h[0]]<<"\n";
    }
}
