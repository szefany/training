#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int mod = 1000000007;
const int N = 1000010;
int a[N];
long long val[N];
int main(void)
{
	int n;
	while(scanf("%d",&n)!=EOF)
	{
		long long ans=0;
		memset(val,0,sizeof(val));
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++){
			long long temp = val[a[i]];
			val[a[i]]=(ans+1)%mod;
			ans+=val[a[i]] - temp;
			// cout<<ans<<endl;
			ans=(ans%mod+mod)%mod;
		}
		cout<<ans<<endl;
	}
	return 0;
}