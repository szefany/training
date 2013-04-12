#include "iostream"
#include "cstring"
#include "cstdio"
#include "algorithm"
using namespace std;
int a[10];
int main(void)
{
	freopen("input","r",stdin);
	while(scanf("%d%d%d%d%d%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5])!=EOF){
		sort(a,a+6);
		if(a[0]==0&&a[5]==0){
			break;
		}
		int sum=0;
		for(int i=1;i<=4;i++){
			sum+=a[i];
		}
		if(sum%4==0){
			printf("%d\n",sum/4);
		}else if(sum%4==1){
			printf("%d.25\n",sum/4);
		}else if(sum%4==2){
			printf("%d.5\n",sum/4);
		}else{
			printf("%d.75\n",sum/4);
		}
	}
	return 0;
}