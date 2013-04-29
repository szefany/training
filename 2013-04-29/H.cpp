#include "iostream"
#include "cstring"
#include "cstdio"
#include "queue"
using namespace std;
const int N = 100010;
const int M =1000010;
const int CH = 26;
const int inf = 0x3ffffff;
int trie[N][CH];
int word[N],fail[N];
int tot;
int ans[N];
char s[M],str[1010];
void init()
{
	tot=0;
	for(int i=0;i<CH;i++){
		trie[0][i]=0;
	}
	fail[0]=0;
	word[0]=inf;
}
void insert(char *s)
{
	int len=strlen(s);
	int r=0;
	for(int i=0;i<len;i++){
		int idx=s[i]-'a';
		if(trie[r][idx]==0){
			trie[r][idx]=++tot;
			for(int j=0;j<CH;j++){
				trie[tot][j]=0;
			}
			word[tot]=inf;
		}
		r=trie[r][idx];
	}
	word[r]=len;
}
void Build()
{
	queue<int> que;
	for(int i=0;i<CH;i++){
		int u=trie[0][i];
		if(u){
			fail[u]=0;
			que.push(u);
		}
	}
	while(!que.empty()){
		int u=que.front();
		word[u]=min(word[fail[u]],word[u]);
		que.pop();
		for(int i=0;i<CH;i++){
			int v=trie[u][i];
			if(v){
				fail[v]=trie[fail[u]][i];
				que.push(v);
			}else{
				trie[u][i]=trie[fail[u]][i];
			}
		}
	}
}
int Work()
{
	int len=strlen(s);
	ans[0]=0;
	int r=0;
	int v=0;
	for(int i=0;i<len;i++){
		int idx=s[i]-'a';
		r=trie[r][idx];
		if(word[r]==inf){
			ans[i+1]=ans[i]+1;
		}else{
			ans[i+1]=word[r]-1;
		}
		v=max(v,ans[i+1]);
	}
	return v;
}
int main(void)
{
	int n;
	freopen("input","r",stdin);
	while(scanf("%s",s)!=EOF){
		init();
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%s",str);
			insert(str);
		}
		Build();
		printf("%d\n",Work());
	}
	return 0;
}
