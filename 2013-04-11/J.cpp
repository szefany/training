#include <cstdio>
#include <map>
#include <string>
#include <sstream>
#include <cstring>

const int N = 260;

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

typedef std::pair<int, int> Pair;
std::map<int, std::map<int, int> > dp, where;
bool visit[N];
int n, result;

char string[300];

int trans(int pivot, int length) {
	std::string s;
	std::stringstream buffer;
	for (int i = pivot; i < length; ++ i) {
		s += string[i];
	}
	int result;
	buffer << s;
	buffer >> result;
	return result;
}

void update(int &a, int b) {
	if (b < a) {
		a = b;
	}
}

void solve(int u, int length) {
	if (visit[u]) {
		return;
	}
	visit[u] = true;
	if (u == length) {
		dp[u][0] = 0;
		return;
	}
	if (string[u] == '0') {
		return;
	}
	int current = 0;
	for (int i = u, counter = 1; i < length && counter <= 5; ++ i, counter ++) {
		current = current * 10 + (string[i] - '0');
		if (current > result) {
			break;
		}
		solve(i + 1, length);
		int step = i + 1 == length ? 0 : 1;
		foreach (iter, dp[i + 1]) {
			int key = (*iter).first;
			int value = (*iter).second;
			if (dp[u].find(current + key) == dp[u].end()) {
				dp[u][current + key] = value + step;
				where[u][current + key] = i;
			} else if (value + step < dp[u][current + key]) {
				dp[u][current + key] = value + step;
				where[u][current + key] = i;
			}
		}
	}
}

int main() {
	freopen("J.in", "r", stdin);
	int test_count = 0;
	while (1) {
		scanf("%s", string);
		if (strcmp(string, "0=0") == 0) {
			break;
		}
		int length = strlen(string), pivot = -1;
		for (int i = 0; i < length; ++ i) {
			if (string[i] == '=') {
				pivot = i;
				break;
			}
		}
		printf("%d. ", ++ test_count);
		if (length - pivot > 7) {
			puts("IMPOSSIBLE");
			continue;
		}
		result = trans(pivot + 1, length);
		memset(visit, 0, sizeof(visit));
		dp.clear();
		where.clear();
		solve(0, pivot);
		if (dp[0].find(result) == dp[0].end()) {
			puts("IMPOSSIBLE");
		} else {
			int memory = result;
			for (int i = 0; i < pivot; ) {
				int next = where[i][result];
				for (int k = i; k <= next; ++ k) {
					putchar(string[k]);
				}
				if (next + 1 < pivot) {
					putchar('+');
					result -= trans(i, next + 1);
				}
				i = next + 1;
			}
			printf("=%d\n", memory);
			// printf("%d\n", dp[0][result]);
		}
	}	
	return 0;
}
