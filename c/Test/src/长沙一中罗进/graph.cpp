#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_N = 105, MAX_M = 2005;
typedef long long LL;

class Edge {
public:
  int nxt, to;
  LL A, B;
} e[MAX_M << 1];

int N, M;
LL MOD;

LL mul(LL x, LL y) {
  LL res = 0;
  if (y < MOD) y += MOD;
  while (y) {
    if (y & 1) res = (res + x) % MOD;
    x = (x + x) % MOD;
    y >>= 1;
  }
  return res;
}

LL fpm(LL x, LL y) {
  LL res = 1;
  while (y) {
    if (y & 1) res = mul(res, x);
    x = mul(x, x);
    y >>= 1;
  }
  return res;
}

int head[MAX_N];
void addedge(int u, int v, int A, int B) {
  static int cnt;
  e[++cnt] = (Edge){head[u], v, A, B}, head[u] = cnt;
  e[++cnt] = (Edge){head[v], u, -A, B}, head[v] = cnt;
}

#define rev(x) (x & 1 ? x + 1 : x - 1)
LL val[MAX_M << 1][MAX_N], B[MAX_M << 1];
int up[MAX_N], cnt = 0, id[MAX_M << 1], fa[MAX_N];

void dfs(int u, int v) {
  static int dfn[MAX_N], tot = 0;

  dfn[u] = ++tot;
  for (int i = head[u]; i; i = e[i].nxt)
    if (e[i].to != v) {
      if (!dfn[e[i].to]) {
	up[e[i].to] = i, id[i] = id[rev(i)] = ++cnt, fa[e[i].to] = u;
	dfs(e[i].to, u);
      } else if (dfn[e[i].to] < dfn[u]) {
	int tmp = u;
	LL inv = fpm(e[i].B, MOD - 2);
	
	while (tmp != e[i].to) {
	  int flag = (up[tmp] & 1) ? 1 : -1;
	  val[i][id[up[tmp]]] = -flag * mul(e[up[tmp]].B, inv);
	  B[i] = (B[i] + mul(e[up[tmp]].A, inv)) % MOD;
	  tmp = fa[tmp];
	}
	
	B[i] = (B[i] + mul(e[i].A, inv)) % MOD;
	for (int j = 1; j <= N; ++j) val[rev(i)][j] = -val[i][j];
	B[rev(i)] = -B[i];
      }
    }
}

int tot = 0;
LL G[MAX_N][MAX_N], F[MAX_N], res[MAX_N];

void Gauss() {
  for (int i = 1; i <= cnt; ++i) {
    int k = i;
    for (; k <= tot; ++k)
      if (G[i][k]) 
	break;
    if (i != k) 
      swap(G[i], G[k]), swap(F[i], F[k]);
    LL inv = fpm(G[i][i], MOD - 2);
    for (int j = 1; j <= tot; ++j) {
      if (i == j) continue;
      LL tmp = mul(G[j][i], inv);
      for (int x = i; x <= cnt; ++x)
	G[j][x] = (G[j][x] - mul(G[i][x], tmp)) % MOD;
      F[j] = (F[j] - mul(F[i], tmp)) % MOD;
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    LL inv = fpm(G[i][i], MOD - 2);
    res[i] = mul(F[i], inv);
  }
}

int main() {
  freopen("graph.in", "r", stdin);
  freopen("graph.out", "w", stdout);

  scanf("%d%d%lld\n", &N, &M, &MOD);
  for (int i = 1; i <= M; ++i) {
    int u, v;
    LL a, b;
    scanf("%d%d%lld%lld\n", &u, &v, &a, &b);
    addedge(u, v, a, b);
  }

  dfs(1, 0);

  for (int u = 1; u <= N; ++u) {
    ++tot;
    for (int i = head[u]; i; i = e[i].nxt)
      if (id[i]) {
	if (i & 1) G[tot][id[i]]++;
	else G[tot][id[i]]--;
      } else {
	F[tot] = (F[tot] - B[i]) % MOD;
	for (int j = 1; j <= cnt; ++j)
	  G[tot][j] = (G[tot][j] + val[i][j]) % MOD;
      }
  }
  
  Gauss();

  for (int i = 1; i <= M; ++i) 
    if (id[i * 2 - 1]) {
      printf("%lld\n", (res[id[i * 2 - 1]] + MOD) % MOD);
    } else {
      LL tmp = B[i * 2 - 1];
      for (int j = 1; j <= cnt; ++j)
	tmp = (tmp + mul(res[j], val[i * 2 - 1][j])) % MOD;
      printf("%lld\n", (tmp + MOD) % MOD);
    }

  
  return 0;
}
