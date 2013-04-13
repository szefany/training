#include "iostream"
#include "cstring"
#include "cstdio"
#include "cmath"
using namespace std;
const int N = 310;
int step[N][N];
double f[N*N];
int a,b;
double ans1=0,ans2=0;
void dfs(int x,int y,double sum,double val,int st){	
	if(step[x][y]!=-1){
		ans1=2.0;
		ans2=val/(1-f[st-1]);
		ans2=0;
		double tt=1.0;
		double prev=-1;
		while(1){
			ans2+=val*tt;
			tt*=f[st-1];
			if(fabs(ans2-prev)<1e-6) break;
			else{
				prev=ans2;
			}
		}
		return ;
	}
	step[x][y]=st;
	if(x==y){
		ans1=f[st-1]*st+sum;
		ans2=val+f[st];
		return ;
	}
	if(x>y){
		dfs(x-y,2*y,sum+st*f[st],val+f[st],st+1);
	}else if(x<y){
		dfs(2*x,y-x,sum+st*f[st],val,st+1);
	}
}
int main(void)
{
	int T,g=0;
	f[0]=1;
	for(int i=1;i<=150*150;i++){
		f[i]=f[i-1]*0.5;
	}
	freopen("input","r",stdin);
	scanf("%d",&T);
	while(T--){
		memset(step,-1,sizeof(step));
		scanf("%d%d",&a,&b);
		printf("Case %d: ",++g);
		ans1=0.0,ans2=0.0;
		dfs(a,b,0,0.0,1);
		printf("%.6f %.6f\n",ans1,ans2);
	}
	return 0;
}