#include <cstdio>
#include <cmath>
#include <iostream>

const int N = 10;

double p[2][N], q[2][N];
int w, D, a, k;

double f(int t, double x) {
    double a = 0, b = 0, c = 1;
    for (int i = 0; i <= k; ++ i) {
        a += c * p[t][i];
        b += c * q[t][i];
        c *= x;
    }
    return a / b;
}

double solve(double d) {
    double result = 0;
    double delta = (double)w / 10000;
    for (int i = 0; i < 10000; ++ i) {
        double x = i * delta + delta / 2;
        result += (std::max(d, f(0, x)) - std::max(d, f(1, x))) * delta;
    }
    return result;
}

int main() {
    while (scanf("%d%d%d%d", &w, &D, &a, &k) != EOF) {
        for (int i = 0; i <= k; ++ i) {
            scanf("%lf", &p[0][i]);
        }
        for (int i = 0; i <= k; ++ i) {
            scanf("%lf", &q[0][i]);
        }
        for (int i = 0; i <= k; ++ i) {
            scanf("%lf", &p[1][i]);
        }
        for (int i = 0; i <= k; ++ i) {
            scanf("%lf", &q[1][i]);
        }
        double l = -D, r = 0;
        while (fabs(r - l) > 1E-5) {
            double m = (l + r) / 2;
            if (solve(m) >= a) {
                l = m;
            } else {
                r = m;
            }
        }
        double answer = -(l + r) / 2;
        printf("%.5f\n", answer);
    }
    return 0;
}
