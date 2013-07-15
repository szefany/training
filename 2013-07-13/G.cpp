#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

const int P = 100000 + 10;

std::vector<int> primes;
bool not_prime[P];

void get_prime() {
	for (int i = 2; i < P; ) {
		primes.push_back(i);
		for (int j = i + i; j < P; j += i) {
			not_prime[j] = true;
		}
		for (i ++; not_prime[i]; ++ i);
	}
}

const int N = 100000;

std::vector<int> neighbors[N];
bool invalid[N], visit[N];
int links[N], size;
long long n;

bool find(int u) {
	if (visit[u]) {
		return false;
	}
	visit[u] = true;
	for (int i = 0; i < neighbors[u].size(); ++ i) {
		int v = neighbors[u][i];
		if (!invalid[v] && (links[v] == 0 || find(links[v]))) {
			links[v] = u;
			return true;
		}
	}
	return false;
}

bool max_match(int start) {	
	for (int i = 0; i < size; ++ i) {
		links[i] = 0;
	}
	for (int i = start; i < n; ++ i) {
		for (int j = 0; j < n; ++ j) {
			visit[j] = 0;
		}
		if (!find(i)) {
			return false;
		}
	}
	return true;
}

long long answer[N], map[N];

int main() {
	get_prime();
	long long l, r;
	while (scanf("%lld%lld", &l, &r) && l + r > 0) {
		for (int i = 0; i < N; ++ i) {
			neighbors[i].clear();
		}
		std::set<long long> set;
		for (long long i = l; i <= r; ++ i) {
			long long x = i;
			for (int j = 0; (long long)primes[j] * primes[j] <= x; ++ j) {
				if (x % primes[j] == 0) {
					set.insert(primes[j]);
				}
				while (x % primes[j] == 0) {
					x /= primes[j];
				}
			}
			if (x > 1) {
				set.insert(x);
			}
		}
		size = 0;
		for (std::set<long long>::iterator iter = set.begin(); iter != set.end(); iter ++, size ++) {
			long long x = *iter;
			map[size] = x;
			for (long long i = l; i <= r; ++ i) {
				if (i % x == 0) {
					neighbors[i - l].push_back(size);
					// printf("%d %d\n", i, x);
				}
			}
		}
		n = r - l + 1;
		memset(invalid, 0, sizeof(invalid));
		memset(answer, 0, sizeof(answer));
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < (int)neighbors[i].size(); ++ j) {
				int x = neighbors[i][j];
				if (invalid[x]) {
					continue;
				}
				invalid[x] = true;
				if (!max_match(i + 1)) {
					invalid[x] = false;
				} else {
					answer[i] = map[x];
					break;
				}
			}
			if (answer[i] == 0) {
				for (int j = 0; j < neighbors[i].size(); ++ j) {
					int x = neighbors[i][j];
					if (!invalid[x]) {
						answer[i] = map[x];
						invalid[x] = true; 
						break;
					}
				}
			}
		}
		for (int i = 0; i < n; ++ i) {
			printf("%lld%c", answer[i], i == n - 1 ? '\n' : ' ');
		}
	}
	return 0;
}
