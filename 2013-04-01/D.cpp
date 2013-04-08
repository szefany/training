#include <cstdio>
#include <cstring>

const int N = 10;

long long number[N][N][2], now[2][N];
int digit[N], rest[N], pow10[N];

long long solve(int len, int key, bool less, bool first) {
	if (len == 0) {
		return 0;
	}
	if (less && number[len][key][first] != -1) {
		return number[len][key][first];
	}
	long long result = 0;
	int limit = less ? 9 : digit[len];
	for (int i = 0; i <= limit; ++ i) {
		if (i == 0 && first) {
			continue;
		}
		result += solve(len - 1, key, less || i < limit, false);
	}
	if (key == 0 && first) {
	} else
	if (less) {
		result += pow10[len - 1];
	} else {
	if (key < digit[len]) {
		result += pow10[len - 1];			
	} else if (key == digit[len]) {
		result += rest[len - 1] + 1;
	}
	}
	if (less) {
		number[len][key][first] = result;
	}
	return result;
}

void calculate(int x, int index) {
	memset(now[index], 0, sizeof(now[index]));
	memset(digit, 0, sizeof(digit));
	if (x == 0) {
		now[index][0] = 0;
		return;
	}
	int length = 0;
	while (x) {
		digit[++ length] = x % 10;
		x /= 10;
	}
	rest[0] = 0;
	for (int i = 1, j = 1; i <= length; ++ i, j *= 10) {
		rest[i] = rest[i - 1] + digit[i] * j;
	}
	for (int i = 1; i <= length; ++ i) {
		for (int j = 0; j < 10; ++ j) {
			now[index][j] += solve(i, j, i < length, true);
		}
	}
}

int main() {
	memset(number, -1, sizeof(number));
	pow10[0] = 1;
	for (int i = 1; i < N; ++ i) {
		pow10[i] = pow10[i - 1] * 10;
	}
	freopen("input", "r", stdin);
	int a, b;
	while (scanf("%d%d", &a, &b) && a + b > 0) {
		calculate(a - 1, 0);
		calculate(b, 1);
		for (int i = 0; i < 10; ++ i) {
			printf("%lld%c", now[1][i] - now[0][i], i == 9 ? '\n' : ' ');
		}
	}
	return 0;
}
