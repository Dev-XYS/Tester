

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

const int N = 1e5 + 100;

int n, m, tp, cap;
int pri[N];
typedef pair<int, LL> pil;

struct edge {
  int to, w;
  int id;
  edge(int _t, int _w, int _i) : to(_t), w(_w), id(_i) {}
};
vector<edge> G[N], tr[N];
LL capdis[N];
int inq[N], del[N << 1];
queue<int> que;
void spfa(int s, LL dist[N]) {
  while (!que.empty()) que.pop();
  for (int i = 0; i < n; i++) dist[i] = LINF, inq[i] = 0;
  que.push(s), inq[s] = 1, dist[s] = 0;
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    // if (u == dest) return;
    for (int i = 0; i < G[u].size(); i++) {
      edge& e = G[u][i];
      if (del[e.id]) continue;
      if (dist[e.to] > dist[u] + e.w) {
        dist[e.to] = dist[u] + e.w;
        if (!inq[e.to]) que.push(e.to), inq[e.to] = 1;
      }
    }
    inq[u] = 0;
  }
  return;
}
inline bool comp(const edge& a, const edge& b) { return pri[a.to] < pri[b.to]; }
int vis[N], link[N], linkid[N << 1];
void build(int u) {
  vis[u] = 1;
  sort(G[u].begin(), G[u].end(), comp);
  for (int i = 0; i < G[u].size(); i++) {
    edge& e = G[u][i];
    if (vis[e.to]) continue;
    if (capdis[e.to] == capdis[u] + e.w) {
      // possible
      del[e.id] = 1;
      tr[u].pb(edge(e.to, e.w, e.id));
      tr[e.to].pb(edge(u, e.w, e.id));
      link[e.to] = u;
      linkid[e.to] = e.id;
      build(e.to);
    }
  }
}
int seq[N], cnt;
LL buff[N];

int main() {
  // srand((int)time(0));
  // printf("Hello, world!\n");
  EnableFileIO("road", 1);

  scanf("%d%d%d%d", &n, &m, &cap, &tp);
  --cap;
  for (int i = 0; i < n; i++) scanf("%d", pri + i);
  for (int i = 0; i < m; i++) {
    int u, v, l;
    scanf("%d%d%d", &u, &v, &l);
    --u, --v;
    G[u].pb(edge(v, l, i));
    G[v].pb(edge(u, l, i));
  }

  spfa(cap, capdis);
  build(cap);
  
  memset(del, 0, sizeof del);

  /*
  for (int i = 0; i < n; i++) {
    spfa(i, dist[i]);
    dfs(i, i);
  }
   */
  // dfs(cap, -1, 0);
  // hld(cap, 0, -1);

  int q, ans = 0;
  scanf("%d", &q);
  for (int _t = 0; _t < q; ++_t) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (tp) u ^= ans, v ^= ans;
    --u, --v;
    cnt = 0;

    int cv = v;
    while (cv != u) {
      seq[cnt++] = linkid[cv];
      cv = link[cv];
    }
    // seq[cnt++] = u;
    reverse(seq, seq + cnt);

    int l = -1, r = cnt;
    while (r - l > 1) {
      int mid = (l + r) >> 1;
      for (int i = 0; i <= mid; i++) del[seq[i]] = 1;
      spfa(cap, buff);
      if (capdis[v] == buff[v]) {
        l = mid;
      } else {
        r = mid;
      }
      for (int i = 0; i <= mid; i++) del[seq[i]] = 0;
    }
    ans = l + 1;
    printf("%d\n", ans);
  }
  return 0;
}

/*
 4 4 1 0
 1 2 3 4
 1 2 1
 2 3 1
 1 4 1
 4 3 1
 2
 1 4
 2 3
 */
