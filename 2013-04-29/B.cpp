#include <cstdio>
#include <cstring>

const int N = 50000 + 1;

char string[N];
char s1[200], s2[200];

void trans(char *string) {
    int length = strlen(string);
    for (int i = 0; i < length; ++ i) {
        if (string[i] >= 'A' && string[i] <= 'Z') {
            string[i] = 'a' + string[i] - 'A';
        }
    }
}

bool equal(char a, char b) {
    if (a >= 'A' && a <= 'Z') {
        a = a - 'A' + 'a';
    }
    if (b >= 'A' && b <= 'Z') {
        b = b - 'A' + 'a';
    }
    return a == b;
}

int main() {
    freopen("B.in", "r", stdin);
    while (gets(s1)) {
        gets(s2);
        int length[2] = {strlen(s1), strlen(s2)};
        gets(string);
        // trans(s1), trans(s2), trans(string);
        int len = strlen(string);
        for (int i = 0; i < len; ) {
            bool flag = (i + length[0] <= len);
            for (int j = 0, k = i; j < length[0] && flag; ++ j, ++ k) {
                flag &= equal(string[k], s1[j]);
            }
            if (flag) {
                printf("%s", s2);
                i += length[0];
            } else {
                putchar(string[i]);
                i ++;
            }
        }
        puts("");
    }
    return 0;
}
