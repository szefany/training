#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 100
using namespace std;

int perm[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
char mark[N];
int girl[10],boy[10];

int main()
{
    int n,m,i,j,x,flag,ans,cnt,tmp;

    while (1)
    {
        flag=0;
        memset(mark,0,sizeof(mark));
        for (i=0;i<3;i++)
        {
            scanf("%d",&girl[i]);
            mark[girl[i]]=1;
            if (girl[i])
                flag=1;
        }
        for (i=0;i<2;i++)
        {
            scanf("%d",&boy[i]);
            mark[boy[i]]=1;
            if (boy[i])
                flag=1;
        }

        if (flag==0)
            return 0;

        ans=0;
        for (i=0;i<6;i++)
        {
            cnt=0;
            for (j=0;j<2;j++)
                if (girl[perm[i][j]]<boy[j])
                    cnt++;
            //printf("%d\n",cnt);

            if (cnt==2)
            {
                tmp=1;
                while (mark[tmp])
                    tmp++;
                ans=max(ans,tmp);
            }
            else if (cnt==0)
                ans=53;
            else
            {
                tmp=girl[perm[i][2]];
                while (mark[tmp])
                    tmp++;
                ans=max(ans,tmp);
            }
        }

        if (ans>52)
            printf("-1\n");
        else
            printf("%d\n",ans);
    }

    return 0;
}

