#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 2e5 + 5;
const int L = 19;
const ll inf = 1e17;

typedef long long ll;
typedef pair<ll, int> pii;
#define fir first
#define sec second


ll dis[N];
int vis[N], p[N];
int n, m, s;

bool cmprank(pii x, pii y) {
	return p[x.sec] < p[y.sec];
}

bool cmpdis(int x, int y) {
	return dis[x] < dis[y];
}

vector <pii> G[N], T[N], R[N];
int fa[N][L], mn[N][L], dep[N];

void build(int x) {
	vis[x] = 1;
	sort(G[x].begin(), G[x].end(), cmprank);
	for (int i = 0; i < G[x].size(); ++i) {
		pii u = G[x][i];
		if (dis[u.sec] == dis[x] + u.fir) {
			if (!vis[u.sec]) {
				T[x].push_back(u);
				fa[u.sec][0] = x;
				dep[u.sec] = dep[x] + 1;
				build(u.sec);
			} else {
				R[x].push_back(u);
			}
		}
	}
}


int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	int d = dep[x] - dep[y];
	for (int i = 0; i < L; ++i)
		if (d & (1 << i)) x = fa[x][i];
	if (x == y) return x;
	for (int i = L-1; ~i; --i)
		if (fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

int query(int x, int d) {
	int ret = n + 1;
	for (int i = 0; i < L; ++i)
		if (d & (1 << i)) {
			ret = min(ret, mn[x][i]);
			x = fa[x][i];
		}
	return ret;
}


priority_queue <pii> q;
void dijkstra(int s) {
	for (int i = 1; i <= n; ++i) dis[i] = inf;
	dis[s] = 0, q.push(pii(0, s));

	while (!q.empty()) {
		pii v = q.top(); q.pop();
		if (vis[v.sec]) continue;
		vis[v.sec] = 1;

		for (int i = 0; i < G[v.sec].size(); ++i) {
			pii e = G[v.sec][i];
			if (dis[e.sec] > -v.fir + e.fir) {
				dis[e.sec] = -v.fir + e.fir;
				q.push(pii(-dis[e.sec], e.sec));
			}
		}
	}
}


int type, last;

int main() {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);

	n = read(), m = read();
	s = read(), type = read();
	for (int i = 1; i <= n; ++i) p[i] = read();
	for (int i = 1; i <= m; ++i) {
		int u = read(), v = read(), w = read();
		G[u].push_back(pii(w, v));
		G[v].push_back(pii(w, u));
	}

	dijkstra(s);

	for (int i = 1; i <= n; ++i) vis[i] = 0;
	build(s);

	for (int i = 1; i <= n; ++i) p[i] = i;
	sort(p + 1, p + 1 + n, cmpdis);

	for (int i = 1; i < L; ++i) 
		for (int j = 1; j <= n; ++j)
			fa[j][i] = fa[fa[j][i-1]][i-1];

	for (int i = 1; i <= n; ++i) mn[i][0] = dep[i];
	for (int i = 1; i <= n; ++i) {
		int x = p[i];
		for (int i = 1; i < L; ++i) 
			mn[x][i] = min(mn[x][i-1], mn[fa[x][i-1]][i-1]);
		for (int i = 0; i < R[x].size(); ++i) {
			pii u = R[x][i];
			int pa = lca(x, u.sec);
			int tp = query(x, dep[x] - dep[pa] + 1);
			mn[u.sec][0] = min(mn[u.sec][0], tp);
		}
	}


	m = read();
	for (int i = 1; i <= m; ++i) {
		int x = read() ^ last;
		int y = read() ^ last;
		int l = dep[x] + 1, r = dep[y], ans = dep[x];
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (query(y, dep[y] - mid + 1) <= dep[x]) 
				ans = mid, l = mid+1;
			else r = mid - 1;
		}
		ans = ans - dep[x];
		printf("%d\n", ans);
		if (type) last = ans;
	}
	return 0;
}