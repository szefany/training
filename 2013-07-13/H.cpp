#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

const int N = 1000 + 10;

struct Point {
	int x, y;
	bool operator < (const Point &o) const {
		return y < o.y || y == o.y && x < o.x;
	}
} points[N];

#define sqr(x) ((x) * (x))
double get_dist(int a, int b) {
	return sqrt(sqr((double)points[a].x - points[b].x) + sqr((double)points[a].y - points[b].y));
}

double dist[N];
int n;

bool visit[N];
double d[N];
void prim(int l, int r) {
	for (int count = 0; count < n; ++ count) {
		int id = -1;
		for (int i = l; i <= r; ++ i) {
			if (!visit[i] && (id == -1 || dist[i] < dist[id])) {
				id = i;
			}
		}
		if (id == -1) {
			break;
		}
		visit[id] = true;
		for (int i = l; i <= r; ++ i) {
			if (!visit[i] && get_dist(id, i) < dist[i]) {
				dist[i] = get_dist(id, i);
			}
		}
	}
}

int main() {
	while (scanf("%d", &n) && n > 0) {
		for (int i = 1; i <= n; ++ i) {
			scanf("%d%d", &points[i].x, &points[i].y);
		}
		double answer = 0;
		for (int i = 1; i <= n; ++ i) {
			dist[i] = 1E30;
		}
		std::sort(points + 1, points + n + 1);
		memset(visit, 0, sizeof(visit));
		dist[1]=0;
		for (int i = 1; i <= n; ) {
			int j = i;
			while (j <= n && points[j].y == points[i].y) {
				j ++;
			}
			for (int k = i; k < j; ++ k) {
				for (int l = 1; l < i; ++ l) {
					dist[k] = std::min(dist[k], get_dist(l, k));
				}
			}
			prim(i, j - 1);
			i = j;
		}
		for (int i = 1; i <= n; ++ i) {
			answer += dist[i];
		}
		printf("%.2f\n", answer);
	}
	return 0;
}
