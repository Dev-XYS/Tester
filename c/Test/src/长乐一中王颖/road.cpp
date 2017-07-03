#include <queue>
#include <cstdio>
using namespace std;
inline int Get() {
	char ch;
	while ((ch = getchar()) < '0' || ch > '9');
	int Num = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		Num = (Num << 3) + (Num << 1) + ch - '0';
	return Num;
}
const int N = 1e5 + 5;
const int M = 2e5 + 5;
const int INF = 1e9;
bool vis[N];
int n, m, s, ty, lev[N], centre, dist[N], fa[N], from[N], dep[N], cnt, D[N], W[N];
int tot, first[N], next[M << 1], end[M << 1], cap[M << 1], mark[M << 1];
queue <int> que;
inline void AddEdge(int x, int y, int z) {
	next[++tot] = first[x], first[x] = tot, end[tot] = y, cap[tot] = z, mark[tot] = INF;
	next[++tot] = first[y], first[y] = tot, end[tot] = x, cap[tot] = z, mark[tot] = INF;
}
void SPFA(int x) {
	for (int i = 1; i <= n; ++i) dist[i] = INF;
	dist[x] = 0, vis[x] = true, que.push(x);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		vis[u] = false;
		for (int k = first[u], v; v = end[k], k; k = next[k]) 
			if (dist[v] > dist[u] + cap[k]) {
				dist[v] = dist[u] + cap[k];
				if (!vis[v]) {
					vis[v] = true;
					que.push(v);
				}
			}
	}
}
void build() {
	fa[centre] = 0, dep[centre] = 1, cnt = 1;
	int cur = centre;
	while (cnt < n) {
		int R = -1, K = 0;
		for (int k = first[cur], v; v = end[k], k; k = next[k]) 
			if (!dep[v] && dist[v] == dist[cur] + cap[k])
				if (R < 0 || lev[R] > lev[v]) R = v, K = k;
			
		if (R < 0) {
			cur = fa[cur];
			continue;
		}
		
		++cnt;
		fa[R] = cur, dep[R] = dep[cur] + 1;
		from[R] = K, cur = R;
	}
}
inline int merge(int x, int y) {
	if (!x || !y) return x + y;
	return min(x, y);
}
inline int relax(int x, int dist, int w) {
	if (dist < D[x]) {
		D[x] = dist, W[x] = w;
		return true;
	}
	if (dist == D[x] && x > W[x]) {
		W[x] = w;
		return true;
	}
	return false;
}
int Query(int x) {
	for (int i = 1; i <= n; ++i) D[i] = INF, W[i] = INF, vis[i] = false;
	D[centre] = 0, W[centre] = INF, vis[centre] = true, que.push(centre);
	
	while (!que.empty()) {
		int u = que.front(); que.pop();
		vis[u] = false;
		for (int k = first[u], v; v = end[k], k; k = next[k]) 
			if (relax(v, D[u] + cap[k], min(W[u], mark[k]))) 
				if (!vis[v]) {
					vis[v] = true;
					que.push(v);
				}
	}
	
	return W[x];
} 
int main() {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	n = Get(), m = Get(), centre = Get(), ty = Get(), tot = 1;
	for (int i = 1; i <= n; ++i) lev[i] = Get();
	for (int i = 1, x, y, z; i <= m; ++i) 
		x = Get(), y = Get(), z = Get(), AddEdge(x, y, z);
	SPFA(centre), build();
	int Q = Get(), lastans = 0;
	while (Q--) {
		int u = Get(), v = Get();
		if (ty) u = u ^ lastans, v = v ^ lastans;
		
		int x = v, del = dep[v] - dep[u];
		while (x != u) mark[from[x]] = mark[from[x] ^ 1] = --del, x = fa[x];
		
		lastans = Query(v);
		if (lastans == INF) lastans = dep[v] - dep[u];
		
		x = v;
		while (x != u) mark[from[x]] = mark[from[x] ^ 1] = INF, x = fa[x];
		printf("%d\n", lastans);
	}
	fclose(stdin);
	fclose(stdout);
}