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

inline void EnableFileIO(const string &fileName, bool local = 0) {
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

int n, m, c, d;
int p;

inline void add(int &a, const int &b) {
  a += b;
  if (a >= p) a -= p;
}
inline void add(LL &a, const LL &b) {
  a += b;
  if (a >= p) a -= p;
}
namespace DP {
#define N 52

int dp[2][N][N][N << 2];
int forb[N][N];

void solve() {
  memset(dp, 0, sizeof dp);
  memset(forb, 0, sizeof forb);
  for (int i = 0; i < c; i++) {
    int a, b;
    cin >> a >> b;
    forb[a][b] = 1;
  }
  int ans = 0;
  for (int i = 1; i <= n + m - 1; i++) {
    int pre = i & 1, cur = pre ^ 1;
    memset(dp[cur], 0, sizeof dp[cur]);
    if (i == 1) {
      dp[cur][1][1][0] = 1;
    }
    for (int j = 1; j <= min(i, n); j++) {
      if (i - j + 1 > m) continue;
      for (int k = 1; k <= min(i, j); ++k) {
        if (i - k + 1 > m) continue;
        if (j == k) {
          if (!(i == n + m - 1 && j == n && k == n)) continue;
        }
        for (int cc = 0; cc <= d; cc++) {
          int fn = forb[j][i - j + 1] + forb[k][i - k + 1];
          if (cc >= fn) {
            add(dp[cur][j][k][cc], dp[pre][j][k][cc - fn]);
            add(dp[cur][j][k][cc], dp[pre][j - 1][k - 1][cc - fn]);
            add(dp[cur][j][k][cc], dp[pre][j][k - 1][cc - fn]);
            add(dp[cur][j][k][cc], dp[pre][j - 1][k][cc - fn]);
          }
        }
      }
    }

    if (i == n + m - 1) {
      for (int cc = 0; cc <= d; cc++) add(ans, dp[cur][n][n][cc]);
    }
  }
  cout << ans << endl;
}
#undef N
}

namespace ciszero {
#define N 100005
int isp[N];
vector<int> pri;
LL val[(N << 1) + 10];
void init() {
  pri.clear();
  memset(isp, 0xf, sizeof isp);
  for (int i = 2; i < N; i++) {
    if (isp[i]) {
      pri.pb(i);
      for (int j = i; j < N; j += i) isp[j] = 0;
    }
  }
}
LL qpow(LL b, LL k) {
  LL r = 1;
  while (k) {
    if (k & 1) r = r * b % p;
    b = b * b % p;
    k >>= 1;
  }
  return r;
}
int cnt[N];
void add(int pp, int v) {
  int pv = pp;
  for (int i = 0; i < pri.size(); i++) {
    if (pri[i] * 1LL * pri[i] > pp) break;
    int c = 0;
    while (pv % pri[i] == 0) {
      pv /= pri[i];
      ++c;
    }
    cnt[pri[i]] += c * v;
  }
  if (pv > 1) cnt[pv] += v;
}
void calc(int n, int m) {
  // memset(cnt, 0, sizeof cnt);
  for (int i = n; i > n - m; i--) {
    add(i, 1);
  }
  for (int i = m; i; i--) {
    add(i, -1);
  }
}
void solve() {
  if (pri.empty()) init();
  memset(cnt, 0, sizeof cnt);
  // int n = ::n - 2, m = ::m - 1;
  calc(m + n - 4, m - 2);
  calc(m + n - 3, m - 2);
  add(m - 1, -1);
  LL ans = 1;
  for (int i = 1; i < N; i++) {
    if (cnt[i]) {
      (ans *= qpow(i, cnt[i])) %= p;
    }
  }
  cout << ans << endl;
}
}

int main() {
  // srand((int)time(0));
  // printf("Hello, world!\n");
  EnableFileIO("grid", 1);

  int T;
  cin >> T;
  while (T--) {
    cin >> n >> m >> c >> d >> p;
    if (n <= 50 && m <= 50) {
      DP::solve();
      continue;
    } else {
      ciszero::solve();
    }
  }
  return 0;
}
