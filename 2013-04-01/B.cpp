#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<vector>
#define N 200
using namespace std;

vector<int>vec;
int mark[N];

int main()
{
    int n,m,i,j,x,ans;

    while (scanf("%d%d",&n,&m),n||m)
    {
        vec.clear();
        memset(mark,0,sizeof(mark));
        for (i=0;i<m;i++)
        {
            scanf("%d",&x);
            vec.push_back(x);
        }

        for (i=0;i<vec.size();i++)
            for (j=0;j<vec.size();j++)
            {
                x=abs(vec[i]-vec[j]);
                mark[x]=1;
            }

        ans=1;
        for (i=0;i<=n;i++)
        {
            //printf("%d ",mark[i]);
            if (mark[i]==0)
                ans=0;
        }

        if (ans)
            printf("Y\n");
        else
            printf("N\n");
    }

    return 0;
}
