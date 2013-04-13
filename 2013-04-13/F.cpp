#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N=50;
char s[N],query[N];
char dic[50][20][50];
int gao(char ch)
{
	if(ch>='A'&&ch<='Z'){
		return ch-'A';
	}
	return ch-'0'+26;
}
int sum[20][50];
int main(void)
{
	freopen("input","r",stdin);
	int n,m;
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	for(int i=0;i<strlen(s);i++){
		for(int j=0;j<17;j++){
			scanf("%s",dic[gao(s[i])][j]);
		}
	}
	for(int i=0;i<m;i++){
		scanf("%s",s);
		int len=strlen(s);
		memset(sum,0,sizeof(sum));
		for(int j=0;j<len;j++){
			for(int k=0;k<17;k++){
				for(int x=0;x<43;x++){
					if(dic[gao(s[j])][k][x]=='*'){
						sum[k][x]++;
					}
				}
			}
		}
		printf("Query %d: ",i+1);
		for(int j=0;j<len;j++){
			bool flag=0;
			for(int k=0;k<17;k++){
				for(int x=0;x<43;x++){
					if(dic[gao(s[j])][k][x]=='*'&&sum[k][x]==1){
						flag=1;
					}
				}
			}
			if(flag){
				printf("Y");
			}else{
				printf("N");
			}
		}
		printf("\n");
	}
	return 0;
}