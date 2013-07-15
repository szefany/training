#include <cstdio>

int main() {
	int width, length, height, n, area, m;
	while (scanf("%d%d%d%d%d%d", &n, &width, &length, &height, &area, &m) != EOF) {
		if (n + width + length + height + area + m == 0) {
			break;
		}
		int total = (width + length) * height * 2 + width * length;
		while (m --) {
			int x, y;
			scanf("%d%d", &x, &y);
			total -= x * y;
		}
		int answer = (total * n + area - 1) / area;
		printf("%d\n", answer);
	}
	return 0;
}
