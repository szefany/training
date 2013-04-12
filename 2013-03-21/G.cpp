#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <climits>
#include <map>

const int N = 200000 + 1;
const int D = 20;

std::vector<int> neighbors[N];
int go[N][D], enter[N], leave[N], depth[N], number[N], roots[N + N];
int n, counter;

void dfs(int u, int p) {
	depth[u] = p == -1 ? 1 : depth[p] + 1;
	go[u][0] = p;
	for (int i = 0; go[u][i] != -1; ++ i) {
		go[u][i + 1] = go[go[u][i]][i];
	}
	enter[u] = ++ counter;
	for (int iter = 0; iter < neighbors[u].size(); ++ iter) {
		int v = neighbors[u][iter];
		if (v != p) {
			dfs(v, u);
		}
	}
	leave[u] = ++ counter;
}

int jump(int u, int d) {
	for (int i = D - 1; i >= 0; -- i) {
		if (d >= 1 << i) {
			d -= 1 << i;
			u = go[u][i];
		}
	}
	return u;
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) {
		std::swap(u, v);
	}
	u = jump(u, depth[u] - depth[v]);
	for (int i = D - 1; i >= 0; -- i) {
		if (go[u][i] != go[v][i]) {
			u = go[u][i];
			v = go[v][i];
		}
	}
	return u == v ? u : go[u][0];
}

int lowbit(int x)
{
	return x&(-x);
}
int c[32][N];
void update(int col,int x,int t)
{
	int u=x;
	while(u<=n){
		c[col][u]+=t;
		u+=lowbit(u);
	}
}
int getsum(int col,int x)
{
	int sum=0;
	while(x>0){
		sum+=c[col][x];
		x-=lowbit(x);
	}
	return sum;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++ i) {
		int u, v;
		scanf("%d%d", &u, &v);
		neighbors[u].push_back(v);
		neighbors[v].push_back(u);
	}
	memset (go, -1, sizeof(go));
	dfs(0, -1);	
	int m;
	scanf("%d", &m);
	n*=2;
	while (m --) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int u, c;
			scanf("%d%d", &u, &c);
			update(c,enter[u],1);
			update(c,leave[u],-1);
			number[u]=c;
		} else {
			int u, v;
			scanf("%d%d", &u, &v);
			int s = lca(u, v);
			int length = depth[u] + depth[v] - 2 * depth[s] + 1;
			if (number[u] != number[v] || number[u]==0||number[u] > 30) {
				puts("NO");
			} else {
				int temp =getsum(number[u],enter[u])+getsum(number[u],enter[v])-2*getsum(number[u],enter[s]);
				if(number[s]==number[u]){
					temp++;
				}
				puts(temp == length ? "YES" : "NO");
			}
		}
	}
	return 0;
}
