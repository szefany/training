#include <cstdio>
#include <cstring>

const int N = 10000;

char string[N];

int main() {
	freopen("input", "r", stdin);
	while (1) {
		gets(string);
		if (*string == '*') {
			break;
		}
		int length = strlen(string);
		for (int i = 0; i < length; ++ i) {
			if (string[i] >= 'a' && string[i] <= 'z') {
				string[i] = string[i] - 'a' + 'A';
			}
		}
		bool flag = true;
		char key = *string;
		for (int i = 0; i + 1 < length; ++ i) {
			if (string[i] == ' ' && string[i + 1] != key) {
				flag = false;
				break;
			}
		}
		puts(flag ? "Y" : "N");
	}
	return 0;
}
