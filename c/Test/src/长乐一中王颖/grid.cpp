#include <cstdio>
#include <iostream>
using namespace std;
inline int Get() {
	char ch;
	while ((ch = getchar()) < '0' || ch > '9');
	int Num = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		Num = (Num << 3) + (Num << 1) + ch - '0';
	return Num;
}
int T, n, m, C, D, Mod, Case;
int g[105][55][55][55], map[55][55];
inline int check(int n, int a) {
	int b = n - a;
	return map[a + 1][b + 1] == Case;
}
void solve1() {
	++Case;
	for (int i = 1; i <= C; ++i) {
		int x = Get(), y = Get();
		map[x][y] = Case;
	}
	
	D = min(D, C);
	for (int k = 0; k <= n + m; ++k)
		for (int a = 0; a <= n; ++a)
			for (int b = 0; b <= n; ++b) 
				for (int x = 0; x <= C; ++x) g[k][a][b][x] = 0;
	
	g[0][0][0][0] = 1;
	for (int i = 0; i < n + m - 2; ++i) 
		for (int a = 0; a < n; ++a)
			for (int b = a; b < n; ++b)
				for (int x = 0; x <= D; ++x)
					if (g[i][a][b][x]) {
						if (i + 1 - a < m && i + 1 - b < m && (i == n + m - 3 || a != b)) 
							if ((g[i + 1][a][b][x + check(i + 1, a) + check(i + 1, b)] += g[i][a][b][x]) >= Mod) 
								g[i + 1][a][b][x + check(i + 1, a) + check(i + 1, b)] -= Mod;
							
						if (a + 1 < n && i + 1 - b < m && (i == n + m - 3 || a + 1 != b) && a + 1 <= b) 
							if ((g[i + 1][a + 1][b][x + check(i + 1, a + 1) + check(i + 1, b)] += g[i][a][b][x]) >= Mod) 
								g[i + 1][a + 1][b][x + check(i + 1, a + 1) + check(i + 1, b)] -= Mod;
							
						if (i + 1 - a < m && b + 1 < n && (i == n + m - 3 || a != b + 1)) 
							if ((g[i + 1][a][b + 1][x + check(i + 1, a) + check(i + 1, b + 1)] += g[i][a][b][x]) >= Mod) 
								g[i + 1][a][b + 1][x + check(i + 1, a) + check(i + 1, b + 1)] -= Mod;
							
						if (a + 1 < n && b + 1 < n && (i == n + m - 3 || a != b)) 
							if ((g[i + 1][a + 1][b + 1][x + check(i + 1, a + 1) + check(i + 1, b + 1)] += g[i][a][b][x]) >= Mod) 
								g[i + 1][a + 1][b + 1][x + check(i + 1, a + 1) + check(i + 1, b + 1)] -= Mod;
					}
	
	int ans = 0;
	for (int i = 0; i <= D; ++i) 
		if ((ans += g[n + m - 2][n - 1][n - 1][i]) >= Mod) ans -= Mod;

	printf("%d\n", ans);
}
int main() {
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	T = Get();
	while (T--) {
		n = Get(), m = Get(), C = Get(), D = Get(), Mod = Get();
		if (n <= 50 && m <= 50) solve1();
	}
	fclose(stdin);
	fclose(stdout);
}