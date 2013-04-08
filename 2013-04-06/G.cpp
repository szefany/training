#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 22000
#define M 440000
using namespace std;

struct Edge
{
    int u,v;

    Edge(){}
    Edge(int a,int b):u(a),v(b){}
};

int first[N],next[M],end[M];
int dfn[N],low[N],father[N],cnt[N];
char mark[N];
int cnt_edge,idx,num;
vector<Edge>bridge;

void addEdge(int u,int v)
{
    end[cnt_edge]=v;
    next[cnt_edge]=first[u];
    first[u]=cnt_edge++;
}
void reset(int n)
{
    for (int i=0;i<=n;i++)
        father[i]=i;
}

int find(int u)
{
    if (father[u]==u)
        return u;
    else
        return father[u]=find(father[u]);
}

void merge(int a,int b)
{
    int fa=find(a);
    int fb=find(b);

    if (fa!=fb)
        father[fa]=fb;
}

int tarjan(int u,int f)
{
    int i,v,flag;

    dfn[u]=low[u]=++idx;
    flag=0;

    for (i=first[u];i;i=next[i])
    {
        v=end[i];

        if (flag==0&&v==f)
        {
            flag=1;
            continue;
        }

        if (dfn[v]==0)
        {
            tarjan(v,u);

            low[u]=min(low[u],low[v]);

            if (dfn[u]<low[v])
                bridge.push_back(Edge(u,v));
            else
                merge(u,v);
        }
        else
            low[u]=min(low[u],dfn[v]);
    }
}

void dfs(int u)
{
    int i,v;

    mark[u]=1;
    num++;

    for (i=first[u];i;i=next[i])
    {
        v=end[i];

        if (cnt[v]==1&&mark[v]==0)
            dfs(v);
    }
}

int main()
{
    int t,n,m,i,j,u,v,ans,ys;

    scanf("%d",&t);
    ys=0;
    while (t--)
    {
        scanf("%d%d",&n,&m);

        memset(first,0,sizeof(first));
        memset(dfn,0,sizeof(dfn));
        memset(low,0,sizeof(low));
        memset(cnt,0,sizeof(cnt));
        memset(mark,0,sizeof(mark));
        cnt_edge=1;
        idx=0;
        bridge.clear();
        reset(n);

        for (i=0;i<m;i++)
        {
            scanf("%d%d",&u,&v);
            addEdge(u,v);
            addEdge(v,u);
        }

        for (i=1;i<=n;i++)
            if(dfn[i]==0)
                tarjan(i,0);
        for (i=1;i<=n;i++)
            cnt[find(i)]++;

        ans=0;
        for (i=1;i<=n;i++)
            if (cnt[i]==1&&mark[i]==0)
            {
                num=0;
                dfs(i);
                ans+=num*(num-1)/2;
            }

        printf("Case #%d: %d\n",++ys,ans);
    }

    return 0;
}
