#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
typedef long long LOL;
LOL gcd(LOL a,LOL b)
{
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}
LOL a[5];
int main(void)
{
	int T;
	scanf("%d",&T);
	while(T--){
		for(int i=1;i<=4;i++){
			scanf("%lld",&a[i]);
		}
		LOL u=gcd(a[1],a[2]);
		if(u==0||a[3]%u!=0||a[4]%u!=0){
			printf("NO\n");
		}else{
			printf("YES\n");
		}
	}
	return 0;
}
