#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

const int N = 200000 + 1;

std::vector<int> total, neighbors[N];
int degree[N], edges[N][2], depth[N];
int n, m;

bool dfs(int u, int p) {
	depth[u] = p == 0 ? 0 : depth[p] + 1;
	bool result = false;
	for (int i = 0; i < neighbors[u].size(); ++ i) {
		int v = neighbors[u][i];
		if (v == p) {
			continue;
		}
		if (depth[v] != -1) {
			result = true;
		} else {
			result |= dfs(v, u);
		}
	}
	return result;
}

bool visit[N];
int length;
void dfs_2(int u, int p, int d) {
	if (d > length) {
		length = d;
	}
	visit[u] = true;
	for (int i = 0; i < neighbors[u].size(); ++ i) {
		int v = neighbors[u][i];
		if (!visit[v]) {
			dfs_2(v, u, d + 1);
		}
	}
}

int main() {
	freopen("input", "r", stdin);
	int number;
	while (scanf("%d%d", &number, &m) != EOF && number + m > 0) {
		total.clear();
		for (int i = 0; i < m; ++ i) {
			int u, v;
			scanf("%d%d", &u, &v);
			edges[i][0] = u;
			edges[i][1] = v;
			total.push_back(u);
			total.push_back(v);
		}
		std::sort(total.begin(), total.end());
		total.resize(unique(total.begin(), total.end()) - total.begin());

		n = total.size();
		for (int i = 0; i < n; ++ i) {
			neighbors[i].clear();
			degree[i] = 0;
		}
		
		bool flag = true;
		for (int i = 0; i < m; ++ i) {
			int u = std::lower_bound(total.begin(), total.end(), edges[i][0]) - total.begin();
			int v = std::lower_bound(total.begin(), total.end(), edges[i][1]) - total.begin();
			neighbors[u].push_back(v);
			neighbors[v].push_back(u);			
			// printf("%d %d\n", u, v);
		}

		for (int i = 0; i < n; ++ i) {
			std::sort(neighbors[i].begin(), neighbors[i].end());
			neighbors[i].resize(unique(neighbors[i].begin(), neighbors[i].end()) - neighbors[i].begin());
			if (neighbors[i].size() > 2) {
				flag = false;
				break;
			}
		}
		if (!flag) {
			puts("N");
			continue;
		}
		for (int i = 0; i < n; ++ i) {
			depth[i] = -1;
		}
		bool circle = false;
		for (int i = 0; i < n; ++ i) {
			if (depth[i] == -1) {
				circle |= dfs(i, -1);
			}
		}
		if (!circle) {
			puts("Y");
			continue;
		}

		memset(visit, 0, sizeof(visit));
		length = 0;
		dfs_2(0, -1, 0);
		puts(length == number - 1 ? "Y" : "N");
	}
	return 0;
}
