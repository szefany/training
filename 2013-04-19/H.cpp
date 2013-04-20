#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 200;
int vis[200];
int ab(int x)
{
	return x>0?x:-x;
}
int main(void)
{
	freopen("input","r",stdin);
	for(int i=0;i<720;i++){
		int x=(i*6)%360;
		int y=(i/12)*6;
		int u;
		if(x>y){
			u=x-y;			
		}else{
			u=y-x;
		}
		u=min(u,360-u);
		vis[u]=1;
	}	
	int n;
	while(scanf("%d",&n)!=EOF){
		if(vis[n]){
			printf("Y\n");
		}else{
			printf("N\n");
		}
	}
}