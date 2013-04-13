#include <cstdio>
#include <algorithm>

const int N = 60;
const double INF = 1E20;
const double EPS = 1E-8;

struct Point {
	int x, y;
	bool operator < (const Point &other) const {
		return x * other.y - y * other.x < 0;
	}
} p[N];

int dp[N][N][N * N];
int n;

void update(int &target, int source) {
	if (target == -1 || source > target) {
		target = source;
	}
}

struct data {
	int i, j, h;
	data() {}
	data(int i, int j, int h): i(i), j(j), h(h) {}
};

data queue[N * N * N * N];
int visit[N][N][N * N];

int main() {
	int test;
	scanf("%d", &test);
	for (int t = 1; t <= test; ++ t) {
		int m, max_value = 0;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++ i) {
			scanf("%d%d", &p[i].x, &p[i].y);
			max_value += p[i].y;
		}
		std::sort(p + 1, p + n + 1);
		
		dp[0][0][0] = 0;
		queue[0] = data(0, 0, 0);
		int area = 0;
		for (int head = 0, tail = 0; head <= tail; ++ head) {
			int i = queue[head].i, j = queue[head].j;
			int h = queue[head].h, value = dp[i][j][h];
			if (j == m) {
				area = std::max(area, value);
			}
			if (i < n) {
			if (visit[i + 1][j][h] != t) {
				visit[i + 1][j][h] = t;
				dp[i + 1][j][h] = value;
				queue[++ tail] = data(i + 1, j, h);
			} else if (value > dp[i + 1][j][h]) {
				dp[i + 1][j][h] = value;
			}
			if (j < m) {
				int temp = value + h * p[i + 1].x * 2 + p[i + 1].x * p[i + 1].y;
				if (visit[i + 1][j + 1][h + p[i + 1].y] != t) {
					visit[i + 1][j + 1][h + p[i + 1].y] = t;
					dp[i + 1][j + 1][h + p[i + 1].y] = temp;
					queue[++ tail] = data(i + 1, j + 1, h + p[i + 1].y);
				} else if (dp[i + 1][j + 1][h + p[i + 1].y] < temp) {
					dp[i + 1][j + 1][h + p[i + 1].y] = temp;
				}
			}
			}
		}
		printf("Case %d: %d\n", t, area);
	}
	return 0;
}
