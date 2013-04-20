#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 1000 + 1;

long long w[N], x[N], g[N], s[N], dp[N][N];
int queue[N];
int n, m;

void init() {
	g[0] = s[0] = 0;
	memset(dp, 1, sizeof(dp));
}

double calc(int k1, int k2, int j) {
	return (double)((double)dp[k1][j - 1] + g[k1] - dp[k2][j - 1] - g[k2]) / (s[k1] - s[k2]);
}

int main() {
	freopen("input", "r", stdin);
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 1; i <= n; ++ i) {
			scanf("%lld%lld", &x[i], &w[i]);
			g[i] = g[i - 1] + w[i] * x[i];
			s[i] = s[i - 1] + w[i];
		}
		dp[1][1] = 0;
		for (int i = 2; i <= n; ++ i) {
			dp[i][1] = x[i] * s[i - 1] - g[i - 1];
		}
		for (int j = 2; j <= m; ++ j) {
			dp[j - 1][j - 1] = 0;
			int head = 0, tail = 1;
			queue[0] = j - 1;
			for (int i = j; i <= n; ++ i) {
				while (head + 1 < tail) {
					int h0 = queue[head], h1 = queue[head + 1];
					if (dp[h0][j - 1] + g[h0] - x[i] * s[h0] >= dp[h1][j - 1] + g[h1] - x[i] * s[h1]) {
						head ++;
					} else {
						break;
					}
				}
				long long temp = - g[i - 1] + x[i] * s[i - 1];
				int k = queue[head];
				dp[i][j] = dp[k][j - 1] + g[k] - x[i] * s[k] + temp;
				if (head + 1 < tail) {
					k = queue[head + 1];
					dp[i][j] = std::min(dp[i][j], dp[k][j - 1] + g[k] - x[i] * s[k] + temp);
				}
				while (tail - 2 >= head) {
					int h0 = queue[tail - 2];
					int h1 = queue[tail - 1];
					int h2 = i;
					if (calc(h0, h1, j) >= calc(h1, h2, j)) {
						tail --;
					} else {
						break;
					}
				}
				queue[tail ++] = i;
			}
		}
		/*
		for (int i = 1; i <= n; ++ i) {
			printf("%lld\n", dp[i][2]);
		}
		*/
		printf("%lld\n", dp[n][m]);
	}
	return 0;
}
/*
10 3
1 7
8 8
11 9
16 3
25 3
27 10
30 9
35 4
40 2
41 4
*/
