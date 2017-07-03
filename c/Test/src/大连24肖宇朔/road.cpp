#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

#define INFL 10000000000000000LL

typedef long long ll;

using namespace std;

struct vertex
{
	int first, p, fa, fae;
	ll dis;
	bool updated, considered, vis;
}V[100010];

struct edge
{
	int endp, next, l;
	bool ing, highway, del;
}E[400010];

struct raw_edge
{
	int endp, p, l;
	raw_edge(int _endp, int _p, int _l) : endp(_endp), p(_p), l(_l) { }
};

struct dij_node
{
	int u;
	ll dis;
	dij_node(int _u, ll _dis) : u(_u), dis(_dis) { }
};

int n, m, s, ty, ec = 2, q, chain[100010], cl;
vector<raw_edge> R[100010];

inline void add_edge(int u, int v, int l)
{
	E[ec].next = V[u].first;
	V[u].first = ec;
	E[ec].endp = v;
	E[ec].l = l;
	ec++;
}

void init_single_source()
{
	for (int i = 1; i <= n; i++)
	{
		V[i].dis = INFL;
	}
	V[s].dis = 0;
}

inline bool operator < (const dij_node &x, const dij_node &y)
{
	return x.dis < y.dis;
}

void dijkstra()
{
	init_single_source();
	priority_queue<dij_node> Q;
	Q.push(dij_node(s, 0));
	while (!Q.empty())
	{
		dij_node u = Q.top();
		Q.pop();
		if (V[u.u].updated == true)
		{
			continue;
		}
		V[u.u].updated = true;
		for (int cur = V[u.u].first; cur != 0; cur = E[cur].next)
		{
			ll newdis = V[u.u].dis + E[cur].l;
			if (newdis < V[E[cur].endp].dis)
			{
				V[E[cur].endp].dis = newdis;
				Q.push(dij_node(E[cur].endp, newdis));
			}
		}
	}
}

void build_graph()
{
	for (int i = 1; i <= n; i++)
	{
		for (int cur = V[i].first; cur != 0; cur = E[cur].next)
		{
			if (V[i].dis + E[cur].l == V[E[cur].endp].dis)
			{
				E[cur].ing = true;
				//printf("choose edge : %d -> %d\n", i, E[cur].endp);
			}
		}
	}
}

void dfs_tree(int u, int fa, int fae)
{
	V[u].considered = true;
	V[u].fa = fa;
	V[u].fae = fae;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].ing == true && V[E[cur].endp].considered == false)
		{
			//printf("highway edge : %d -> %d\n", u, E[cur].endp);
			E[cur].highway = true;
			dfs_tree(E[cur].endp, u, cur);
		}
	}
}

void get_chain(int u, int v)
{
	static int _chain[100010];
	cl = 0;
	while (v != u)
	{
		_chain[cl++] = v;
		v = V[v].fa;
	}
	_chain[cl] = v;
	for (int i = 0; i <= cl; i++)
	{
		chain[i] = _chain[cl - i];
	}
}

void mark(int u, int w, bool value)
{
	while (w != u)
	{
		E[V[w].fae].del = value;
		w = V[w].fa;
	}
}

void clear_vis()
{
	for (int i = 1; i <= n; i++)
	{
		V[i].vis = false;
	}
}

bool dfs_reach(int u, int tar)
{
	//printf("dfs_reach : %d\n", u);
	if (u == tar)
	{
		return true;
	}
	V[u].vis = true;
	for (int cur = V[u].first; cur != 0; cur = E[cur].next)
	{
		if (E[cur].ing == true && E[cur].del == false && V[E[cur].endp].vis == false)
		{
			if (dfs_reach(E[cur].endp, tar) == true)
			{
				return true;
			}
		}
	}
	return false;
}

inline bool _raw_edge_p_cmp_(const raw_edge &x, const raw_edge &y)
{
	return x.p > y.p;
}

int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	scanf("%d%d%d%d", &n, &m, &s, &ty);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &V[i].p);
	}
	int u, v, l;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d%d", &u, &v, &l);
		R[u].push_back(raw_edge(v, V[v].p, l));
		R[v].push_back(raw_edge(u, V[u].p, l));
	}
	for (int i = 1; i <= n; i++)
	{
		sort(R[i].begin(), R[i].end(), _raw_edge_p_cmp_);
		for (int j = 0; j < (int)R[i].size(); j++)
		{
			add_edge(i, R[i][j].endp, R[i][j].l);
		}
	}
	dijkstra();
	build_graph();
	dfs_tree(s, 0, 0);
	int lastans = 0;
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &u, &v);
		if (ty == 1)
		{
			u ^= lastans;
			v ^= lastans;
		}
		get_chain(u, v);
		//for (int i = 0; i <= cl; i++) printf("%d ", chain[i]); printf("\n");
		int l = 0, r = cl;
		while (l < r)
		{//printf("l = %d, r = %d\n", l, r);
			int mid = (l + r + 1) >> 1;
			mark(u, chain[mid], true);
			clear_vis();
			if (dfs_reach(s, v) == true)
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
			mark(u, chain[mid], false);
		}
		printf("%d\n", lastans = l);
	}
	return 0;
}
