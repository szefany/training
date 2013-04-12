#include <cstdio>
#include <cstring>

const int N = 10000;

char string[N], buffer[N];

int main() {
    while (1) {
        bool flag = true;
        gets(string);
        int length = strlen(string), size = 0;
        for (int i = 0; i < length; ) {
            if (i + 2 < length && string[i] == 'E' && string[i + 1] == 'O' && string[i + 2] == 'F') {
                flag = false;
                break;
            }
            if (string[i] == ' ') {
                buffer[size ++] = ' ';
                i ++;
            } else if (string[i] < 'a' || string[i] > 'z') {
                i ++;
            } else if (i + 1 < length && string[i] == 'd' && string[i + 1] == 'd') {
                buffer[size ++] = 'p';
                i += 2;
            } else if (i + 3 < length && string[i] == 'p' && string[i + 1] == 'i' && string[i + 2] == 'n' && string[i + 3] == 'k') {
                buffer[size ++] = 'f';
                buffer[size ++] = 'l';
                buffer[size ++] = 'o';
                buffer[size ++] = 'y';
                buffer[size ++] = 'd';
                i += 4;
            } else if (i + 1 < length && string[i] == 'e' && string[i + 1] == 'i' && (i == 0 || string[i - 1] != 'c')) {
                buffer[size ++] = 'i';
                buffer[size ++] = 'e';
                i += 2;
            } else {
                buffer[size ++] = string[i];
                i ++;
            }
        }   
        buffer[size] = '\0';
        if (flag) {
            puts(buffer);
        } else {
            printf("%s", buffer);
        }
        if (!flag) {
            break;
        }
    }
    return 0;
}
