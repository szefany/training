#include <cstdio>
#include <cstring>

const int N = 100000 + 1;
const int S = N << 2;

int n, m;
int a[N];

int flag[S], size, child[S][2], left[S], right[S];

int get_id(int l, int r) {
	return l + r | l != r;
}

void update(int id) {
	int L = child[id][0];
	int R = child[id][1];
	if (flag[L] == 0 || flag[R] == 0) {
		flag[id] = 0;
	} else if (flag[L] == flag[R]) {
		flag[id] = 1;
	} else {
		flag[id] = -1;
	}
}

void build(int &id, int l, int r) {
	id = ++ size;
	left[id] = l;
	right[id] = r;
	if (l == r) {
		if (a[l] == 0) {
			flag[id] = 0;
		} else {
			flag[id] = a[l] > 0 ? 1 : -1;
		}
	} else {
		int middle = l + r >> 1;
		build(child[id][0], l, middle);
		build(child[id][1], middle + 1, r);
		update(id);
	}
}

int check(int id, int a, int b) {
	if (a > right[id] || b < left[id]) {
		return 1;
	}
	if (a <= left[id] && b >= right[id]) {
		return flag[id];
	}
	int x = check(child[id][0], a, b);
	int y = check(child[id][1], a, b);
	if (x == 0 || y == 0) {
		return 0;
	}
	if (x == y) {
		return 1;
	}
	return -1;
}

void insert(int id, int a, int v) {
	if (left[id] == right[id]) {
		if (v == 0) {
			flag[id] = 0;
		} else {
			flag[id] = v > 0 ? 1 : -1;
		}
		return;
	}
	int m = left[id] + right[id] >> 1;
	if (a > m) {
		insert(child[id][1], a, v);
	} else {
		insert(child[id][0], a, v);
	}
	update(id);
}

int main() {
	freopen("input", "r", stdin);
	while (scanf("%d%d", &n, &m) != EOF) {
		memset(flag, 0, sizeof(flag));
		for (int i = 1; i <= n; ++ i) {
			scanf("%d", &a[i]);
		}
		size = 0;
		int root = 0;
		build(root, 1, n);
		while (m --) {
			char buffer[2];
			scanf("%s", buffer);
			if (*buffer == 'C') {
				int x, value;
				scanf("%d%d", &x, &value);
				insert(root, x, value);
			} else {
				int l, r;
				scanf("%d%d", &l, &r);
				int flag = check(root, l, r);
				if (flag == 0) {
					putchar('0');
				} else {
					putchar(flag < 0 ? '-' : '+');
				}
			}
		}
		puts("");
	}
	return 0;
}
