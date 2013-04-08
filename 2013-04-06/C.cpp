#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
typedef long long ll;
const int N = 10;
const int M = 10000;
ll a[M][N];
ll s[M];
int main(void)
{
	int T,g=0;
	// freopen("input","r",stdin);
	scanf("%d",&T);
	ll maxx;
	while(T--){
		printf("Case #%d: ",++g);
		ll sum=0;
		for(int i=1;i<=5;i++){
			scanf("%lld",&a[1][i]);
			sum+=a[1][i];
		}
		s[1]=sum;
		scanf("%lld",&maxx);
		if(sum>=maxx){
			printf("0\n");
			continue;
		}
		int flag=-1;
		for(int i=2;;i++){
			ll tmp=0;
			a[i][1]=a[i-1][1]+a[i-1][2];
			a[i][2]=a[i-1][2]+a[i-1][3];
			a[i][3]=a[i-1][3]+a[i-1][4];
			a[i][4]=a[i-1][4]+a[i-1][5];
			a[i][5]=a[i-1][5]+a[i-1][1];
			for(int j=1;j<=5;j++){
				tmp+=a[i][j];
			}
			s[i]=tmp;
			if(s[i]<=s[i-1]){
				break;
			}
			if(s[i]>=maxx){
				flag=i-1;
				break;
			}
		}
		printf("%d\n",flag);
	}
}