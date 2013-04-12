#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 1010;
int a[N][N],b[N][N];
int pos[N*N][2];
int ab(int x)
{
	return x>0?x:-x;
}
void getnext(int &x,int &y,int i,int n)
{
	int dx,dy;
	if(x==i){
		if(y==n-i+1){
			dx=1;dy=0;
		}else{
			dx=0;dy=1;
		}
	}else if(x==n-i+1){
		if(y==i){
			dx=-1;dy=0;
		}else{
			dx=0;dy=-1;
		}
	}else if(y==i){
		dx=-1;dy=0;
	}else{
		dx=1;dy=0;
	}
	x+=dx;y+=dy;
}
int main(void)
{
	int n,g=0;
	freopen("input","r",stdin);
	while(scanf("%d",&n)&&n){
		int tot=0;
		memset(pos,0,sizeof(pos));		
		bool flag=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=++tot;
				scanf("%d",&b[i][j]);
				if(pos[b[i][j]][0]!=0){
					flag=0;
				}else{
					pos[b[i][j]][0]=i;
					pos[b[i][j]][1]=j;	
				}
			}
		}
		for(int i=1;i*2<=n+1;i++){
			int u=a[i][i];
			if(ab(pos[u][0])!=i&&ab(pos[u][1])!=i&&ab(n-pos[u][0]+1)!=i&&(n-pos[u][1]+1)!=i){
				flag=0;
				break;
			}
			if(n%2==1&&i*2==n+1){
				continue;
			}
			int step=(n-(i-1)*2)*4-4;
			int x0=i,y0=i,x1=pos[u][0],y1=pos[u][1];
			while(step--){
				if(a[x0][y0]!=b[x1][y1]){
					flag=0;break;
				}
				getnext(x0,y0,i,n);
				getnext(x1,y1,i,n);
			}
		}
		if(flag){
			printf("%d. YES\n",++g);
		}else{
			printf("%d. NO\n",++g);
		}
	}
	return 0;
}