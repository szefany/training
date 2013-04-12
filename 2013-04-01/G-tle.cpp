#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

const int L = 1000 + 1;
const int N = 10000 + 10;
const int M = (1000000 + 1) << 1;

std::vector<int> neighbors[N];

char string[N][L];
int root[N], length[N], degree[N], rank[N];
int n, size;

int step[M], prev[M], children[M][26];

void clear(int u) {
	memset(children[u], 0, sizeof(children[u]));
	prev[u] = step[u] = 0;
}

void initialise() {
	for (int i = 0; i < n; ++ i) {
		neighbors[i].clear();
		root[i] = degree[i] = 0;
	}
	size = 0;
	clear(0);
}

void move_to(int u, int v) {
	prev[v] = prev[u];
	step[v] = step[u];
	memcpy(children[v], children[u], sizeof(children[u]));
}

void build(int &r, int index) {
	r = ++ size;
	clear(size);
	for (int i = 0, last = r, u, node; i < length[index]; ++ i, last = u) {
		int key = string[index][i] - 'a';
		u = ++ size;
		clear(u);
		step[u] = step[last] + 1;
		for (node = last; node && children[node][key] == 0; node = prev[node]) {
			children[node][key] = u;
		}
		if (node == 0) {
			prev[u] = r;
			continue;
		}
		int v = children[node][key];
		if (step[v] == step[node] + 1) {
			prev[u] = v;
		} else {
			int nv = ++ size;
			move_to(v, nv);
			step[nv] = step[node] + 1;
			prev[u] = prev[v] = nv;
			for (; node && children[node][key] == v; node = prev[node]) {
				children[node][key] = nv;
			}
		}
	}
}

bool cmp(int x, int y) {
	return length[x] < length[y];
}

int queue[N], dist[N];
bool in_queue[N];

bool match(int x, int y) {
	for (int i = 0, u = root[y], cover = 0; i < length[x]; ++ i) {
		int key = string[x][i] - 'a';
		if (children[u][key]) {
			u = children[u][key];
			cover ++;
		} else {
			while (u && children[u][key] == 0) {
				u = children[u][key];
			}
			if (u == 0) {
				u = root[y];
				cover = 0;
			} else {
				cover = step[u] + 1;
				u = children[u][key];
			}
		}
		if (cover == length[x]) {
			return true;
		}
	}
	return false;
}

int main() {
	freopen("input", "r", stdin);
	while (scanf("%d", &n) != EOF && n > 0) {
		initialise();
		for (int i = 0; i < n; ++ i) {
			scanf("%s", string[i]);
			length[i] = strlen(string[i]);
			build(root[i], i);
			rank[i] = i;
		}
		std::sort(rank, rank + n, cmp);
		for (int i = 0; i < n; ++ i) {
			int u = rank[i];
			for (int j = i + 1; j < n; ++ j) {
				int v = rank[j];
				if (match(u, v)) {
					neighbors[u].push_back(v);
					degree[v] ++;
					// printf("%d %d\n", u, v);
				}
			}
		}

		int tail = 0;
		for (int i = 0; i < n; ++ i) {
			dist[i] = -1 << 21;
			in_queue[i] = false;
			if (degree[i] == 0) {
				queue[++ tail] = i;
				dist[i] = 1;
				in_queue[i] = true;
			}
		}
		
		const int Q = N - 1;
		int answer = 1, head = 0;
		for (int head = 1; head <= tail; ++ head) {
			int u = queue[head];
			in_queue[u] = false;
			if (dist[u] > answer) {
				answer = dist[u];
			}
			for (int i = 0; i < neighbors[u].size(); ++ i) {
				int v = neighbors[u][i];
				degree[v] --;
				if (degree[v] == 0) {
					dist[v] = dist[u] + 1;
					in_queue[v] = true;
					queue[++ tail] = v;
				}
			}
		}
		printf("%d\n", answer);
	}
	return 0;
}
