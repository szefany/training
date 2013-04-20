#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 5010;
int a[N];
int vis[15];
int gao(int x)
{
	memset(vis,0,sizeof(vis));
	while(x!=0){
		if(vis[x%10]) return 0;
		vis[x%10]=1;
		x/=10;
	}
	return 1;
}
int main(void)
{
	freopen("input","r",stdin);
	for(int i=1;i<=5000;i++){
		a[i]=gao(i);
	}
	for(int i=2;i<=5000;i++){
		a[i]+=a[i-1];
	}
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF){
		printf("%d\n",a[m]-a[n-1]);
	}
	return 0;
}