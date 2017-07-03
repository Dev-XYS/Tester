#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int LEN = 1e5 + 5;
int i, j, k, n, m, s, t, ans, C, D, mod;
const int dx[2] = {0, 1};
const int dy[2] = {1, 0};
struct node {
	int x, y;
} a[LEN];
bool IN(int x, int y) {
	return 1 <= x && x <= n && 1 <= y && y <= m;
}
void Plus(int &x, int y) {
	x += y;
	if (x >= mod) {
		x -= mod;
	}
}
namespace D1 {
	int a[55][55];
	int dp[105][55][55][55];
	void DO() {
		memset(a, 0, sizeof(a));
		for (int i = 1; i <= C; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			a[x][y] = 1;
		}
		memset(dp, 0, sizeof(dp));
		dp[2][1][1][0] = 1;
		for (int i = 2; i < n + m; i++) {
			for (int x1 = 1; x1 <= n; x1++) {
				for (int x2 = x1; x2 <= n; x2++) {
					for (int k = 0; k <= D; k++) {
						if (dp[i][x1][x2][k]) {
							int y1 = i - x1, y2 = i - x2;
				        	if (IN(x1, y1) && IN(x2, y2)) {
				        		for (int k1 = 0; k1 < 2; k1++) {
						        	for (int k2 = 0; k2 < 2; k2++) {
							        	int X1 = x1 + dx[k1], X2 = x2 + dx[k2];
						         		int Y1 = y1 + dy[k1], Y2 = y2 + dy[k2];
						         		if (X1 > X2) {
						         			continue;
						         		}
						  		        if (IN(X1, Y1) && IN(X2, Y2) && (X1 != X2 || X1 == n && X2 == n && Y1 == m && Y2 == m)) {
						  		        	int t = a[X1][Y1] + a[X2][Y2];
							        		Plus(dp[i + 1][X1][X2][k + t], dp[i][x1][x2][k]);
							        	}
					        		}
				        		}
				        	}
						}
					}
				}
			}
		}
		int ans = 0;
		for (int k = 0; k <= D; k++) {
			Plus(ans, dp[n + m][n][n][k]);
		}
		printf("%d\n", ans);
	}
}
int main() {
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %d %d", &n, &m, &C, &D, &mod);
		if (n <= 50 && m <= 50) {
			D1 :: DO();
		}
	}
	return 0;
}
