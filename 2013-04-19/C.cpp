#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
const int N = 100010;
const int M = N*10;
int trie[M][26];
int son[M];
char s[N][85];
int tot=0;
void insert(int x)
{
	int r=0;
	int len=strlen(s[x]);
	for(int i=0;i<len;i++){
		int idx=s[x][i]-'a';
		if(trie[r][idx]){
			r=trie[r][idx];
		}else{
			trie[r][idx]=++tot;
			for(int j=0;j<26;j++){
				trie[tot][j]=0;
			}
			r=trie[r][idx];
		}
		son[r]++;
	}
}
void init()
{
	for(int i=0;i<26;i++){
		trie[0][i]=0;
	}
	memset(son,0,sizeof(son));
	tot=0;
}
int count(int x)
{
	int r=0;
	int len=strlen(s[x]);
	int sum=1;
	r=trie[r][s[x][0]-'a'];
	for(int i=1;i<len;i++){
		int idx=s[x][i]-'a';
		if(son[r]==son[trie[r][idx]]){
			r=trie[r][idx];
		}else{
			if(son[r]==1){
				return sum;
			}else{
				r=trie[r][idx];
				sum++;
			}
		}
	}
	return sum;
}
int main(void)
{
	int n;
	freopen("input","r",stdin);
	while(scanf("%d",&n)!=EOF){
		init();
		for(int i=1;i<=n;i++){
			scanf("%s",s[i]);
			insert(i);
		}
		double sum=0;
		for(int i=1;i<=n;i++){
			sum+=count(i);
		}
		sum/=n;
		printf("%.2lf\n",sum);
	}
	return 0;
}