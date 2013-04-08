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

const int M = N << 1;
int key[M], value[M], weight[M], sum[M], children[M][2];
int size;

void update(int u) {
	sum[u] = sum[children[u][0]] + value[u] + sum[children[u][1]];
}

void rotate(int &u, int d) {
	int v = children[u][d];
	children[u][d] = children[v][d ^ 1];
	children[v][d ^ 1] = u;
	update(u);
	update(v);
	u = v;
}

void insert(int &u, int k, int v) {
	if (u == 0) {
		u = ++ size;
		weight[u] = rand();
		key[u] = k;
		value[u] = v;
		children[u][0] = children[u][1] = 0;
	} else {
		int d = k > key[u];
		insert(children[u][d], k, v);
		if (weight[children[u][d]] < weight[u]) {
			rotate(u, d);
		}
	}
	update(u);
}

void erase(int &u, int k) {
	if (u == 0) {
		children[u][0] = children[u][1] = sum[u] = value[u] = key[u] = 0;
	} else {
		if (key[u] == k) {
			rotate(u, weight[children[u][1]] > weight[children[u][0]]);
			erase(u, k);
		} else {
			erase(children[u][k > key[u]], k);
		}
		update(u);
	}
}

int query(int u, int k) {
	int result;
	if (u == 0) {
		result = 0;
	} else if (k < key[u]) {
		result = query(children[u][0], k);
	} else {
		result = sum[children[u][0]] + value[u] + query(children[u][1], k);
	}
	return result;
}

int main() {
	freopen("input", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++ i) {
		int u, v;
		scanf("%d%d", &u, &v);
		neighbors[u].push_back(v);
		neighbors[v].push_back(u);
	}

	memset (go, -1, sizeof(go));
	weight[0] = INT_MAX;
	size = 0;
	dfs(0, -1);

	for (int i = 0, j = 31; i < n; ++ i, ++ j) {
		insert(roots[j], enter[i], 1);
		insert(roots[j], leave[i], -1);
		number[i] = j;
	}
	
	int m;
	scanf("%d", &m);
	while (m --) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int u, c;
			scanf("%d%d", &u, &c);
			erase(roots[number[u]], enter[u]);
			erase(roots[number[u]], leave[u]);
			number[u] = c;
			insert(roots[c], enter[u], 1);
			insert(roots[c], leave[u], -1);
		} else {
			int u, v;
			scanf("%d%d", &u, &v);
			int s = lca(u, v);
			int length = depth[u] + depth[v] - 2 * depth[s] + 1, key = number[u];
			if (number[u] != number[v] || number[u] > 30 || number[v] > 30) {
				puts("NO");
			} else {
				int temp = abs(query(roots[key], enter[v]) - query(roots[key], enter[u])) + 1;
				puts(temp == length ? "YES" : "NO");
			}
		}
	}
	return 0;
}
