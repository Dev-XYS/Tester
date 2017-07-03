#include <cstdio>
#include <algorithm>
using namespace std;


const int M = 15;

int n, m, p;
struct Edge {
	int x, y, a, b, d;
	void exchange() {
		a %= p, b %= p;
		if(x > y) {
			if (x == 3 && y == 1) return;
			swap(x, y), b = p-b, d = 1;
		} else {
			if (x == 1 && y == 3) {
				swap(x, y), b = p-b, d = 1;
			}
		}
	}
} e[M];

bool check(int x) {
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= m; ++i) sum2 += e[i].a;
	for (int i = 1; i <= m; ++i) sum1 += e[i].b * x;
	return (sum1 % p) == (sum2 % p);
}

int main() {
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);

	scanf("%d%d%d", &n, &m, &p);
	for (int i = 1; i <= m; ++i) 
		scanf("%d%d%d%d", &e[i].x, &e[i].y, &e[i].a, &e[i].b);
	for (int i = 1; i <= m; ++i) e[i].exchange();
	for (int i = 0; i < p; ++i) 
		if (check(i)) {
			for (int j = 1; j <= m; ++j)
				if (e[j].d) printf("%d\n", p - i);
				else printf("%d\n", i);
			break;
		}
	return 0;
}