#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

const int N = 200 + 1;
const int MOD = 100000000;

struct Segment {
	int left, right;
	bool operator < (const Segment &other) const {
		return right < other.right || right == other.right && left > other.left;
	}
} segments[N];

int n, top;
int dp[N][N];
std::vector<int> total;

int main() {
	freopen("input", "r", stdin);
	while (scanf("%d%d", &top, &n) && n + top > 0) {
		total.clear();
		for (int i = 1; i <= n; ++ i) {
			scanf("%d%d", &segments[i].left, &segments[i].right);
			total.push_back(segments[i].left);
			total.push_back(segments[i].right);
		}
		total.push_back(0);
		total.push_back(top);
		std::sort(total.begin(), total.end());
		total.resize(unique(total.begin(), total.end()) - total.begin());
		
		for (int i = 1; i <= n; ++ i) {
			segments[i].left = std::lower_bound(total.begin(), total.end(), segments[i].left) - total.begin(); 
			segments[i].right = std::lower_bound(total.begin(), total.end(), segments[i].right) - total.begin();
		}
		std::sort(segments + 1, segments + n + 1);
		/*
		for (int i = 1; i <= n; ++ i) {
			printf("%d %d\n", segments[i].left, segments[i].right);
		}*/
		
		segments[0].right = segments[0].left = -1;
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; ++ i) {	
			if (segments[i].left == 0) {
				dp[i][0] ++;
			}
			for (int j = 1; j < i; ++ j) {
				if (segments[j].left >= segments[i].left || segments[j].right < segments[i].left || (segments[i].right == segments[j].right && segments[j].left <= segments[i].left)) {
					continue;
				}
				for (int k = 0; k < j; ++ k) {
					if (k == 0 && segments[i].left != 0 || segments[k].right >= segments[j].left && segments[k].right < segments[i].left && segments[k].left < segments[j].left) {
			//			printf("%d %d %d\n",i, j, k);
						(dp[i][j] += dp[j][k]) %= MOD;
					}
				}
			}
		}
		int answer = 0;
		for (int i = 1; i <= n; ++ i) {
			if (segments[i].right == total.size() - 1) {
				for (int j = 0; j < i; ++ j) {
					(answer += dp[i][j]) %= MOD;
				}
			}
		}
		printf("%d\n", answer);
	}
	return 0;
}
