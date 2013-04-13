#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 11000
#define M 88000
#define oo 10000000000000ll
using namespace std;

int first[N],next[M],end[M];
long long weight[N],dis[M];
int cnt_edge,idx,cnt_node,total;
int father[N],dfn[N],low[N];
int tree_size[N];
char mark[N],vis[N];
int flag,n;
long long limit;
vector<int>cpt[N];

void addEdge(int u,int v,long long w)
{
	end[cnt_edge]=v;
	dis[cnt_edge]=w;
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
		father[fb]=fa;
}

void tarjan(int u,int f)
{
	int i,v,flag;
	
	dfn[u]=low[u]=++idx;
	flag=0;
	
	for (i=first[u];~i;i=next[i])
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
			if (dfn[u]>=low[v])
				merge(u,v);
		}
		else
			low[u]=min(low[u],dfn[v]);
	}
}

int calc(int f)
{
	int i,j,u,v,sum,a,b;
	long long w;
	
	mark[f]=1;
	sum=cpt[f].size();
	
	for (i=0;i<cpt[f].size();i++)
	{
		u=cpt[f][i];
		for (j=first[u];~j;j=next[j])
		{
			v=end[j];
			w=dis[j];
			
			if (mark[find(v)]==0&&find(u)!=find(v))
			{
				a=calc(find(v));
				sum+=a;
				b=total-a;
				dis[j]=dis[j^1]=a*b*w;
			}
		}
	}
	
	return sum;
}

int dfs(int f,long long x)
{
	int u,v,i,j;
	long long cur,w,tot;
	
	mark[find(f)]=1;
	for (i=0;i<cpt[find(f)].size();i++)
	{
		u=cpt[find(f)][i];
		cur=weight[u];
		for (j=first[u];~j;j=next[j])
		{
			v=end[j];
			w=dis[j];
			
			if (mark[find(v)]==0&&find(u)!=find(v))
			{
				if (dfs(v,w)==0)
					cur+=w;
			}
		}		
		
		if (cur>limit)
			flag=0;
		if (u==f)
			tot=cur;
	}
	
	if (tot+x<=limit)
		return 1;
	else
		return 0;
}		
	
	
int check(long long x)
{
	int i,u;
	
	flag=1;
	limit=x;
	memset(mark,0,sizeof(mark));
	for (i=1;i<=n;i++)
		if (tree_size[i]>0)
			dfs(i,0);
	return flag;
}
	
int main()
{
	int t,i,j,m,u,v,ys;
	long long w;
	long long left,right,mid;
	
	scanf("%d",&t);
	ys=0;
	while (t--)
	{				
		scanf("%d%d",&n,&m);
		memset(first,-1,sizeof(first));
		memset(dfn,0,sizeof(dfn));
		memset(tree_size,0,sizeof(tree_size));
		reset(n);		
		cnt_edge=0;
		for (i=0;i<N;i++)
				cpt[i].clear();
				
		for (i=1;i<=n;i++)
			scanf("%lld",&weight[i]);
		for (i=0;i<m;i++)
		{
			scanf("%d%d%lld",&u,&v,&w);
			addEdge(u,v,w);
			addEdge(v,u,w);
		}
		
		for (i=1;i<=n;i++)
			if (dfn[i]==0)
			{				
				idx=0;
				tarjan(i,0);
				tree_size[find(i)]=idx;
			}
		for (i=1;i<=n;i++)
		{
			//printf("f %d\n",father[i]); 
			cpt[find(i)].push_back(i);
		}

		memset(mark,0,sizeof(mark));
		for (i=1;i<=n;i++)
			if (tree_size[i]>0)
			{
				total=tree_size[i];				
				calc(i);
				
			}
	
		left=0; right=oo;
		while (left<right)
		{
			mid=(left+right)/2;
			if (check(mid))
				right=mid;
			else
				left=mid+1;
		}
		printf("Case %d: %lld\n",++ys,left);
	}
	
	return 0;
}
