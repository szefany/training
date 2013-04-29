#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
typedef long long LOL;
int main(void)
{
	int T;
	LOL S,H,vx,vy;
	freopen("input","r",stdin);
	scanf("%d",&T);
	while(T--){
		cin>>S>>H>>vx>>vy;
		LOL t=S/vx;
		LOL sum=vy*t-5*t*t;
		if(sum>=H){
			printf("good done!\n");
		}else{
			printf("poor Merida!\n");
		}
	}
	return 0;
}