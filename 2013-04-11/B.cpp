#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 1000010;
char s[N];
int a[N];
int ans[N];
int main(void)
{
	int g=0;
	freopen("input","r",stdin);
	while(scanf("%s",s)){
		if(strcmp(s,"0")==0){
			break;
		}
		int len=strlen(s);
		for(int i=1;i<=len;i++){
			a[i]=s[len-i]-'0';
		}
		bool flag=0;
		for(int i=1;i<=len;i++){
			if(i==1){
				ans[1]=a[i];
			}else{
				ans[i]=a[i]-ans[i-1];
				if(ans[i]<0){
					ans[i]+=10;
					a[i+1]--;
				}
			}
		}
		printf("%d. ",++g);
		if(ans[len]<=0){
			printf("IMPOSSIBLE\n");
		}else{
			for(int i=len;i>=1;i--){
				printf("%d",ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}