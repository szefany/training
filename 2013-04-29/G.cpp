#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

long long n,x1,x2,x3,y1,y2,y3;

long long calc(long long a)
{
    long long l,r;

    l=x2;
    l=max(l,n-a-y3);
    l=max(l,a);
    l=max(l,(n-2*a)/2+1);

    r=y2;
    r=min(r,n-a-x3);
    r=min(r,(n-a)/2);

    long long res=r-l+1;

    return res>0?res:0;
}

int main()
{
    long long i;
    long long ans;

    while (cin>>n)
    {
        cin>>x1>>y1>>x2>>y2>>x3>>y3;
        ans=0;
        for (i=x1;i<=y1;i++)
            ans+=calc(i);
        cout<<ans<<endl;
    }

    return 0;
}



