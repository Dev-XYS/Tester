#include <bits/stdc++.h>
#define M 400010

using namespace std;

typedef long long ll;

int n, m, s, ty, q, lans = 0, H[M], N[M], G[M], P[M], Cnt = 0;

bool vis[M];

ll V[M], Dis[M];

struct two {int x, v; two(){} two(ll _1, ll _2) {x = _1, v = _2;}};

bool cmp(two A, two B) {return P[A.x] < P[B.x];}

struct Tree
{
	vector <two> cad[M];
	
	int cadt[M], Dep[M], Ans[M], Val[M], F[M];
	
	bool vis[M];
	
	void init() {memset(cad, 0, sizeof cad), memset(cadt, 0, sizeof cadt), memset(vis, 0, sizeof vis);}

	void DFS0(int x, int dep = 1)
	{
		vis[x] = 1, Dep[x] = dep;
		for(int i = cadt[x]; i < cad[x].size(); i++) if(!vis[cad[x][i].x])
			cadt[x] = i + 1, cad[x][i].v = 1, F[cad[x][i].x] = x, DFS0(cad[x][i].x, dep + 1);
	}
	
	int DFS1(int x)
	{
		if(Ans[x] != -1) return Ans[x];
		int& ans = Ans[x];
		ans = 0;
		for(int i = 0; i < cad[x].size(); i++) ans = max(ans, min((cad[x][i].v ? Val[cad[x][i].x] : (int) 2e9), DFS1(cad[x][i].x)));
		return ans;
	}
 
	int solve(int x, int y)
	{
		memset(Ans, -1, sizeof(int) * (n + 5)), memset(Val, 63, sizeof(int) * (n + 5)), Ans[y] = 2e9;
		for(int i = y; i != x; i = F[i]) Val[i] = Dep[i];
		int tmp = DFS1(s);
		if(tmp >= 1e9) return Dep[y] - Dep[x];
		return tmp - Dep[x] - 1;
	}
}tree;

void addedge(int x, int y, int z) {G[++Cnt] = y, N[Cnt] = H[x], H[x] = Cnt, V[Cnt] = z;}

void SPFA()
{
	static ll Dl[M + 10];
	static bool vis[M];
	memset(Dis, 63, sizeof Dis), Dis[s] = 0;
	memset(vis, 0, sizeof vis), vis[s] = 1, Dl[1] = s;
	for(int t = 1, w = 1; (t + 1) % M != w; ) {
		int W = Dl[w];
		w = (w + 1) % M;
		vis[W] = 0;
		for(int T = H[W]; T; T = N[T]) if(Dis[G[T]] > Dis[W] + V[T]) {
			Dis[G[T]] = Dis[W] + V[T];
			if(!vis[G[T]]) t = (t + 1) % M, Dl[t] = G[T];
		}
	}
}

int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &s, &ty), tree.init();
	for(int i = 1; i <= n; i++) scanf("%d", &P[i]);
	for(int i = 1; i <= m; i++) {
		int x, y, v;
		scanf("%d%d%d", &x, &y, &v);
		addedge(x, y, v), addedge(y, x, v);
	}
	SPFA();
	for(int i = 1; i <= n; i++)
		for(int T = H[i]; T; T = N[T]) if(Dis[G[T]] == Dis[i] + V[T]) tree.cad[i].push_back(two(G[T], 0));
	for(int i = 1; i <= n; i++) sort(tree.cad[i].begin(), tree.cad[i].end(), cmp), tree.cadt[i] = 0;
	tree.DFS0(s);
	for(scanf("%d", &q); q--;) {
		int x, y, ans;
		scanf("%d%d", &x, &y);
		printf("%d\n", ans = tree.solve(x ^= lans, y ^= lans)), lans ^= ans * ty;
	}
	return 0;
}
