#include <algorithm>
#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long s64;

/*
考虑两种情况：
1. 走到某个祖先，然后通过横叉边走到其他子树内
2. 走到某个祖先，然后通过返祖边越过u
*/

inline int getint()
{
	static char c;
	while ((c = getchar()) < '0' || c > '9');

	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

const int MaxN = 100005;
const int MaxM = 200005;
const int MaxLogN = 19;
const s64 INF = 0x3f3f3f3f3f3f3f3fll;

int n, m, sv, mask, last;
int pri[MaxN];
int eu[MaxM], ev[MaxM], ew[MaxM];

struct halfEdge
{
	int v, w, k;
	halfEdge *next;
};
halfEdge adj_pool[MaxM * 2], *adj_tail = adj_pool;
halfEdge *adj[MaxN];

inline void addEdge(const int &u, const int &v, const int &w, const int &k)
{
	adj_tail->v = v, adj_tail->w = w, adj_tail->k = k;
	adj_tail->next = adj[u], adj[u] = adj_tail++;
}

struct info
{
	int v;
	s64 l;
	info() {}
	info(const int &_v, const int &_l)
		: v(_v), l(_l) {}

	friend inline bool operator<(const info &lhs, const info &rhs)
	{
		if (lhs.l != rhs.l)
			return lhs.l > rhs.l;
		return lhs.v > rhs.v;
	}
};

int q_n;
info q[MaxM];

inline void push_heap(int v, s64 l)
{
	q[q_n++] = info(v, l);
	push_heap(q, q + q_n);
}
inline info pop_heap()
{
	info t = q[0];
	pop_heap(q, q + q_n--);
	return t;
}

s64 dist[MaxN];

inline void calc_dist()
{
	for (int u = 1; u <= n; ++u)
		dist[u] = INF;
	dist[sv] = 0;

	push_heap(sv, 0ll);
	while (q_n > 0)
	{
		info u = pop_heap();
		if (u.l != dist[u.v])
			continue;

		for (halfEdge *e = adj[u.v]; e; e = e->next)
		{
			s64 d = u.l + e->w;
			if (d < dist[e->v])
			{
				dist[e->v] = d;
				push_heap(e->v, d);
			}
		}
	}
}

int dep[MaxN];
int anc[MaxN][MaxLogN];
int val[MaxN][MaxLogN];

int dfs_clock = 0;
int dfn_l[MaxN], dfn_r[MaxN];

inline bool is_anc(const int &u, const int &v)
{
	return dfn_l[u] <= dfn_l[v] && dfn_l[v] <= dfn_r[u];
}

inline void check(int u, int v, int w)
{
	if (dist[u] + w != dist[v])
		return;
	int d = is_anc(u, v) ? dep[u] : 0;
	val[v][0] = min(val[v][0], d);
}

void dfs_init(const int &u)
{
	dfn_l[u] = ++dfs_clock;

	for (halfEdge *e = adj[u]; e; e = e->next)
	{
		dep[e->v] = dep[u] + 1;
		dfs_init(e->v);
	}

	dfn_r[u] = dfs_clock;
}

void dfs_build(const int &u)
{
	for (int i = 0; anc[u][i]; ++i)
	{
		int v = anc[u][i];
		anc[u][i + 1] = anc[v][i];
		val[u][i + 1] = min(val[u][i], val[v][i]);
	}

	for (halfEdge *e = adj[u]; e; e = e->next)
		dfs_build(e->v);
}

bool book[MaxM];
int fa[MaxN], faE[MaxN];

inline void build_tree()
{
	int now = sv, rest = n - 1;
	for (int u = 1; u <= n; ++u)
		book[u] = false;
	book[sv] = true;

	while (rest > 0)
	{
		int w = INT_MAX;
		halfEdge *p = NULL;
		for (halfEdge *e = adj[now]; e; e = e->next)
		{
			s64 l = dist[now] + e->w;
			if (l == dist[e->v] && !book[e->v] && pri[e->v] < w)
				w = pri[e->v], p = e;
		}

		if (!p)
			now = fa[now];
		else
		{
			fa[p->v] = now, faE[p->v] = p->k;
			now = p->v;
			book[now] = true, --rest;
		}
	}

	adj_tail = adj_pool;
	for (int u = 1; u <= n; ++u)
		adj[u] = NULL;
	for (int i = 1; i <= m; ++i)
		book[i] = false;
	for (int u = 1; u <= n; ++u)
		if (u != sv)
		{
			int v = anc[u][0] = fa[u];
			int k = faE[u], w = ew[k];
			addEdge(v, u, w, k), book[k] = true;
		}

	dfs_init(sv);

	for (int u = 1; u <= n; ++u)
		val[u][0] = dep[u];
	for (int i = 1; i <= m; ++i)
		if (!book[i])
		{
			int u = eu[i], v = ev[i], w = ew[i];
			check(u, v, w);
			check(v, u, w);
		}

	dfs_build(sv);
}

int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);

	cin >> n >> m >> sv >> mask;
	for (int i = 0; i < 30; ++i)
		mask = mask << 1 | mask;

	for (int u = 1; u <= n; ++u)
		pri[u] = getint();
	for (int i = 1; i <= m; ++i)
	{
		int u = eu[i] = getint();
		int v = ev[i] = getint();
		int w = ew[i] = getint();
		addEdge(u, v, w, i);
		addEdge(v, u, w, i);
	}

	calc_dist();
	build_tree();

	int q = getint();
	while (q--)
	{
		int u = getint() ^ (mask & last);
		int v = getint() ^ (mask & last);
		for (int i = 16; i >= 0; --i)
			if (val[v][i] > dep[u])
				v = anc[v][i];
		printf("%d\n", last = dep[v] - dep[u]);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}