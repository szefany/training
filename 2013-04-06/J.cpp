#include "iostream"
#include "cstring"
#include "cstdio"
#include "algorithm"
using namespace std;
const int N = 510;
const int M = 1010;
int trie[N*M][26];
int word[N*M];
struct T
{
	char s[N];
	int len;
}tt[M];
bool cmp(T a,T b)
{
	return a.len<b.len;
}
int sz=0;
void insert(int x)
{
	int r=0;
	for(int i=0;i<tt[x].len;i++){
		int idx=tt[x].s[i]-'a';
		if(trie[r][idx]){
			r=trie[r][idx];
		}else{
			++sz;
			for(int j=0;j<26;j++){
				trie[sz][j]=0;
			}
			word[sz]=0;
			trie[r][idx]=sz;
			r=sz;
		}
	}
	word[r]++;
}
void reset()
{
	sz=0;
	for(int i=0;i<26;i++){
		trie[0][i]=0;
	}
}
char tmp[M];
char str[M*3];
int p[M*3];
bool check(int l,int r)
{
	int ll=l*2+2-1;
	int rr=r*2+2+1;
	int tx=(ll+rr)/2;
	if(p[tx]>=tx-ll+1){
		return true;
	}else{
		return false;
	}
}
int sum=0,n;
void manatcher(char *s)
{
	int len=strlen(s);
	p[0]=1;p[1]=1;p[2]=2;
	int id=2;
	for(int i=3;i<len;i++){
		int u=2*id-i;
		if(p[u]+i<p[id]+id){
			p[i]=p[u];
		}else{
			int j=p[id]+id-i;
			while(i+j<len&&s[i+j]==s[i-j]){
				j++;
			}
			p[i]=j;
			id=i;
		}
	}
}
int solve(){
	reset();
	for(int i=1;i<=n;i++){
		int len=tt[i].len;
		for(int j=0;j<len;j++){
			tmp[len-j-1]=tt[i].s[j];	
		}			
		tmp[len]='\0';
		str[0]='$';
		str[1]='#';
		for(int j=0;j<len;j++){
			str[j*2+2]=tmp[j];
			str[j*2+3]='#';
		}
		str[len*2+2]='\0';
		manatcher(str);
		int r=0;
		for(int j=0;j<len;j++){
			int idx=tmp[j]-'a';
			if(!trie[r][idx]){
				break;
			}else{				
				r=trie[r][idx];
				// printf("%d %d %d %d\n",i,j,r,word[r]);
				if(j==len-1||check(j+1,len-1)){
					sum+=word[r];
				}
			}
		}
		insert(i);
	}
}
int main(void)
{
	int T,g=0;
	freopen("input","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%s",tt[i].s);
			tt[i].len=strlen(tt[i].s);
		}
		sort(tt+1,tt+1+n,cmp);
		sum=0;
		solve();
		for(int i=1;i<=n;i++){
			reverse(tt[i].s,tt[i].s+tt[i].len);
		}
		solve();
		printf("Case #%d: %d\n",++g,sum);
	}
	return 0;
}

