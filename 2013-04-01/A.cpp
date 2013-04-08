#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 100000 + 1;
const int D = 18;
const int M = N << 1;

struct Edge {
	int to, weight, next;
	Edge() {}
	Edge(int v, int w, int n): to(v), weight(w), next(n) {}
} g[M];
int first[N], edge_count;

void add_edge(int u, int v, int w) {
	edge_count ++;
	g[edge_count] = Edge(v, w, first[u]), first[u] = edge_count;
}

long long dist[N];
int depth[N], go[N][D];
int n, m;

void initialise() {
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < D; ++ j) {
			go[i][j] = -1;
		}
	}
	memset(first, 0, sizeof(first));
	edge_count = 0;
}

void dfs(int u, int p, int w) {
	depth[u] = p == -1 ? 0 : depth[p] + 1;
	dist[u] = p == -1 ? 0 : dist[p] + w;
	go[u][0] = p;
	for (int i = 0; go[u][i] != -1; ++ i) {
		go[u][i + 1] = go[go[u][i]][i];
	}
	for (int iter = first[u]; iter; iter = g[iter].next) {
		int v = g[iter].to;
		dfs(v, u, g[iter].weight);
	}
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

long long query(int u, int v) {
	int x = lca(u, v);
	return dist[u] + dist[v] - 2 * dist[x];
}

long long answer[N];

int main() {
	freopen("input", "r", stdin);
	while (scanf("%d", &n) != EOF && n) {
		initialise();
		for (int i = 1; i < n; ++ i) {
			int u, d;
			scanf("%d%d", &u, &d);
			add_edge(u, i, d);
		}
		dfs(0, -1, 0);
		scanf("%d", &m);
		int size = 0;
		while (m --) {
			int u, v;
			scanf("%d%d", &u, &v);
			answer[size ++] = query(u, v);
		}
		for (int i = 0; i < size; ++ i) {
			std::cout << answer[i];
			putchar(i == size - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
