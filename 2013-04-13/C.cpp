#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 1100;
char s[N];
int main(void)
{
	int T,g=0,n,m;
	freopen("input","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %s",&n,&m,s);
		int sum=0;
		for(int i=0;i<n;i++){
			int flag=0;
			for(int j=i-1;j>=max(i-m,0);j--){
				if(s[j]==s[i]){
					flag=1;
				}
			}
			sum+=flag;
		}
		printf("Case %d: %d\n",++g,sum);
	}
	return 0;
}