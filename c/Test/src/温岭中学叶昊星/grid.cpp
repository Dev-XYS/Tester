#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

ll T, n, m, C, D, mod, B[55][55], F[55][55][55][55];

void add(ll& X, ll Y) {X = (X + Y) % mod;}

int main()
{
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	scanf("%lld", &T);
	while(T--) {
		memset(B, 0, sizeof B), memset(F, 0, sizeof F), F[1][1][1][0] = 1;
		scanf("%lld%lld%lld%lld%lld", &n, &m, &C, &D, &mod);
		if(n <= 50 && m <= 50 && C <= 50) {
			for(int i = 1; i <= C; i++) {
				int x, y;
				scanf("%d%d", &x, &y);
				B[x][y] = 1;
			}
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= m; j++)
					for(int k = 1; k <= n; k++) {
						int s = i + j - k;
						if(s > m || s <= 0) continue;
						for(int b1 = 0; b1 < 2; b1++) {
							int ni = i + !b1, nj = j + b1;
							if(ni <= n && ni >= 1 && nj <= m && nj >= 1) for(int b2 = 0; b2 < 2; b2++) {
								int nk = k + !b2, ns = s + b2;
								if(nk <= n && nk >= 1 && ns <= m && ns >= 1 && (ni != nk || nj != ns))
									for(int f = 0; f <= D; f++)	add(F[ni][nj][nk][f + B[ni][nj] + B[nk][ns]], F[i][j][k][f]);
							}
						}
					}
			ll ans = 0;
			for(int i = 0; i <= D; i++) ans = (ans + F[n - 1][m][n][i]) % mod;
			printf("%lld\n", ans);
		}
	}
	return 0;
}
