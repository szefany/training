#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

const int N = 100 + 1;
const int M = 200;

struct Data {
	int x, height;
	bool operator < (const Data &other) const {
		return x < other.x;
	}
} data[N];

int n, H, W;
int dp[N][M << 3];

int main() {
	freopen("input", "r", stdin);
	int test_count;
	scanf("%d", &test_count);
	for (int t = 1; t <= test_count; ++ t) {
		// initialise();
		scanf("%d%d%d", &n, &H, &W);
		int max_height = 0;
		for (int i = 1; i <= n; ++ i) {
			scanf("%d%d", &data[i].x, &data[i].height);
			max_height = std::max(max_height, data[i].height);
		}
		std::sort(data + 1, data + n + 1);

		bool updated = false;
		memset(dp, 1, sizeof(dp));
		int answer = dp[0][0];
		dp[0][0] = 0;
		for (int i = 1; i <= n; ++ i) {
			for (int j = 0; j < M; ++ j) {
				if (data[i].height == max_height && j != data[i].x) {
					continue;
				}
				int temp = 1 << 30;
				for (int k = 0; k < j; ++ k) {
					temp = std::min(temp, dp[i - 1][k] + abs(j - data[i].x) * data[i].height);
				}
				if (data[i].height <= H) {
					dp[i][j] = std::min(dp[i][j], temp);
				}
				if (i > 1) {
					for (int k = 0; k < j; ++ k) {
						if (abs(j - k) > W) {
							continue;
						}
						if (data[i - 1].height > data[i].height || data[i].height - data[i - 1].height <= H) {
							dp[i][j] = std::min(dp[i][j], dp[i - 1][k] + temp);
						}
					}
				}
				if (data[i].height == max_height && dp[i][j] < answer) {
					printf("%d %d\n", i, j);
					answer = dp[i][j];
					updated = true;
				}
			}
		}
		printf("Case #%d: %d\n", t, updated ? answer : -1);
	}
	return 0;
}
