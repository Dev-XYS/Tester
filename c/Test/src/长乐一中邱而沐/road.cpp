#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 400010
using namespace std;
typedef long long LL;

queue < int > que;
int n, m, rt, ty;
int p[N];
int depth[N];
LL dist[N];
int vist[N];
int f[N][22], tag[N][22];
int ord[N];
int cmp(const int &a, const int &b) { return depth[a] < depth[b]; }

struct node
{
	int to, v, bo;
	node(){}
	node(int _to, int _v, int _bo) { to = _to, v = _v, bo = _bo; }
	bool operator < (node b) const
	{
		return p[to] < p[b.to];
	}
};

vector < node > g[N];

inline int Get()
{
	char c;
	while(c = getchar(), c < '0' || '9' < c);
	int s = c - '0';
	while(c = getchar(), '0' <= c && c <= '9')
		s = s * 10 + c - '0';
	return s;
}

inline void spfa()
{
	memset(dist, 63, sizeof(dist));
	dist[rt] = 0;
	que.push(rt);
	while(!que.empty())
	{
		int u = que.front();
		que.pop();
		vist[u] = 0;
		for(int i=0, L=g[u].size(); i<L; ++i)
		{
			int v = g[u][i].to;
			LL tmp;
			if((tmp = dist[u] + g[u][i].v) < dist[v])
			{
				dist[v] = tmp;
				if(!vist[v])
				{
					que.push(v);
					vist[v] = 1;
				}
			}
		}
	}
}

void dfs(int u, int fa)
{
	depth[u] = depth[fa] + 1;
	f[u][0] = fa;
	for(int i=1; i<=20; ++i) f[u][i] = f[f[u][i-1]][i-1];
	for(int i=0, L=g[u].size(); i<L; ++i)
	{
		int v = g[u][i].to;
		if(!f[v][0] && dist[u] + g[u][i].v == dist[v])
		{
			g[u][i].bo = 1;
			for(int j=0, Len=g[v].size(); j<Len; ++j)
			if(g[v][j].to == u)
			{
				g[v][j].bo = 1;
				break;
			}
			
			dfs(v, u);
		}
	}
}

inline int Jump(int u)
{
	int res = 0;
	for(int i=20; i>=0; --i)
		if(!tag[u][i]) u = f[u][i], res += (1 << i);
	return res;
}

int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	
	scanf("%d%d%d%d", &n, &m, &rt, &ty);
	for(int i=1; i<=n; ++i) p[i] = Get();
		
	for(int i=1; i<=m; ++i)
	{
		int x = Get(), y = Get(), z = Get();
		g[x].push_back(node(y, z, 0));
		g[y].push_back(node(x, z, 0));
	}
	
	spfa();
	
	for(int i=1; i<=n; ++i)
		sort(g[i].begin(), g[i].end());
	
	dfs(rt, 0);
	
	//非树边
	for(int u=1; u<=n; ++u)
	for(int j=0, L=g[u].size(); j<L; ++j)
	{
		int v = g[u][j].to;
		if(!g[u][j].bo && dist[u] + g[u][j].v == dist[v]) tag[v][0] = 1;
	}
	
	// tag
	tag[rt][0] = 1;       // 防止跳到根节点上面
	for(int i=1; i<=n; ++i) ord[i] = i;
	sort(ord + 1, ord + n + 1, cmp);
	for(int i=1; i<=n; ++i)
	{
		int u = ord[i];
		for(int j=1; j<=20; ++j)
			tag[u][j] = (tag[u][j-1] | tag[f[u][j-1]][j-1]);
	}
		
	// query
	int q, ans = 0;
	scanf("%d", &q);
	while(q--)
	{
		int u = Get(), v = Get();
		if(ty) u ^= ans, v ^= ans;
		ans = depth[v] - depth[u] - Jump(v);
		if(ans < 0) ans = 0;
		printf("%d\n", ans);
	}
}