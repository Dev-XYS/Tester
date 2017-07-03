#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 100005;
int n, m, Q, S, type, ans, p[MAXN], vis[MAXN];
long long dis[MAXN];
struct edge { int v, w; };
vector<edge> g[MAXN], mg[MAXN];

#define fi first
#define se second
#define MP make_pair
priority_queue< pair<long long, int> >q;
inline void Dijkstra() {
	for(int i = 1; i <= n; ++i) dis[i] = 10000000000000000LL;
	dis[S] = 0;
	q.push(MP(-dis[S], S));
	while(!q.empty()) {
		int u = q.top().se; q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = 0; i < g[u].size(); ++i) {
			edge e = g[u][i];
			if(dis[e.v] > dis[u] + e.w) {
				dis[e.v] = dis[u] + e.w;
				q.push(MP(-dis[e.v], e.v));
			}
		}
	}
	
	for(int u = 1; u <= n; ++u)
	for(int i = 0; i < g[u].size(); ++i) {
		edge e = g[u][i];
		if(dis[e.v] == dis[u] + e.w)
			mg[u].push_back((edge) { e.v, p[e.v] });
	}
}

int pa[MAXN], dep[MAXN], dfn[MAXN], rev[MAXN], idx;
inline bool cmp(edge A, edge B) { return A.w < B.w; }
int cnt[MAXN], st[MAXN], top;
inline void bfs() {
	pa[S] = S; dep[S] = 1; st[++top] = S;
	while(top) {
		int u = st[top];
		if(!cnt[u]) rev[dfn[u] = ++idx] = u;
		if(cnt[u] >= mg[u].size()) --top;
		else {
			edge e = mg[u][cnt[u]++];
			if(dfn[e.v]) continue;
			dep[e.v] = dep[pa[e.v] = u] + 1;
			st[++top] = e.v;
		}
	}
}

int F[MAXN], idom[MAXN], sdom[MAXN], best[MAXN];
inline int f(int u) {
	if(F[u] == u) return u;
	int anc = f(F[u]);
	if(dfn[best[anc]] < dfn[best[u]]) best[u] = best[anc];
	return F[u] = anc;
}

vector<int> rg[MAXN], sg[MAXN];
inline void Build() {
	for(int i = 1; i <= n; ++i) {
		best[i] = sdom[i] = F[i] = i;
	}
	for(int u = 1; u <= n; ++u)
	for(int i = 0; i < mg[u].size(); ++i) {
		edge e = mg[u][i];
		rg[e.v].push_back(u);
	}
	
	for(int u, v, i = n; i; --i) {
		vis[u = rev[i]] = 1;
		for(int j = 0; j < sg[u].size(); ++j) {
			v = sg[u][j];
			if(sdom[v] == best[f(v)]) idom[v] = sdom[v], sdom[v] = 0;
		}
		
		for(int j = 0; j < rg[u].size(); ++j) {
			if(!dfn[v = rg[u][j]]) continue;
			if(dfn[best[f(v)]] < dfn[sdom[u]]) sdom[u] = best[f(v)];
		}
		
		F[f(u)] = pa[u];
		sg[sdom[u]].push_back(u);
	}
	
	for(int u = 1; u <= n; ++u) if(sdom[u]) idom[u] = idom[sdom[u]];
}

int fa[MAXN][20];
inline int Query(int u, int v) {
	for(int k = 18; k >= 0; --k) if(dep[fa[v][k]] >= dep[u]) v = fa[v][k];
	return dep[v] - dep[u];
}
int main() {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	
	scanf("%d%d%d%d", &n, &m, &S, &type);
	for(int i = 1; i <= n; ++i) scanf("%d", p + i);
	for(int u, v, w, i = 1; i <= m; ++i) {
		scanf("%d%d%d", &u, &v, &w);
		g[u].push_back((edge) { v, w });
		g[v].push_back((edge) { u, w });
	}
	
	Dijkstra();
	for(int u = 1; u <= n; ++u)
		sort(mg[u].begin(), mg[u].end(), cmp);
	bfs();
	
	Build();
	
	for(int u, i = 1; i <= n; ++i) {
		u = rev[i];
		fa[u][0] = idom[u];
		for(int k = 0; k < 18; ++k) fa[u][k+1] = fa[fa[u][k]][k];
	}
	
	scanf("%d", &Q);
	for(int u, v, t = 1; t <= Q; ++t) {
		scanf("%d%d", &u, &v);
		if(type) u ^= ans, v ^= ans;
		printf("%d\n", ans = Query(u, v));
	}
	return 0;
}
