#include <cstdio>
#include <algorithm>
#define FOR(i, l, r) for(int i = l; i <= r; i++)

using namespace std;

const int M = 2010, N = 110;
typedef long long ll;
ll mod, a[M], b[M], f[N][N];
int x[M], y[M], n, m;

ll tim(ll a, ll b)
{
	ll ans = 0;
	for(; b; b >>= 1)
	{
		if (b & 1) {ans += a; if (ans >= mod) ans -= mod;}
		a <<= 1; if (a >= mod) a -= mod;
	}
	return ans;
}

ll pow(ll a, ll b)
{
	ll ans = 1;
	for(; b; b >>= 1)
	{
		if (b & 1) ans = tim(ans, a);
		a = tim(a, a);
	}
	return ans;
}

void ins(int x, int y, ll a, ll b)
{
	(f[x][y] += b) %= mod;
	(f[x][x] += mod - b) %= mod;
	(f[x][n + 1] += mod - tim(a, b)) %= mod;
}

void gauss()
{
	FOR(i, 1, n)
	{
		int tmp;
		FOR(j, i, n) if (f[j][i]) {tmp = i; break;}
		if (tmp != i) FOR(j, i, n + 1) swap(f[i][j], f[tmp][j]);
		ll tt = pow(f[i][i], mod - 2); FOR(j, i, n + 1) f[i][j] = tim(f[i][j], tt);
		FOR(j, 1, n) if (j != i && f[j][i])
		{
			FOR(k, i + 1, n + 1) f[j][k] = (f[j][k] + mod - tim(f[j][i], f[i][k])) % mod;
			f[j][i] = 0;
		}
	}
}

int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	scanf("%d%d%lld", &n, &m, &mod); f[1][1] = 1;
	FOR(i, 1, m)
	{
		scanf("%d%d%lld%lld", &x[i], &y[i], &a[i], &b[i]); b[i] = pow(b[i], mod - 2);
		if (x[i] != 1) ins(x[i], y[i], a[i], b[i]);
		if (y[i] != 1) ins(y[i], x[i], (mod - a[i]) % mod, b[i]);
	}
	gauss();
	FOR(i, 1, m)
		printf("%lld\n", tim((f[y[i]][n + 1] - f[x[i]][n + 1] + a[i] + mod) % mod, b[i]));
	return 0;
}
