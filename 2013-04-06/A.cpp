#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 60;
const int D[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

int a[N][N];
long long dp[N][N];
int n, m;

long long solve(int x, int y) {
	if (dp[x][y] != -1) {
		return dp[x][y];
	}
	dp[x][y] = 0;
	bool flag = false;
	for (int i = 0; i < 4; ++ i) {
		int dx = x + D[i][0];
		int dy = y + D[i][1];
		if (dx >= 0 && dx < n && dy >= 0 && dy < m && a[dx][dy] < a[x][y]) {
			dp[x][y] += solve(dx, dy);
			flag = true;
		}
	}
	if (!flag) {
		dp[x][y] = 1;
	}
	return dp[x][y];
}

int main() {
	freopen("input", "r", stdin);
	int test_count;
	scanf("%d", &test_count);
	for (int t = 1; t <= test_count; ++ t) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j) {
				scanf("%d", &a[i][j]);
			}
		}
		memset(dp, -1, sizeof(dp));
		long long answer = 0;
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < m; ++ j) {
				solve(i, j);
				bool flag = true;
				for (int k = 0; k < 4 && flag; ++ k) {
					int x = i + D[k][0];
					int y = j + D[k][1];
					if (x >= 0 && x < n && y >= 0 && y < m && a[x][y] > a[i][j]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					answer += dp[i][j];
				}
			}
		}
		printf("Case #%d: ", t);
		std::cout << answer << '\n';
	}
	return 0;
}
