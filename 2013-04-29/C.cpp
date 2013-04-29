#include <cstdio>
#include <cstring>

const char mode[] = "0469";

int main() {
    int test;
    scanf("%d", &test);
    while (test --) {
        char buffer[10];
        scanf("%s", buffer);
        int length = strlen(buffer);
        int answer = 0;
        for (int i = 0; i < length; ++ i) {
            int key = buffer[i] - '0';
            if (key == 8) {
                answer += 2;
            } else if (key == 0 || key == 4 || key == 6 || key == 9) {
                answer ++;
            }
        }
        printf("%d\n", answer);
    }
    return 0;
}
