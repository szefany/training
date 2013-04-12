#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 10000000;
int prime[N+10];
int sum[N+10],num[N+10];
void getprime()
{
	int tot=0;
	for(int i=2;i<=N;i++){
		if(!prime[i]){
			prime[++tot]=i;
		}
		for(int j=1;j<=tot;j++){
			if((long long)((long long)i*(long long)prime[j])>N) break;		
			prime[prime[j]*i]=1;
			if(i%prime[j]==0){
				break;
			}
		}
	}
	for(int i=1;i<=tot;i++){
		int u=prime[i];
		num[u]++;
		if(u==2||u%4==1){
			sum[u]++;
		}
	}	
	for(int i=2;i<=N;i++){
		num[i]+=num[i-1];
		sum[i]+=sum[i-1];
	}
}
int main(void)
{
	getprime();
	freopen("input","r",stdin);
	int x,y;
	while(scanf("%d%d",&x,&y)!=EOF){
		if(x==-1&&y==-1) break;
		int tx=x,ty=y;
		if(x<=0) x=1;
		if(y<0) y=0;
		printf("%d %d %d %d\n",tx,ty,num[y]-num[x-1],sum[y]-sum[x-1]);
	}
	return 0;
}