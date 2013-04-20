#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
#include<vector>
#define N 100100
#define M 200200
using namespace std;

int next[N],dis[N],step[N],father[N],color[N],len[N];
char mark[N],ins[N];
int idx;
int p[N][50];
stack<int>s;
vector<int>tree[N],edge[N];

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
        father[fb]=fa;
}

void floodfill(int u)
{
    int i,v;

    color[u]=idx;
    for (i=0;i<edge[u].size();i++)
    {
        v=edge[u][i];
        if (color[v]==0)
            floodfill(v);
    }
}

inline void Push(int x)
{
    mark[x]=1;
    ins[x]=1;
    s.push(x);
}

inline void Pop()
{
    ins[s.top()]=0;
    s.pop();
}

void dfs(int u)
{
    int v,i,j,cur;

    for (i=0;i<tree[u].size();i++)
    {
        v=tree[u][i];
        if (find(u)!=find(v))
            continue;
        //printf("v %d\n",v);
        cur=p[v][0]=u;
        dis[v]=dis[u]+1;
        //printf("%d %d\n",dis[u],dis[v]);
        for (j=0;cur!=-1&&p[cur][j]!=-1;j++)
        {
            p[v][j+1]=p[cur][j];
            cur=p[cur][j];
        }

        dfs(v);
    }
}

int lca(int u,int v)
{
    if (u==v)
        return u;

    if (dis[u]<dis[v])
        swap(u,v);

    int d=dis[u]-dis[v],k=0;

    while (d)
    {
        if (d&1)
            u=p[u][k];
        d>>=1;
        k++;
    }
    k=0;
    while (u!=v)
    {
        if (p[u][k]!=p[v][k]||(p[u][k]==p[v][k]&&k==0))
        {
            u=p[u][k];
            v=p[v][k];
            k++;
        }
        else
            k--;
    }

    return u;
}

int main()
{
    int n,q,i,j,u,v,d,cur,ans,tmp;

    freopen("dataJ.in","r",stdin);

    while(scanf("%d",&n)!=EOF)
    {
        memset(color,0,sizeof(color));
        memset(mark,0,sizeof(mark));
        memset(step,0,sizeof(step));
        memset(ins,0,sizeof(ins));
        memset(p,-1,sizeof(p));
        reset(n);

        for (i=0;i<=n;i++)
        {
            tree[i].clear();
            edge[i].clear();
        }

        for (i=1;i<=n;i++)
        {
            scanf("%d",&next[i]);
            tree[next[i]].push_back(i);
            edge[i].push_back(next[i]);
            edge[next[i]].push_back(i);
        }

        idx=0;
        for (i=1;i<=n;i++)
            if (color[i]==0)
            {
                idx++;
                floodfill(i);
            }
        //printf("pp\n");
        for (i=1;i<=n;i++)
            if (mark[i]==0)
            {
                cur=i;
                while (mark[cur]==0)
                {
                    Push(cur);
                    cur=next[cur];
                }
                //printf("cur %d\n",cur);
                if (ins[cur])
                {
                    d=0;
                    while (s.top()!=cur)
                    {
                        step[s.top()]=++d;
                        Pop();
                    }
                    step[cur]=++d;
                    len[color[cur]]=d;
                }
                while (!s.empty())
                {
                    merge(cur,s.top());
                    Pop();
                }
            }

        //printf("haha\n");

        for (i=1;i<=n;i++)
            if (father[i]==i)
        {
            dis[i]=0;
            dfs(i);
        }

        //for (i=1;i<=n;i++)
           // printf("%d ",father[i]);
        //printf("\n");
        scanf("%d",&q);
        while (q--)
        {
            scanf("%d%d",&u,&v);

            if (color[u]!=color[v])
                printf("-1\n");
            else
            {
                ans=0;

                if (find(u)==find(v))
                    ans=dis[u]+dis[v]-2*dis[lca(u,v)];
                else
                {
                    ans+=dis[u];
                    u=find(u);
                    ans+=dis[v];
                    v=find(v);
                    tmp=abs(step[u]-step[v]);
                    ans+=min(tmp,len[color[u]]-tmp);
                }
                printf("%d\n",ans);
            }
        }
    }

    return 0;
}














