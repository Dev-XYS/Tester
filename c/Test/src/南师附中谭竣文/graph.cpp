#include <string.h>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
// #include <unordered_map>
// #include <unordered_set>
#include <utility>
#include <vector>

#define pb push_back
#define mp make_pair

#ifdef ONLINE_JUDGE
#define link renamelink
#define next renamenext
#define prev renameprev
#endif

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
typedef long double ld;

inline void EnableFileIO(const string& fileName, bool local = 0) {
  if (fileName.empty()) return;
  if (local) {
    freopen((fileName + ".in").c_str(), "r", stdin);
    freopen((fileName + ".out").c_str(), "w", stdout);
    return;
  }
#ifdef ONLINE_JUDGE
  freopen((fileName + ".in").c_str(), "r", stdin);
  freopen((fileName + ".out").c_str(), "w", stdout);
#endif
}

const int INF = (1 << 30) - 1;
const LL LINF = (1LL << 61) - 1;
const double EPS = 1e-10, PI = acos(-1);

int n, m;
LL p;

const int MX = 1e9 + 7;
inline LL mul(LL a, LL b) {
  if (a <= MX && b <= MX) return a * b % p;
  LL res = 0;
  a %= p, b %= p;
  while (b) {
    if (b & 1) {
      res += a;
      if (res >= p) res -= p;
    }
    b >>= 1, a <<= 1;
    if (a >= p) a -= p;
  }
  return res;
}
inline LL qpow(LL b, LL k) {
  LL res = 1;
  while (k) {
    if (k & 1) res = mul(res, b);
    b = mul(b, b);
    k >>= 1;
  }
  return res;
}

const int N = 233, M = 2333;
int x[M], y[M];
LL va[N][N], vb[N][N];
vector<int> G[N];
int vis[N], stk[N], head, id[N][N], rev[N][N];
vector<vector<int> > cir;
LL a[M][M];

void dfs(int u, int p) {
  vis[u] = 1;
  stk[++head] = u;

  for (int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if (v == p) continue;
    if (!vis[v]) {
      dfs(v, u);
    } else if (vis[v] == 1) {
      // got circle
      vector<int> cur(0);
      cur.pb(v);
      int j = head;
      while (stk[j] != v) {
        cur.pb(stk[j]);
        --j;
      }
      cur.pb(v);
      reverse(cur.begin(), cur.end());
      cir.pb(cur);
    }
  }
  vis[u] = 2;
  --head;
}
int main() {
  // srand((int)time(0));
  // printf("Hello, world!\n");
  EnableFileIO("graph", 1);

  cin >> n >> m >> p;
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d%d%d", x + i, y + i, &a, &b);
    --x[i], --y[i];
    va[x[i]][y[i]] = a, va[y[i]][x[i]] = p - a;
    vb[x[i]][y[i]] = b, vb[y[i]][x[i]] = b;
    id[x[i]][y[i]] = i, id[y[i]][x[i]] = i, rev[y[i]][x[i]] = 1;
    G[x[i]].pb(y[i]), G[y[i]].pb(x[i]);
  }
  memset(vis, 0, sizeof vis);
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) dfs(i, -1);
  }
  int tot = (int)cir.size();
  for (int i = 0; i < cir.size(); i++) {
    vector<int>& vec = cir[i];
    LL sum = 0;
    for (int j = 0; j < vec.size() - 1; j++) {
      int u = vec[j], v = vec[j + 1], f = 1;
      if (rev[u][v]) f = -1;
      sum += va[u][v];
      a[i][id[u][v]] = vb[u][v] * f;
    }
    a[i][m] = sum;
  }
  for (int u = 0; u < n; u++) {
    for (int i = 0; i < G[u].size(); i++) {
      int v = G[u][i], f = 1;
      if (rev[u][v]) f = -1;
      a[tot][id[u][v]] = f;
    }
    tot++;
  }

  for (int i = 0; i < tot; i++) {
    for (int j = 0; j <= m; j++) a[i][j] = (a[i][j] % p + p) % p;
  }
  for (int i = 0; i < tot; i++) {
    int c = -1;
    for (int j = i; j < tot; j++) {
      if (a[j][i]) {
        c = j;
        break;
      }
    }
    if (c < 0) {
      // cerr << "BREAK AT " << i << endl;
      break;
    }
    for (int j = i; j <= m; j++) swap(a[i][j], a[c][j]);
    LL inv = qpow(a[i][i], p - 2);
    for (int j = i; j <= m; j++) a[i][j] = mul(a[i][j], inv);

    for (int j = 0; j < tot; j++) {
      if (i == j) continue;
      LL t = a[j][i];
      for (int k = i; k <= m; k++) {
        a[j][k] -= mul(a[i][k], t);
        if (a[j][k] < 0) a[j][k] += p;
      }
    }
  }

  for (int i = 0; i < m; i++) {
    int k = id[x[i]][y[i]];
    cout << a[k][m] << endl;
  }
  return 0;
}

/*
4 5 19
 1 2 1 1
 2 3 0 1
 1 4 1 2
 3 1 1 1
 4 2 0 1
*/
