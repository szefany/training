#include "iostream"
#include "cstring"
#include "cstdio"
#include "string"
#include "map"
#include "sstream"
#include "vector"
#define PB push_back
using namespace std;
const int N = 100010;
vector<int> tree[N];
map<string,int> mp;
string s,tmp,str;
bool vis[N];
int dp[N][2],num1[N][2],num2[N][2];
int c1,c2;
int n;

void dfs(int u)
{
	int i,v,tmp1,tmp2,sum;
	
	dp[u][0]=dp[u][1]=0;
	num1[u][0]=num1[u][1]=num2[u][0]=num2[u][1]=0;
	sum=tmp1=tmp2=0;
	
	for (i=0;i<tree[u].size();i++)
	{
		v=tree[u][i];
		
		dfs(v);
		dp[u][0]+=dp[v][1];
		num1[u][0]+=num1[v][1];
		num2[u][0]+=num2[v][1];
		
		if (dp[v][0]<dp[v][1]||(dp[v][0]==dp[v][1]&&num1[v][0]+num2[v][0]<=num1[v][1]+num2[v][1]))
		{
			sum+=dp[v][0];
			tmp1+=num1[v][0];
			tmp2+=num2[v][0];
		}
		else
		{
			sum+=dp[v][1];
			tmp1+=num1[v][1];
			tmp2+=num2[v][1];
		}
	}
	
	sum+=c2;	
	
	if (sum<dp[u][0]+c1||(sum==dp[u][0]+c1&&tmp1+tmp2<=num1[u][0]+num2[u][0]))
	{
		dp[u][1]=sum;
		num1[u][1]=tmp1;
		num2[u][1]=tmp2+1;
	}
	else
	{
		dp[u][1]=dp[u][0]+c1;
		num1[u][1]=num1[u][0]+1;
		num2[u][1]=num2[u][0];
	}
}	
	
int main(void)
{	
	int ns,nf,ans,ys,d1,d2;
	
	mp.clear();
	scanf("%d%d\n",&d1,&d2);
	while(1)
	{
		c1=d1;
		c2=d2;
		if(c1==0&&c2==0) break;
		for(int i=0;i<N;i++)
		{
			tree[i].clear();
		}
		memset(vis,0,sizeof(vis));
		memset(num1,0,sizeof(num1));
		memset(num2,0,sizeof(num2));
		memset(dp,0,sizeof(dp));
		
		mp.clear();
		int tot=0;
		while(getline(cin,s))
		{				
			istringstream stream(s);			
			if(s[0]>='0'&&s[0]<='9')
			{
				stream>>d1>>d2;
				break;
			}
			vector<int> v;
			while(stream >>str)
			{
				if(mp[str]==0)
				{
					mp[str]=++tot;
				}
				v.PB(mp[str]);
			}
			for(int i=1;i<v.size();i++)
			{
				int u=v[i];
				vis[u]=1;
				tree[v[0]].PB(u);
			}
		}
		
		n=tot;
		ans=ns=nf=0;
		for (int i=1;i<=n;i++)
			if (vis[i]==0)
			{				
				dfs(i);
				ans+=dp[i][1];
				ns+=num1[i][1];
				nf+=num2[i][1];				
			}
				
			
		printf("%d. %d %d %d\n",++ys,ns,nf,ans);

	}
	return 0;
}
