#include <cstdio>

int g[1000][1000];

int main() {
	int dx[4], dy[4];
	for (int i = 1; i <= 3; ++ i) {
		scanf("%d%d", &dx[i], &dy[i]);
	}
	for (int i = 0; i <= 5; ++ i) {
		for (int j = 0; j <= 5; ++ j) {
			for (int k = 0; k <= 5; ++ k) {
				int x = i * dx[1] + j * dx[2] + k * dx[3];
				int y = i * dy[1] + j * dy[2] + k * dy[3];
				if (x >= 0 && y >= 0) {
					g[x][y] = 1;
				}
			}
		}
	}
	for (int i = 0; i <= 20; ++ i) {
		for (int j = 0; j <= 20; ++ j) {
			putchar(g[i][j] ? '*' : '.');
		} puts("");
	}
}	
