#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 110;
long long a[N][N];
int main(void)
{
	int T,n,m;
	long long x;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%lld",&a[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%lld",&x);
				a[i][j]=min(x,a[i][j]);
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%lld",&x);
				a[i][j]*=x;
			}
		}
		long long sum=0;
		for(int i=1;i<=n;i++){
			long long maxx=-1;
			for(int j=1;j<=m;j++){
				maxx=max(maxx,a[i][j]);
			}
			sum+=maxx;
		}
		cout<<sum<<endl;
	}
	return 0;
}
