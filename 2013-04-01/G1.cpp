//AC
#include "iostream"
#include "cstring"
#include "cstdio"
#include "string"
#include "algorithm"
#include "queue"
#define PB push_back
using namespace std;
const int N = 10010;
const int M = 1000010;
const int CH=26;
string s[N];
int trie[M][26],loc;
int fail[M];
int dp[N];
int word[M];
bool cmp(string a,string b)
{
	if(a.size()==b.size()){
		return a<b;
	}
	return a.size()<b.size();
}
void insert(string s,int x)
{
	int r=0;
	int len=s.size();
	for(int i=0;i<len;i++){
		int idx=s[i]-'a';
		if(trie[r][idx]){
			r=trie[r][idx];
		}else{
			trie[r][idx]=++loc;
			r=loc;
		}
	}
	word[r]=x;
}	
void ac()
{
	queue<int> que;
	for(int i=0;i<CH;i++){
		if(trie[0][i]){
			fail[trie[0][i]]=0;
			que.push(trie[0][i]);
		}
	}
	while(!que.empty()){
		int tmp=que.front();
		word[tmp]=max(word[tmp],word[fail[tmp]]);
		que.pop();
		for(int i=0;i<CH;i++){
			int u=trie[tmp][i];
			if(u){
				fail[u]=trie[fail[tmp]][i];
				que.push(u);
			}else{
				trie[tmp][i]=trie[fail[tmp]][i];
			}
		}
	}
}
int getsum(string s,int x)
{
	int len=s.size();
	int sum=0;
	int r=0;
	for(int i=0;i<len;i++){
		int idx=s[i]-'a';
		r=trie[r][idx];
		sum=max(sum,dp[word[r]]);
		if(i==len-1){
			sum=max(sum,dp[word[fail[r]]]);
		}
	}
	return sum+1;
}
int main(void)
{
	int n;
	while(scanf("%d",&n)&&n){
		for(int i=1;i<=n;i++){
			cin>>s[i];
		}
		loc=0;
		memset(trie,0,sizeof(trie));
		memset(word,0,sizeof(word));
		memset(dp,0,sizeof(dp));
		sort(s+1,s+1+n,cmp);
		for(int i=1;i<=n;i++){
			if(i==1||s[i]!=s[i-1])
			insert(s[i],i);
		}
		ac();
		int ans=1;
		for(int i=1;i<=n;i++){
			dp[i]=getsum(s[i],i);
			ans=max(ans,dp[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}