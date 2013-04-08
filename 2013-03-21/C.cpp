#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 400000
using namespace std;

struct node
{
    long long pos;
    int cnt;

    node (){}
    node (long long a,int b):pos(a),cnt(b){}

    bool operator < (const node &a) const
    {
        if (pos==a.pos)
            return cnt>a.cnt;
        else
            return pos<a.pos;
    }
};

vector<node>vec;
long long p[N];
int type[N];

int main()
{
    int i,n,cur,maxc;
    long long ans,oo;

    scanf("%d",&n);
    oo=0;
    for (i=0;i<n;i++)
    {
        scanf("%d%lld",&type[i],&p[i]);
        oo=max(oo,p[i]+10);
    }

    for (i=0;i<n;i++)
        if (type[i]==1)
        {
            vec.push_back(node(p[i]+1,1));
            vec.push_back(node(oo,-1));
        }
        else if (type[i]==2)
        {
            vec.push_back(node(0,1));
            vec.push_back(node(p[i]-1,-1));
        }
        else if (type[i]==3)
        {
            vec.push_back(node(p[i],1));
            vec.push_back(node(p[i],-1));
        }
        else
        {
            vec.push_back(node(0,1));
            vec.push_back(node(p[i]-1,-1));
            vec.push_back(node(p[i]+1,1));
            vec.push_back(node(oo,-1));
        }

    sort(vec.begin(),vec.end());

    cur=0;
    ans=0;
    maxc=0;
    for (i=0;i<vec.size();i++)
    {
        cur+=vec[i].cnt;
        if (maxc<cur)
        {
            maxc=cur;
            ans=vec[i].pos;
        }
    }

    printf("%d %lld\n",maxc,ans);

    return 0;
}



