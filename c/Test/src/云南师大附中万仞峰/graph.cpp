#include <cstdio>
#include <vector>
long long MOD;
int N, M, f[101], head[101], next[199], to[199], id[199], rev[199], E, q[101], fa[101], dep[101], fe[101], fr[101], POS[100];
int F(int x)
{
	return f[x] == x ? x : f[x] = F(f[x]);
}
struct edge
{
	int id, u, v;
	long long a, b;
}
p[2001];
long long w[2001][100], g[100][100], res[100], O[2000];
std::vector < int > Inc[101], Dec[101];
long long MULTI(long long a, long long b)
{
	long long r = 0;
	for (; b; b >>= 1)
	{
		if (b & 1)
			if ((r += a) >= MOD)
				r -= MOD;
		if ((a += a) >= MOD)
			a -= MOD;
	}
	return r;
}
long long POWER(long long a, long long b)
{
	long long r = 1;
	for (; b; b >>= 1)
	{
		if (b & 1)
			r = MULTI(r, a);
		a = MULTI(a, a);
	}
	return r;
}
inline void CT(long long &x)
{
	if (x < 0)
		x += MOD;
	else if (x >= MOD)
		x -= MOD;
}
int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	scanf("%d%d%lld", &N, &M, &MOD);
	for (int i = 1; i <= N; i++)
		f[i] = i;
	for (int i = 1, L = 0, R = M; i <= M; i++)
	{
		int u, v;
		long long a, b;
		scanf("%d%d%lld%lld", &u, &v, &a, &b);
		int fu = F(u), fv = F(v);
		if (fu == fv)
			p[R--] = (edge) { i, u, v, a, b };
		else
		{
			f[fu] = fv;
			p[++L] = (edge) { i, u, v, a, b };
		}
	}
	for (int i = 1; i <= M; i++)
	{
		Inc[p[i].u].push_back(i);
		Dec[p[i].v].push_back(i);
	}
	for (int i = 1; i < N; i++)
	{
		next[++E] = head[p[i].u], to[E] = p[i].v, id[E] = i, rev[E] = 1, head[p[i].u] = E;
		next[++E] = head[p[i].v], to[E] = p[i].u, id[E] = i, rev[E] = 0, head[p[i].v] = E;
	}
	int H = 0, T = 1, u;
	q[1] = 1;
	while (H < T)
		for (int e = head[u = q[++H]]; e; e = next[e])
			if (to[e] != fa[u])
			{
				fa[q[++T] = to[e]] = u;
				dep[to[e]] = dep[u] + 1;
				fe[to[e]] = id[e];
				fr[to[e]] = rev[e];
			}
	for (int i = N; i <= M; i++)
	{
		// p[i].c * p[i].b = sum_{e on way(v -> u)} (正走 ? -e.b : e.b) * e.c + \sum_{e on way(v -> u)} (正走 ? e.a : -e.a) + p[i].a
		int u = p[i].u, v = p[i].v;
		while (dep[u] > dep[v])
		{
			CT(w[i][fe[u]] += fr[u] ? -p[fe[u]].b : p[fe[u]].b);
			CT(w[i][0] += fr[u] ? p[fe[u]].a : -p[fe[u]].a);
			u = fa[u];
		}
		while (dep[u] < dep[v])
		{
			CT(w[i][fe[v]] += fr[v] ? p[fe[v]].b : -p[fe[v]].b);
			CT(w[i][0] += fr[v] ? -p[fe[v]].a : p[fe[v]].a);
			v = fa[v];
		}
		while (u != v)
		{
			CT(w[i][fe[u]] += fr[u] ? -p[fe[u]].b : p[fe[u]].b);
			CT(w[i][0] += fr[u] ? p[fe[u]].a : -p[fe[u]].a);
			u = fa[u];
			CT(w[i][fe[v]] += fr[v] ? p[fe[v]].b : -p[fe[v]].b);
			CT(w[i][0] += fr[v] ? -p[fe[v]].a : p[fe[v]].a);
			v = fa[v];
		}
		CT(w[i][0] += p[i].a);
		long long inv = POWER(p[i].b, MOD - 2);
		for (int j = 0; j < N; j++)
			w[i][j] = MULTI(w[i][j], inv);
	}
	for (int i = 1; i < N; i++)
	{
		for (std::vector < int >::iterator j = Inc[i].begin(); j != Inc[i].end(); j++)
			if (*j < N)
				CT(++g[i][*j]);
			else
			{
				long long *my_w = w[*j];
				CT(g[i][0] -= my_w[0]);
				for (int k = 1; k < N; k++)
					CT(g[i][k] += my_w[k]);
			}
		for (std::vector < int >::iterator j = Dec[i].begin(); j != Dec[i].end(); j++)
			if (*j < N)
				CT(--g[i][*j]);
			else
			{
				long long *my_w = w[*j];
				CT(g[i][0] += my_w[0]);
				for (int k = 1; k < N; k++)
					CT(g[i][k] -= my_w[k]);
			}
	}
	for (int i = 1; i < N; i++)
	{
		int pos = 1;
		while (!g[i][pos])
			pos++;
		POS[i] = pos;
		for (int j = i + 1; j < N; j++)
		{
			long long W = MULTI(g[j][pos], POWER(g[i][pos], MOD - 2));
			for (int k = 0; k < N; k++)
				CT(g[j][k] -= MULTI(W, g[i][k]));
		}
	}
	for (int i = N - 1; i; i--)
	{
		long long W = g[i][0];
		for (int j = 1; j < N; j++)
			if (j != POS[i])
				CT(W -= MULTI(res[j], g[i][j]));
		res[POS[i]] = MULTI(W, POWER(g[i][POS[i]], MOD - 2));
	}
	for (int i = 1; i < N; i++)
		O[p[i].id] = res[i];
	for (int i = N; i <= M; i++)
	{
		long long W = w[i][0];
		for (int j = 1; j < N; j++)
			CT(W += MULTI(w[i][j], res[j]));
		O[p[i].id] = W;
	}
	for (int i = 1; i <= M; i++)
		printf("%lld\n", O[i]);
	return 0;
}
