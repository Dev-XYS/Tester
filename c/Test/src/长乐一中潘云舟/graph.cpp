#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
using namespace std;

typedef long long s64;
typedef long double r64;

inline s64 getint()
{
	static char c;
	while ((c = getchar()) < '0' || c > '9');

	s64 res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res;
}

const int MaxN = 105;
const int MaxM = 2005;

int n, m;
s64 p;

inline s64 add(s64 a, const s64 &b)
{
	a += b;
	return a >= p ? a - p : a;
}
inline s64 dec(s64 a, const s64 &b)
{
	a -= b;
	return a < 0 ? a + p : a;
}

inline s64 modmul(s64 a, const s64 &b)
{
/*	s64 res = 0;
	for (s64 i = b; i; i >>= 1)
	{
		if (i & 1)
			res = add(res, a);
		a = add(a, a);
	}
	return res;*/
	return (a * b - (s64)(((r64)a * b + 0.5) / (r64)p) * p + p) % p;
}

inline s64 modpow(s64 a, const s64 &n)
{
	s64 res = 1;
	for (s64 i = n; i; i >>= 1)
	{
		if (i & 1)
			res = modmul(res, a);
		a = modmul(a, a);
	}
	return res;
}

struct edge
{
	int u, v;
	s64 a, b;
};
edge allE[MaxM];

struct halfEdge
{
	int v, k;
	s64 c;
	halfEdge *next;
};
halfEdge adj_pool[MaxM * 2], *adj_tail = adj_pool;
halfEdge *adj[MaxN];

inline void addEdge(int u, int v, int k, s64 c)
{
	adj_tail->v = v, adj_tail->k = k, adj_tail->c = c;
	adj_tail->next = adj[u], adj[u] = adj_tail++;
}

inline halfEdge *oppo(const halfEdge *e)
{
	return adj_pool + ((e - adj_pool) ^ 1);
}

int dfs_clock = 0;
int dfn[MaxN];

halfEdge *faE[MaxN];

int nR = 0;
s64 f[MaxM][MaxM];

inline void add(const halfEdge *e)
{
	s64 c = e->c;
	int k = e->k;
	s64 a = modmul(c, allE[k].a);
	s64 b = modmul(c, allE[k].b);
	f[nR][k + 0] = add(f[nR][k + 0], b);
	f[nR][m + 1] = add(f[nR][m + 1], a);
}

void dfs(const int &u, const int &prev)
{
	dfn[u] = ++dfs_clock;

	for (halfEdge *e = adj[u]; e; e = e->next)
	{
		if (e->v == prev)
			continue;

		if (!dfn[e->v])
		{
			faE[e->v] = oppo(e);
			dfs(e->v, u);
		}
		else if (dfn[e->v] < dfn[u])
		{
			++nR;
			for (int v = u; v != e->v; v = faE[v]->v)
				add(faE[v]);
			add(oppo(e));
		}
	}
}

inline void eliminate()
{
	for (int i = 1; i <= m; ++i)
	{
		int r = i;
		while (r <= nR && !f[r][i])
			++r;

		s64 x = modpow(f[r][i], p - 2);
		for (int j = i; j <= m + 1; ++j)
		{
			swap(f[r][j], f[i][j]);
			f[i][j] = modmul(f[i][j], x);
		}

		for (int j = 1; j <= nR; ++j)
		{
			if (i == j || !(x = f[j][i]))
				continue;
			for (int k = 1; k <= m + 1; ++k)
				f[j][k] = dec(f[j][k], modmul(f[i][k], x));
		}
	}
}

int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);

	cin >> n >> m >> p;
	for (int i = 1; i <= m; ++i)
	{
		allE[i].u = getint(), allE[i].v = getint();
		allE[i].a = getint(), allE[i].b = getint();
		addEdge(allE[i].u, allE[i].v, i, 0 + 1);
		addEdge(allE[i].v, allE[i].u, i, p - 1);
	}

	nR = n;
	for (int u = 1; u <= n; ++u)
		for (halfEdge *e = adj[u]; e; e = e->next)
			f[u][e->k] = e->c;

	dfs(1, 0);

	static int g[MaxM][MaxM];
	for (int i = 1; i <= nR; ++i)
		for (int j = 1; j <= m + 1; ++j)
			g[i][j] = f[i][j];

	eliminate();

	for (int i = 1; i <= m; ++i)
		cout << f[i][m + 1] << endl;

	fclose(stdin);
	fclose(stdout);
	return 0;
}