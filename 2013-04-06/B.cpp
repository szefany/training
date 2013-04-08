#include "iostream"
#include "cstring"
#include "algorithm"
#include "cstdio"
#include "vector"
#define PB push_back
#define MP make_pair
#define F first
#define S second
using namespace std;
const int N = 100010;
vector<pair<int,int> > edge[N];
int sum=0;
void dfs(int x,int pre,int pa)
{
	vector<int> v;
	for(int i=0;i<edge[x].size();i++){
		int u=edge[x][i].F;
		int w=edge[x][i].S;
		if(u==pa) continue;
		v.PB(w);
	}
	sort(v.begin(),v.end());
	if(v.size()==0) return ;
	int tmp=0;
	if(v.size()==1){
		tmp=v[0];
		sum+=max(0,tmp-pre);
	}else{
		int tx=0,ty=v[v.size()-1];
		for(int i=0;i<v.size()-1;i++){
			tx+=v[i];
		}
		if(tx>=ty){
			sum+=max((tx+ty+1-pre)/2,0);
		}else{
			if(pre>=ty-tx){
				sum+=max((tx+ty+1-pre)/2,0);
			}else{
				sum+=max(0,ty-pre);
			}			
		}
	}
	for(int i=0;i<edge[x].size();i++){
		int u=edge[x][i].F;
		int w=edge[x][i].S;
		if(u==pa) continue;
		dfs(u,w,x);
	}
}
int main(void)
{
	int T,n,x,y,w,g=0;
	freopen("input","r",stdin);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			edge[i].clear();
		}
		for(int i=1;i<n;i++){
			scanf("%d%d%d",&x,&y,&w);
			edge[x].PB(MP(y,w));
			edge[y].PB(MP(x,w));
		}
		sum=0;
		dfs(1,0,-1);
		printf("Case #%d: %d\n",++g,sum);
	}
	return 0;
}