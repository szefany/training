#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 25 + 1;
const int S = 25 * 25 * 2 + 1;
const int INF = 1 << 30;

bool visit[S];
int g[N][N];
bool dp[N][N][S];
int n, m;

int abs(int x) {
	return x > 0 ? x : -x;
}

int main() {
	freopen("input", "r", stdin);
	int test_count;
	scanf("%d", &test_count);
	while (test_count --) {
		int a, b;
		scanf("%d%d%d%d", &n, &m, &a, &b);
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= m; ++ j) {
				scanf("%d", &g[i][j]);
			}
		}

		int sum = 25 * n;
		
		memset(dp, 0, sizeof(dp));
		
		for (int i = 1; i <= m; ++ i) {
			int key = g[n][i];
			dp[n][i][key + sum] = true;
		}
		for (int i = n - 1; i >= 1; -- i) {
			for (int j = 1; j <= m; ++ j) {
				for (int k = -1; k <= 1; ++ k) {
					int y = j + k;
					if (y >= 1 && y <= m) {
						for (int key = -sum; key <= sum; ++ key) {
							if (key + g[i][j] >= -sum && key + g[i][j] <= sum) {
								dp[i][j][key + sum + g[i][j]] |= dp[i + 1][y][key + sum];
							}
						}
					}
				}
			}
		}

		memset(visit, 0, sizeof(visit));
		int first = b + 1, last = a - 1;
		for (int i = 1; i <= m; ++ i) {
			for (int j = -sum; j <= sum; ++ j) {
				if (dp[1][i][j + sum] && j >= a && j <= b) {
					first = std::min(first, j);
					last = std::max(last, j);
				}
			}
		}
		if (first <= b) {
			printf("%d ", first);
		} else {
			printf("NO ");
		}
		if (last >= a) {
			printf("%d\n", last);
		} else {
			printf("NO\n");
		}	}
	return 0;
}
