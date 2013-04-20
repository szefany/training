#include "iostream"
#include "cstring"
#include "cstdio"
#include "vector"
#define PB push_back
using namespace std;
const int N = 60;
vector<int> edge[N*N];
int l[N][N],id[N][N];
char s[N][N];
int match[N*N],vis[N*N];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int dfs(int x)
{
	for(int i=0;i<edge[x].size();i++){
		int u=edge[x][i];
		if(!vis[u]){
			vis[u]=1;
			if(!match[u]||dfs(match[u])){
				match[u]=x;
				return 1;
			}
		}
	}
	return 0;
}
int n,m;
int gao()
{
	int sum=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(l[i][j]==0) continue;
			memset(vis,0,sizeof(vis));
			if(dfs(id[i][j])) sum++;
		}
	}
	return sum;
}
int main(void)
{
	
	freopen("input","r",stdin);
	while(scanf("%d %d",&n,&m)!=EOF){
		memset(l,0,sizeof(l));
		memset(match,0,sizeof(match));
		int tot=0;
		for(int i=0;i<n;i++){
			scanf("%s",s[i]);
			for(int j=0;j<m;j++){
				if(s[i][j]=='.'){
					id[i][j]=++tot;
					edge[tot].clear();
					if(i%2==j%2) l[i][j]=1;
				}
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(s[i][j]=='.'){
					for(int k=0;k<4;k++){
						int u=i+dx[k];
						int v=j+dy[k];
						if(u>=0&&u<n&&v>=0&&v<m){
							if(s[u][v]=='.'){
								edge[id[i][j]].PB(id[u][v]);
								edge[id[u][v]].PB(id[i][j]);
							}
						}
					}
				}
			}
		}
		if(gao()*2==tot){
			printf("2\n");
		}else{
			printf("1\n");
		}
	}
	return 0;
}