#include <cstdio>
#include <cstring>
#include <vector>

const int M = 50;
const int N = M * M + M;
const int D[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

std::vector<int> neighbors[N];
char map[M][M];
int indices[M][M];
int n, m, r, c;

void initialise() {
    memset(indices, 0, sizeof(indices));
    for (int i = 0; i < N; ++ i) {
        neighbors[i].clear();
    }
}

bool visit[N];
int link[N];

bool find(int u) {
    if (visit[u]) {
        return false;
    }
    visit[u] = true;
    for (int iter = 0; iter < neighbors[u].size(); ++ iter) {
        int v = neighbors[u][iter];
        if (link[v] == -1 || find(link[v])) {
            link[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    freopen("input", "r", stdin);
    while (scanf("%d%d", &r, &c) != EOF) {
        initialise();
        int counter[2] = {0};
        for (int i = 0; i < r; ++ i) {
            scanf("%s", map[i]);
            for (int j = 0; j < c; ++ j) {
                if (map[i][j] == '.') {
                    int t = (i + j) % 2;
                    indices[i][j] = counter[t] ++;
                }
            }
        }
        for (int i = 0; i < r; ++ i) {
            for (int j = 0; j < c; ++ j) {
                if (map[i][j] == '.' && (i + j) % 2 == 0) {
                    int p = indices[i][j];
                    for (int k = 0; k < 4; ++ k) {
                        int x = i + D[k][0], y = j + D[k][1];
                        if (x >= 0 && x < r && y >= 0 && y < c && map[x][y] == '.') {
                            neighbors[p].push_back(indices[x][y]);
                        }
                    }
                }
            }
        }

        memset(link, -1, sizeof(link));
        bool flag = counter[0] == counter[1];
        for (int i = 0; i < counter[0] && flag; ++ i) {
            memset(visit, 0, sizeof(visit));
            flag &= find(i);
        }
        puts(flag ? "2" : "1");
    }
    return 0;
}
