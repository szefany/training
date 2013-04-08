#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>

const int N = 20000 + 1;
const double EPS = 1E-8;
const double INF = 1 << 30;

struct Point {
	int x, y;
	int id, pos;
	Point() {}
	Point(double x, double y): x(x), y(y), id(-1) {}
	Point(double x, double y, int id): x(x), y(y), id(id) {}
	Point operator - (const Point &other) const {
		return Point(x - other.x, y - other.y);
	}
	void input(int i) {
		id = i;
		scanf("%d%d", &x, &y);
	}
};

int sgn(double x) {
	if (x < -EPS) {
		return -1;
	}
	return x < EPS ? 0 : 1;
}

long long dot(Point a, Point b) {
	return (long long)a.x * b.x + (long long)a.y * b.y;
}

long long det(Point a, Point b) {
	return (long long)a.x * b.y - (long long)a.y * b.x;
}

bool on_segment(Point p, Point a, Point b) {
	return det(p - a, p - b) == 0 && dot(p - a, p - b) <= 0;
}

struct Polygon {
	static const int N = 30;
	Point points[N];
	int size;
	
	Polygon() {
		size = 0;
	}
	void push(Point p) {
		points[size ++] = p;
	}
	bool inside(Point p) {
		for (int i = 0; i < size; ++ i) {
			int j = i + 1 == size ? 0 : i + 1;
			if (on_segment(p, points[i], points[j])) {
				return true;
			}
		}
		int counter[2] = {0};
		for (int i = 0; i < size; ++ i) {
			Point last = points[i];
			Point now = i + 1 == size ? points[0] : points[i + 1];
			if (last.y - p.y < 0 && now.y - p.y >= 0 || now.y - p.y < 0 && last.y - p.y >= 0) {
				double x = ((double)p.y - last.y) * (now.x - last.x) / (now.y - last.y) + last.x;
				counter[sgn(x - p.x) >= 0] ++;
			}
		}
		return (counter[0] & 1) && (counter[1] & 1);
	}
};

int now;
bool cmp(const Point &a, const Point &b) {
	if (now == 0) {
		return a.x < b.x;
	}
	return a.y < b.y;
}
	
struct kDTree {
	static const int N = 20000 + 1;
	Point points[N], current;
	std::vector<Point> all_points;
	int divide[N], tree[N], size, answer[2];
	long long dist[2];
	
	void clear() {
		all_points.clear();
		for (int i = 0; i <= size; ++ i) {
			divide[i] = tree[i] = 0;
		}
		size = 0;
	}

	void push(Point p) {
		p.pos = size;
		points[size ++] = p;
		all_points.push_back(p);
	}

	void initialise() {
		build(0, size);
	}
	
	void build(int l, int r) {
		if (l >= r) {
			return;
		}
		int middle = l + r >> 1;
		int min_x = INF, min_y = INF, max_x = -INF, max_y = -INF;
		for (int i = l; i < r; ++ i) {
#define updateMin(a, b) if ((b) < (a)) (a) = (b)
#define updateMax(a, b) if ((b) > (a)) (a) = (b)
			updateMin(min_x, all_points[i].x);
			updateMin(min_y, all_points[i].y);
			updateMax(max_x, all_points[i].x);
			updateMax(max_y, all_points[i].y);
		}
		now = max_x - min_x > max_y - min_y ? 0 : 1;
		divide[middle] = now;
		std::nth_element(all_points.begin() + l, all_points.begin() + middle, all_points.begin() + r, cmp);
		tree[middle] = all_points[middle].pos;
		build(l, middle);
		build(middle + 1, r);
	}

	bool compare(long long source, long long dest, int source_id, int dest_id) {
		long long flag = source - dest;
		return flag < 0 || flag == 0 && source_id < dest_id;
	}
	
	void update(long long d, int id) {
		if (compare(d, dist[0], id, answer[0])) {
			dist[1] = dist[0];
			answer[1] = answer[0];
			dist[0] = d;
			answer[0] = id;
		} else if (compare(d, dist[1], id, answer[1])) {
			dist[1] = d;
			answer[1] = id;
		}
	}
	
	void find(int l, int r) {
		if (l >= r) {
			return;
		}
		int middle = l + r >> 1;
		
		int delta[2];
		delta[0] = current.x - points[tree[middle]].x;
		delta[1] = current.y - points[tree[middle]].y;
#define sqr(x) ((x) * (x))
		long long d = sqr((long long)delta[0]) + sqr((long long)delta[1]);
		update(d, points[tree[middle]].id);
		
		if (l + 1 == r) {
			return;
		}
		int l1 = l, r1 = middle;
		int l2 = middle + 1, r2 = r;
		if (delta[divide[middle]] > 0) {
			std::swap(l1, l2);
			std::swap(r1, r2);
		}
		find(l1, r1);
		if (dist[1] >= delta[divide[middle]] * delta[divide[middle]]) {
			find(l2, r2);
		}
	}
	
	void query(Point p, int &a, int &b) {
		// return the ID
		current = p;
		answer[0] = answer[1] = -1;
		dist[0] = dist[1] = (1LL) << 60;
		find(0, size);
		a = answer[0];
		b = answer[1];
	}
} tree;

std::vector<Point> point;
int n, m;

void initialise() {
	point.clear();
}

int main() {
	freopen("input", "r", stdin);
	int test_count;
	scanf("%d", &test_count);
	for (int t = 1; t <= test_count; ++ t) {
		initialise();
		scanf("%d", &n);
		for (int i = 0; i < n; ++ i) {
			Point p;
			p.input(i);
			point.push_back(p);
		}
		printf("Case #%d:\n", t);
		scanf("%d", &m);
		for (int counter = 0; counter < m; ++ counter) {
			Polygon poly;
			int number;
			scanf("%d", &number);
			while (number --) {
				Point p;
				p.input(-1);
				poly.push(p);
			}

			tree.clear();
			for (int i = 0; i < n; ++ i) {
				if (poly.inside(point[i])) {
					tree.push(point[i]);
				}
			}
			tree.initialise();

			printf("Region %d\n", counter + 1);
			scanf("%d", &number);
			while (number --) {
				Point p;
				p.input(-1);
				int a, b;
				tree.query(p, a, b);
				printf("%d %d\n", a + 1, b + 1);
			}
		}
	}
	return 0;
}
