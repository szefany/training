#include "iostream"
#include "cstring"
#include "cstdio"
#include "vector"
#include "queue"
#define PB push_back
#define MP make_pair
using namespace std;
const int N = 110;
const int Mod = 100000000;
const int inf = 0x3ffffff;
int a[N][2];
int dp[N][N];
int d[N];
vector<int> edge[N];
int main(void)
{
	int n,m;
	while(scanf("%d%d",&m,&n)&&(n||m)){
		for(int i=1;i<=n;i++){
			scanf("%d%d",&a[i][0],&a[i][1]);
		}
		int num = n+2;
		for(int i=0;i<num;i++){
			edge[i].clear();
		}
		memset(d,0,sizeof(d));
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++){
			if(a[i][0]==0){
				edge[0].PB(i);
				d[i]++;
			}
			if(a[i][1]==m){
				edge[i].PB(n+1);
				d[n+1]++;
			}
			for(int j=1;j<=n;j++){
				if(i==j) continue;
				if(a[j][0]<=a[i][1]&&a[j][0]>a[i][0]&&a[j][1]>a[i][1]){
					edge[i].PB(j);
					d[j]++;
				}
			}
		}
		queue<int> que;
		for(int i=0;i<edge[0].size();i++){
			int u=edge[0][i];
			dp[u][0]=1;
			d[u]--;
			if(d[u]==0){
				que.push(u);
			}
		}
		while(!que.empty()){
			int u=que.front();
			que.pop();
			for(int i=0;i<edge[u].size();i++){
				int x=edge[u][i];
				for(int j=0;j<num;j++){
					if(a[x][0]>a[j][1]&&dp[u][j]){						
						dp[x][u]+=dp[u][j];
						dp[x][u]%=Mod;
					}
				}
				d[x]--;
				if(d[x]==0){
					que.push(x);
				}
			}
		}
		int sum=0;
		for(int i=1;i<=n;i++){
			if(a[i][1]==m){
				for(int j=0;j<num;j++){
					sum+=dp[i][j];
					sum%=Mod;
				}
			}
		}
		printf("%d\n",sum);
	}
	return 0;
}
