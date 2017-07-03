#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 205;
int T, R, C, n, m, P, ans;
struct X { int x, y; } s[MAXN];
inline bool cmp(X A, X B) { return A.x != B.x ? A.x < B.x : A.y < B.y; }

int tot, factor[40], pw[40], fac[15][200005], cnt[15][200005];
inline void init(int Mod) {
	tot = 0;
	for(int i = 2; i * i <= Mod; ++i) if(Mod % i == 0) {
		factor[++tot] = i; pw[tot] = 1;
		while(Mod % i == 0) Mod /= i, pw[tot] *= i;
	}
	if(Mod > 1) { factor[++tot] = Mod; pw[tot] = Mod; }
	
	for(int k = 1; k <= tot; ++k) {
		for(int i = fac[k][0] = 1; i <= R + C; ++i) {
			int d = i;
			cnt[k][i] = cnt[k][i-1];
			while(d % factor[k] == 0) d /= factor[k], ++cnt[k][i];
			fac[k][i] = 1LL * d * fac[k][i-1] % pw[k];
		}
	}
}

inline int QuickPow(int x, int k, int mod) {
	int res = 1;
	for(; k; k >>= 1, x = 1LL * x * x % mod) if(k & 1) res = 1LL * res * x % mod;
	return res;
}

inline int Comb(int N, int M) {
	if(N < 0 || M < 0 || M > N) return 0;
	int res = 0;
	for(int k = 1; k <= tot; ++k) {
		int phi = pw[k] / factor[k] * (factor[k] - 1), mod = pw[k];
		int delta = QuickPow(factor[k], cnt[k][N] - cnt[k][M] - cnt[k][N-M], mod);
		int Combine = 1LL * fac[k][N] * QuickPow(1LL * fac[k][M] * fac[k][N-M] % mod, phi - 1, mod) % mod * delta % mod;
		res = (res + 1LL * Combine * QuickPow(P / mod, phi, P)) % P;
	}
	return res;
}

int jump[MAXN][MAXN], f[2][2][MAXN], g[MAXN][MAXN];
inline void calc(int F[MAXN], X Start, X End) {
	s[0] = Start; s[n + 1] = End;
	for(int i = 0, j = 1; j <= n + 1; ++j) {
		jump[i][j] = Comb(s[j].x-s[i].x+s[j].y-s[i].y, s[j].x-s[i].x);
		for(int k = 1; k < j; ++k)
			jump[i][j] = (jump[i][j] - 1LL * jump[i][k] * Comb(s[j].x-s[k].x+s[j].y-s[k].y, s[j].x-s[k].x)) % P;
	}
	for(int i = 0, j = n + 1; i <= n; ++i) {
		jump[i][j] = Comb(s[j].x-s[i].x+s[j].y-s[i].y, s[j].x-s[i].x);
		for(int k = i + 1; k < j; ++k)
			jump[i][j] = (jump[i][j] - 1LL * jump[i][k] * Comb(s[j].x-s[k].x+s[j].y-s[k].y, s[j].x-s[k].x)) % P;
	}
	
	memset(g, 0, sizeof g);
	g[0][0] = 1;
	for(int i = 1; i <= n + 1; ++i)
	for(int j = 1; j <= i; ++j)
	for(int k = 0; k < i; ++k)
		g[i][j] = (g[i][j] + 1LL * g[k][j-1] * jump[k][i]) % P;
	
	for(int i = 0; i <= m; ++i) F[i] =  g[n + 1][i + 1];
}

int main() {
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d%d%d", &R, &C, &n, &m, &P);
		init(P);
		for(int i = 1; i <= n; ++i) scanf("%d%d", &s[i].x, &s[i].y);
		sort(s + 1, s + n + 1, cmp);
		
		for(int i = 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j) {
			jump[i][j] = Comb(s[j].x-s[i].x+s[j].y-s[i].y, s[j].x-s[i].x);
			for(int k = i + 1; k < j; ++k)
				jump[i][j] = (jump[i][j] - 1LL * jump[i][k] * Comb(s[j].x-s[k].x+s[j].y-s[k].y, s[j].x-s[k].x)) % P;
		}
		
		calc(f[0][0], (X) { 2, 1 }, (X) { R, C - 1 });
		calc(f[0][1], (X) { 2, 1 }, (X) { R - 1, C });
		calc(f[1][0], (X) { 1, 2 }, (X) { R, C - 1 });
		calc(f[1][1], (X) { 1, 2 }, (X) { R - 1, C });
		
		ans = 0;
		for(int i = 0; i <= m; ++i)
		for(int j = 0; i + j <= m; ++j)
			ans = (ans + 1LL * f[0][0][i] * f[1][1][j] - 1LL * f[0][1][i] * f[1][0][j]) % P;
		printf("%d\n", (ans % P + P) % P);
	}
	return 0;
}
