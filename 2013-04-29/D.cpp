#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

const int N = 22;
const int Q = 1000000;
const int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const double INF = 1E10;

struct data {
    int x, y;
    data() {}
    data(int x, int y): x(x), y(y) {}
} queue[Q];

int n, m;
char map[N][N];
bool visit[N][N][2];
double dist[N][N][2];

#define update(a, b) if ((b) < (a)) (a) = (b)

int main() {
    freopen("input", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++ j) {
                for (int k = 0; k < 2; ++ k) {
                    visit[i][j][k] = false;
                    dist[i][j][k] = INF;
                }
            }
        }
        int sx, sy, ex, ey, px, py;
        bool exist = false;
        for (int i = 1; i <= n; ++ i) {
            scanf("%s", map[i] + 1);
            for (int j = 1; j <= m; ++ j) {
                if (map[i][j] == 'P') {
                    sx = i, sy = j;
                }
                if (map[i][j] == 'B') {
                    ex = i, ey = j;
                }
                if (map[i][j] == 'S') {
                    px = i, py = j;
                    exist = true;
                }
            }
        }
        queue[0] = data(sx, sy);
        visit[sx][sy][0] = true;
        dist[sx][sy][0] = 0;
        for (int head = 0, tail = 0; head <= tail; ++ head) {
            int x = queue[head].x, y = queue[head].y;
            if (exist && x == px && y == py) {
                continue;
            }
            for (int i = 0; i < 4; ++ i) {
                int dx = x + D[i][0];
                int dy = y + D[i][1];
                if (dx >= 1 && dx <= n && dy >= 1 && dy <= m && map[dx][dy] != 'X' && !visit[dx][dy][0]) {
                    dist[dx][dy][0] = dist[x][y][0] + 1;
                    visit[dx][dy][0] = true;
                    queue[++ tail] = data(dx, dy);
                }
            }
        }
        
        double answer = INF;
        for (int i = 1; i <= n; ++ i) {
            int x1 = std::min(i, ex);
            int x2 = std::max(i, ex);
            bool flag = true;
            for (int j = x1 + 1; j <= x2 && flag; ++ j) {
                flag &= (map[j][ey] != 'X' && map[j][ey] != 'S');
            }
            if (flag) {
                update(answer, dist[i][ey][0] + 0.2 * (x2 - x1));
            }
        }
        for (int i = 1; i <= m; ++ i) {
            int y1 = std::min(i, ey);
            int y2 = std::max(i, ey);
            bool flag = true;
            for (int j = y1 + 1; j <= y2 && flag; ++ j) {
                flag &= (map[ex][j] != 'X' && map[ex][j] != 'S');
            }
            if (flag) {
                update(answer, dist[ex][i][0] + 0.2 * (y2 - y1));
            }
        }
        if (exist) {
        queue[0] = data(px, py);
        visit[px][py][1] = true;
        dist[px][py][1] = 0;
        for (int head = 0, tail = 0; head <= tail; ++ head) {
            int x = queue[head].x, y = queue[head].y;
            for (int i = 0; i < 4; ++ i) {
                int dx = x + D[i][0];
                int dy = y + D[i][1];
                if (dx >= 1 && dx <= n && dy >= 1 && dy <= m && map[dx][dy] != 'X' && !visit[dx][dy][1]) {
                    dist[dx][dy][1] = dist[x][y][1] + 0.5;
                    visit[dx][dy][1] = true;
                    queue[++ tail] = data(dx, dy);
                }
            }
        }
        for (int i = 1; i <= n; ++ i) {
            int x1 = std::min(i, ex);
            int x2 = std::max(i, ex);
            bool flag = true;
            for (int j = x1; j <= x2 && flag; ++ j) {
                flag &= (map[j][ey] != 'X');
            }
            if (flag) {
                update(answer, dist[px][py][0] + dist[i][ey][1] + 0.2 * (x2 - x1));
            }
        }
        for (int i = 1; i <= m; ++ i) {
            int y1 = std::min(i, ey);
            int y2 = std::max(i, ey);
            bool flag = true;
            for (int j = y1; j <= y2 && flag; ++ j) {
                flag &= (map[ex][j] != 'X' && map[ex][j] != 'S');
            }
            if (flag) {
                update(answer, dist[px][py][0] + dist[ex][i][1] + 0.2 * (y2 - y1));
            }
        }
        }
        if (fabs(answer - INF) < 1E-6) {
            puts("-1");
        } else {
            printf("%.1f\n", answer);
        }
    }
}
