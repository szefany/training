#include "iostream"
#include "cstring"
#include "cstdio"
#include "vector"
#include "queue"
#define PB push_back
using namespace std;
const int N = 1010;
vector<int> e[N];
int d[N];
queue<int> que;
int main(void)
{
	int n,m,x,y;
	while(scanf("%d%d",&n,&m)&&(n||m)){
		for(int i=1;i<=n;i++){
			d[i]=0;e[i].clear();
		}
		int sum=0;
		for(int i=1;i<=m;i++){
			scanf("%d%d",&x,&y);
			d[y]++;
			e[x].push_back(y);
		}
		bool flag=0;
		for(int i=1;i<=n;i++){
			if(d[i]==0){
				que.push(i);
				sum++;
			}
		}
		while(!que.empty()){
			if(que.size()>1){
				flag=1;
			}
			int u=que.front();
			que.pop();
			for(int i=0;i<e[u].size();i++){
				int v=e[u][i];
				d[v]--;
				if(d[v]==0){
					que.push(v);
					sum++;
				}
			}
		}
		if(sum<n){
			printf("0\n");
		}else if(flag==0){
			printf("1\n");
		}else{
			printf("2\n");
		}
	}	
	return 0;
}
