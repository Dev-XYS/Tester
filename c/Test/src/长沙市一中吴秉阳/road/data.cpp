#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


int main() {
	freopen("road.in", "r", stdin);
	freopen("road.in", "w", stdout);
	
	int n = 100000, m = n - 1, S = 1;
	printf("%d %d %d %d\n", n, m, S, 0);
	for(int i = 1; i <= n; ++i) printf("%d ", i);
	puts("");
	for(int i = 1; i < n; ++i) printf("%d %d %d\n", i, i + 1, 1);
	puts("0");
	return 0;
}
