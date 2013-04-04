#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

const int N = 10000 + 1;
const int M = 1000000 + 1;
const int ROOT = 1;

int children[M][26], fail[M], index[M];
int n, size;

std::string string[N];

void clear(int node) {
    fail[node] = 0;
    index[node] = -1;
    for (int i = 0; i < 26; ++ i) {
        children[node][i] = 0;
    }
}

void initialise() {
    size = 1;
    clear(1);
}

int rank[N], mapping[N], dp[N];

void insert(std::string &string, int x) {
    int u = ROOT;
    for (int i = 0; i < string.length(); ++ i) {
        int key = string[i] - 'a';
        if (children[u][key] == 0) {
            clear(++ size);
            children[u][key] = size;
        }
        u = children[u][key];
    }
    index[u] = x;
}

int queue[M];
void get_label() {
    queue[0] = ROOT;
    for (int head = 0, tail = 0, node; head <= tail; ++ head) {
        int u = queue[head];
        if (fail[u] && index[fail[u]] != -1) {
            index[u] = mapping[index[u]] > mapping[index[fail[u]]] ? index[u] : index[fail[u]];
        }
        for (int i = 0; i < 26; ++ i) {
            int v = children[u][i];
            if (v == 0) {
                children[u][i] = children[fail[u]][i];
            } else {
                queue[++ tail] = v;
                int &node = fail[v];
                for (node = fail[u]; node && children[node][i] == 0; node = fail[node]);
                node = node == 0 ? ROOT : children[node][i];
            }
        }
    }
}

bool cmp(int x, int y) {
    if (string[x].length() - string[y].length()) {
        return string[x].length() < string[y].length();
    }
    return x < y;
}

int solve(std::string &string) {
    int result = 0;
    for (int i = 0, u = ROOT; i < string.length(); ++ i) {
        int key = string[i] - 'a';
        u = children[u][key];
        result = std::max(result, dp[index[u]] + 1);
        if (fail[u]) {
            result = std::max(result, dp[index[fail[u]]] + 1);
        }
    }
    return result;
}

int main() {
    freopen("input", "r", stdin);
    std::ios::sync_with_stdio(false);
    while (std::cin >> n && n > 0) {
        initialise();
        for (int i = 0; i < n; ++ i) {
            std::cin >> string[i];
            rank[i] = i;
        }
        std::sort(rank, rank + n, cmp);
        for (int i = 0; i < n; ++ i) {
            mapping[rank[i]] = i;
        }

        for (int i = 0; i < n; ++ i) {
            int u = rank[i];
            insert(string[u], u);
        }
        get_label();

        for (int i = 0; i < n; ++ i) {
            dp[i] = 0;
        }
        int answer = 1;
        for (int i = 0; i < n; ++ i) {
            int u = rank[i];
            dp[u] = solve(string[u]);
            answer = std::max(answer, dp[u]);
            // std::cout << string[u] << " " << dp[u] << std::endl;
        }
        printf("%d\n", answer);
    }
    return 0;
}
