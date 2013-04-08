#include <cstdio>
#include <cstring>

const int N = 100000 + 1;

int n, m;
int element[N];

const int S = N << 2;

int state[S], cover[S], flag[S];

int get_id(int l, int r) {
	return l + r | l != r;
}

int judge(int s, int t, int a, int b) {
	int result = -1;
	if (s == 0 || t == 0) {
		result = 0;
	} else if (s == 3 && t == 3) {
		if (a == b) {
			result = 3;
		} else {
			result = a < b ? 1 : 2;
		}
	} else if (s == 3 || s == 1 && t == 3 || t == 1) {
		result = a <= b ? 1 : 0;
	} else if (s == 3 || s == 2 && t == 3 || t == 2) {
		result = a >= b ? 2 : 0;
	}
	if (result == -1) {
		result = 0;
	}
	return result;
}

void down(int l, int r) {
	int id = get_id(l, r);
	int middle = l + r >> 1;
	cover[get_id(l, middle)] += cover[id];
	cover[get_id(middle, r)] += cover[id];
	flag[get_id(l, middle)] ^= flag[id];
	flag[get_id(middle, r)] ^= flag[id];
	cover[id] = flag[id] = 0;
}

void build(int l, int r) {
	int id = get_id(l, r);
	if (l + 1 == r) {
		cover[id] = element[l];
		state[id] = 3;
	} else {
		int middle = l + r >> 1;
		build(l, middle);
		build(middle, r);
		state[id] = judge(state[get_id(l, middle)], state[get_id(middle, r)], element[middle], element[middle + 1]);
		cover[id] = flag[id] = 0;
	}
}

void insert(int l, int r, int a, int b, int v) {
	if (a >= r || b <= l) {
		return;
	}
	int id = get_id(l, r);
	if (a <= l && b >= r) {
		cover[id] = v - cover[id];
		flag[id] ^= 1;
	} else {
		down(l, r);
		int middle = l + r >> 1;
		insert(l, middle, a, b, v);
		insert(middle, r, a, b, v);
	}
}

int get_value(int l, int r, int p) {
	int id = get_id(l, r);
	if (l + 1 == r) {
		return cover[id] + (element[l] ^ flag[id]);
	}
	down(l, r);
	int middle = l + r >> 1;
	if (p >= middle) {
		return get_value(middle, r, p);
	}
	return get_value(l, middle, p);
}

int query(int l, int r, int a, int b) {
	if (a >= r || b <= l) {
		return 3;
	}
	int id = get_id(l, r);
	if (a <= l && b >= r) {
		return state[id];
	}
	down(l, r);
	int middle = l + r >> 1;
	if (b <= middle) {
		return query(l, middle, a, b);
	}
	if (a >= middle) {
		return query(middle, r, a, b);
	}
	int s = query(l, middle, a, b);
	int t = query(middle, r, a, b);
	return judge(s, t, get_value(0, n, middle), get_value(0, n, middle + 1));	
}

int main() {
	freopen("input", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", &element[i]);
	}
	build(0, n);
	while (m --) {
		int type, l, r;
		scanf("%d%d%d", &type, &l, &r);
		if (type == 0) {
			printf("%d\n", query(0, n, l, r));
		} else {
			insert(0, n, l, r, type);
		}
	}	
	return 0;
}

