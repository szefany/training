#include <cstdio>
#include <cstring>
#include <cmath>

const int N = 400;

double prob[N][N], expt[N][N];
bool visit[N][N];
int x,y;
bool chain(int a, int b) {
	if (a == 0 || b == 0) {
		return true;
	}
	if (visit[a][b]) {
		x=a;y=b;
		return false;
	}
	visit[a][b] = true;
	bool result;
	if (a >= b) {
		result = chain(a - b, b * 2);
	} else {
		result = chain(a * 2, b - a);
	}
	return result;
}
double solve_prob_2(int a, int b, int depth, double p) {
	if (visit[a][b]) {
		double temp = 1;
		for (int i = 0; i < depth; ++ i) {
			temp *= 0.5;
		}
		double result = p / (1 - temp);
		return result;
	}
	visit[a][b] = true;
	double result;
	if (a >= b) {
		result = solve_prob_2(a - b, b * 2, depth + 1, p + pow(0.5, depth + 1));
	} else {
		result = solve_prob_2(a * 2, b - a, depth + 1, p);
	}
	return result;
}
double solve_prob_1(int a, int b) {
	if(a==x&&b==y) return solve_prob_2(a, b,0, 0);
	if (a == b) {
		return 0.5;
	}
	double result;
	if (a >= b) {
		result = 0.5 + 0.5 * solve_prob_1(a - b, b * 2);
	} else {
		result = 0.5 * solve_prob_1(a * 2, b - a);
	}
	return result;
}

double solve_expt_1(int a, int b) {
	if(a==x&&b==y) return 2.0;
	if (a == b) {
		return 1;
	}
	double result;
	if (a > b) {
		result = 0.5 + 0.5 * (1 + solve_expt_1(a - b, 2 * b));
	} else {
		result = 0.5 + 0.5 * (1 + solve_expt_1(2 * a, b - a));
	}
	return result;
}




int main() {
	int test_count;
	scanf("%d", &test_count);
	for (int t = 1; t <= test_count; ++ t) {
		int a, b;
		scanf("%d%d", &a, &b);
		double p, e;
		memset(visit, 0, sizeof(visit));
		x=-1,y=-1;
		if (chain(a, b)) {
			p = solve_prob_1(a, b);
			e = solve_expt_1(a, b);
		} else if(a==x&&y==b){
			memset(visit, 0, sizeof(visit));
			p = solve_prob_2(a, b, 0, 0);
			memset(visit, 0, sizeof(visit));
			// e = solve_expt_2(a, b);
			e = 2;
		}else{
			memset(visit, 0, sizeof(visit));
			p=solve_prob_1(a,b);
			memset(visit, 0, sizeof(visit));
			e=solve_expt_1(a,b);
		}
		printf("Case %d: %.6f %.6f\n", t, e, p);
	}
	return 0;
}
