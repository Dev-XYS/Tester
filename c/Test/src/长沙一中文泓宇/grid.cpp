#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;


const int N = 55;
int cas, n, m, k1, k2, mod;
vector <int> r[N];


int dp[2][N][N][N], o;
#define f dp[o]
#define g dp[!o]


int get(int s[][N], int l1, int r1, int l2, int r2) {
	return s[l2][r2] - s[l2][r1-1] - s[l1-1][r2] + s[l1-1][l2-1];
}

int main() {
	freopen("grid.in", "r", stdin);
	//freopen("grid.out", "w", stdout);

	scanf("%d", &cas);
	while (cas-- ) {
		scanf("%d%d%d%d%d", &n, &m, &k1, &k2, &mod);

		for (int i = 1, x, y; i <= k1; ++i) {
			scanf("%d%d", &x, &y);
			r[y].push_back(x);
		}
		for (int i = 1; i <= m; ++i) {
			r[i].push_back(0);
			r[i].push_back(n+1);
			sort(r[i].begin(), r[i].end());
		}

		memset(dp, 0, sizeof(dp));

		g[0][1][2] = 1;
		for (int i = 1; i <= m; ++i) {
			memset(f, 0, sizeof(f));
			for (int d = 0; d <= k2; ++d) {
				for (int p1 = 1; p1 <= n; ++p1)
					for (int p2 = p1 + 1; p2 <= n; ++p2) {
						int t = 0;
						while (r[i][t] < p2) ++t;
						for (int o1 = 1; o1 < t; ++o1)
							for (int o2 = t; o2 < r[i].size(); ++o2) {
								int no = o1 + o2 - 2;
								int l1 = 1, r1 = r[i][o1] - 1;
								int l2 = 1, r2 = r[i][o2] - 1;
								(f[d+no][p1][p2] += get(g[d], l1, r1, l2, r2)) %= mod;
							}
					}

				for (int p1 = 1; p1 <= n; ++p1)
					for (int p2 = 1; p2 <= n; ++p2) 
						(f[d][p1][p2] += f[d][p1-1][p2] + f[d][p1][p2-1] - f[d][p1-1][p2-1]) %= mod;
			}
			o ^= 1;
		}

		int ans = 0;
		for (int d = 0; d <= k2; ++d)
			(ans += g[d][n-1][n]) %= mod;
		(ans += mod) %= mod;
		printf("%d\n", ans);
	}
	return 0;
}