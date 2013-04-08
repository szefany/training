#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 310;
double c[N][N];
double dp[N][N];
int vis[N][N];
double getdp(int x,int y)
{
	if(vis[x][y]){
		return dp[x][y];
	}
	vis[x][y]=1;
	if(x==0){
		return dp[x][y]=0;
	}
	if(x==1){
		return dp[x][y]=y;
	}
	if(y==0){
		return 0;
	}
	double sum=0;
	for(int i=0;i<=x;i++){
		sum+=c[x][i]*(getdp(i,y-1)+((i==0)?0:1)+getdp(x-i,y-1)+(i==x?0:1));
	}
	return dp[x][y]=sum;
}
int main(void)
{
	int T,n,m;
	c[0][0]=1;
	for(int i=1;i<=300;i++){
		c[i][0]=c[i-1][0]/2.0;
	}
	for(int i=1;i<=300;i++){
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])/2.0;
		}
	}
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		printf("%.2f\n",getdp(n,m)+1.0);
	}
	return 0;
}
