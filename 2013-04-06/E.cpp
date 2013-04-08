#include "iostream"
#include "cstring"
#include "vector"
#include "cstdio"
#include "algorithm"
#define PB push_back
#define MP make_pair
using namespace std;
const int N = 210;
int pos[N],hei[N];
int vis[N];
int dp[N][N];
int ab(int x)
{
	return x>0?x:-x;
}
struct T
{
	int x,y;
}tt[N];
bool cmp(T a,T b)
{
	return a.x<b.x;
}
int main(void)
{
	freopen("input","r",stdin);
	int T,g=0;
	scanf("%d",&T);
	while(T--){
		int maxx=0,n,h,w;
		scanf("%d %d %d",&n,&h,&w);
		vector<int> high;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&pos[i],&hei[i]);
			tt[i].x=pos[i];tt[i].y=hei[i];
			maxx=max(maxx,hei[i]);
		}
		sort(tt+1,tt+1+n,cmp);
		for(int i=1;i<=n;i++){
			pos[i]=tt[i].x;
			hei[i]=tt[i].y;
		}
		for(int i=1;i<=n;i++){
			if(maxx==hei[i]){
				high.PB(i);
			}
		}
		int flag=-1,ans=0x3ffffff;
		for(int i=0;i<high.size();i++){
			int u=high[i];
			memset(dp,-1,sizeof(dp));
			dp[u][pos[u]]=0;
			if(hei[u]<=h){
				flag=1;
				ans=0;
				break;
			}
			for(int j=u-1;j>=1;j--){
				if(hei[j]==maxx||hei[j]+h<hei[j+1])break;
				for(int k=0;k<=100;k++){
					if(dp[j+1][k]!=-1){
						for(int x=k-1;x>=0;x--){
							if(ab(k-x)>w) continue;
							// printf("%d %d %d %d\n",i,j,k,x);
							if(dp[j][x]==-1){
								dp[j][x]=dp[j+1][k]+ab(pos[j]-x)*hei[j];
							}else{
								dp[j][x]=min(dp[j][x],dp[j+1][k]+ab(pos[j]-x)*hei[j]);
							}		
							if(hei[j]<=h&&dp[j][x]!=-1){
								flag=1;
								ans=min(ans,dp[j][x]);
							}
						}
					}
				}
			}
			for(int j=u+1;j<=n;j++){
				if(hei[j]==maxx||hei[j]+h<hei[j-1])break;
				for(int k=0;k<=100;k++){
					if(dp[j-1][k]!=-1){
						for(int x=k+1;x<=100;x++){
							if(ab(k-x)>w) continue;
							if(dp[j][x]==-1){
								dp[j][x]=dp[j-1][k]+ab(pos[j]-x)*hei[j];
							}else{
								dp[j][x]=min(dp[j][x],dp[j-1][k]+ab(pos[j]-x)*hei[j]);
							}							
							if(hei[j]<=h&&dp[j][x]!=-1){
								flag=1;
								ans=min(ans,dp[j][x]);
							}
						}
					}
				}
			}
		}
		if(flag>0){
			printf("Case #%d: %d\n",++g,ans);
		}else{
			printf("Case #%d: %d\n",++g,-1);
		}
	}
	return 0;
}