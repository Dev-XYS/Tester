#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_N = 100005;
typedef long long LL;
typedef pair<int, int> pii;
#define fi first
#define se second

inline LL fpm(LL x, LL y, int mod) {
  LL res = 1;
  while (y) {
    if (y & 1) res = 1LL * res * x % mod;
    x = 1LL * x * x % mod;
    y >>= 1;
  }
  return res;
}

inline void extgcd(LL &x, LL &y, LL a, LL b) {
  if (a == 0) {
    x = 0, y = 1;
    return;
  }
  extgcd(x, y, b % a, a);
  LL t = x;
  x = y - (b / a) * x, y = t;
}

inline LL get_inv(LL x, LL mod) {
  LL a, b;
  extgcd(a, b, x, mod);
  return (a + mod) % mod;
}

pii pr[13], fac[13][MAX_N << 1];
int N, M, C, D, MOD, tot;

inline int get(int n, int m, int x) {
  if (n < m) return 0;
  pii a = fac[x][n], b = fac[x][m], c = fac[x][n - m];
  LL res = 1LL * a.fi * get_inv(1LL * b.fi * c.fi % pr[x].fi, pr[x].fi) % pr[x].fi;
  res = 1LL * res * fpm(pr[x].se, a.se - b.se - c.se, pr[x].fi) % pr[x].fi;
  return res;
}

inline LL binom(int n, int m) {
  static LL X[20], Y[20];
  for (int i = 1; i <= tot; ++i)
    X[i] = get(n, m, i), Y[i] = pr[i].fi;
  LL res = 0;
  for (int i = 1; i <= tot; ++i) {
    LL x = 1LL * X[i] * (MOD / pr[i].fi) % MOD;
    res = (res + 1LL * x * get_inv(MOD / pr[i].fi, pr[i].fi) % MOD) % MOD;
  }
  return res;
}

void init() {
  scanf("%d%d%d%d%d", &N, &M, &C, &D, &MOD);
  tot = 0;
  int tmp = MOD;
  for (int i = 2, num; i * i <= tmp; ++i) 
    if (tmp % i == 0) {
      ++tot, num = 1;
      while (tmp % i == 0) tmp /= i, num *= i;
      pr[tot] = make_pair(num, i);
    }
  if (tmp != 1) pr[++tot] = make_pair(tmp, tmp);

  for (int i = 1; i <= tot; ++i) {
    fac[i][0] = make_pair(1, 0);
    for (int j = 1; j <= N + M; ++j) {
      int tmp = j, num = 0;
      while (tmp % pr[i].se == 0) tmp /= pr[i].se, num++;
      fac[i][j].fi = 1LL * fac[i][j - 1].fi * tmp % pr[i].fi;
      fac[i][j].se = fac[i][j - 1].se + num;
    }
  }
}

pii p[205];
LL g[205][205];

void calc(LL *f, pii st, pii end) {
  for (int i = 0; i <= C; ++i) f[i] = 0;
  memset(g, 0, sizeof g);
  
  p[0] = st, p[C + 1] = end;
  
  g[0][0] = 1;
  for (int i = 1; i <= C; ++i) {
    for (int j = 0; j < i; ++j) {
      if (p[i].fi < p[j].fi || p[i].se < p[j].se) continue;
      int way = binom(p[i].fi - p[j].fi + p[i].se - p[j].se, p[i].fi - p[j].fi);
      for (int k = 1; k <= C; ++k) {
	g[i][k] = (g[i][k] + 1LL * way * g[j][k - 1] % MOD) % MOD;
	g[i][k] = (g[i][k] - 1LL * way * g[j][k] % MOD) % MOD;
      }
    }
  }
  
  for (int i = 1; i <= C; ++i)
    if (p[i] == end) {
      memcpy(f, g[i], sizeof g[i]);
      return;
    }
  
  for (int i = 0; i <= C; ++i) {
    if (p[i].fi > end.fi || p[i].se > end.se) continue;
    int way = binom(end.fi - p[i].fi + end.se - p[i].se, end.fi - p[i].fi);
    for (int k = 0; k <= C; ++k) {
      f[k] = (f[k] + 1LL * way * g[i][k] % MOD) % MOD;
      f[k] = (f[k] - 1LL * way * g[i][k + 1] % MOD) % MOD;
    }
  }
}

LL f[2][2][205];

void work() {
  for (int i = 1; i <= C; ++i)
    scanf("%d%d", &p[i].fi, &p[i].se);

  sort(p + 1, p + C + 1);

  calc(f[0][0], make_pair(2, 1), make_pair(N, M - 1));
  calc(f[0][1], make_pair(2, 1), make_pair(N - 1, M));
  calc(f[1][0], make_pair(1, 2), make_pair(N, M - 1));
  calc(f[1][1], make_pair(1, 2), make_pair(N - 1, M));

  LL res = 0;
  for (int i = 0; i <= D; ++i)
    for (int j = 0; i + j <= D; ++j) {
      res = (res + 1LL * f[0][0][i] * f[1][1][j] % MOD) % MOD;
      res = (res - 1LL * f[0][1][i] * f[1][0][j] % MOD) % MOD;
    }
  printf("%lld\n", (res + MOD) % MOD);
}

int main() {
  freopen("grid.in", "r", stdin);
  freopen("grid.out", "w", stdout);

  int T;
  scanf("%d", &T);
  while (T--) {
    init();
    work();
  }
  return 0;
}
