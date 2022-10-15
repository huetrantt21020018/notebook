#include <bits/stdc++.h>
using namespace std;
#define int long long
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r){return l+rng()%(r-l+1);}

#define forinc(a,b,c) for(int a=b,_c=c;a<=_c;++a)
#define fordec(a,b,c) for(int a=b,_c=c;a>=_c;--a)

const int N = 1e5+5;


main()
{
    #define task "  "
    srand(time(nullptr));
    for(;;)
    {
        ofstream cout(task".inp");

        int n = rnd(3,6);
        cout << n << '\n';
        forinc(i,1,n)
        {
            int a = rnd(1,10);
            cout << a << ' ';
        }

        cout.close();
        system(task".exe");
        system(task"1.exe");
        if(system("fc "task"1.out "task".out")) return cout<<"Wrong Answer :(((((",0;
        else cout << "Pretest Passed" << "\n";
    }
}

