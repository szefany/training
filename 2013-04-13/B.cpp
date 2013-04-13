#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 1100;
char s[N];
int vis[30];
int d[30];
bool f[30];
int main(void)
{
	int T,g=0,n,m;
	freopen("input","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%s",s);
		int len=strlen(s);
		printf("Case %d\n",++g);
		memset(d,0,sizeof(d));
		memset(f,0,sizeof(f));
		f[s[0]-'A']=1;
		for(int i=1;i<len;i++){
			if(f[s[i]-'A']!=0) continue;
			f[s[i]-'A']=1;
			memset(vis,0,sizeof(vis));
			for(int j=i-1;j>=0;j--){
				vis[s[j]-'A']++;
			}
			for(int j=i-1;j>=0;j--){
				if(vis[s[j]-'A']%2==1){
					d[s[j]-'A']++;
					d[s[i]-'A']++;
					break;
				}
			}
		}
		for(int i=0;i<26;i++){
			if(d[i]!=0){
				printf("%c = %d\n",'A'+i,d[i]);
			}
		}
	}
	return 0;
}