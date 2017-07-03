#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<stack>
#include<bitset>
using namespace std;

const int N = 17;
const int maxn = 1E5 + 10;
typedef long long LL;
const LL INF = 1E16;

#define fr first
#define sc second
#define mp(a,b) (make_pair((a),(b)))

struct E{
	int to,p; LL w; E(){}
	E(int to,int p,LL w): to(to),p(p),w(w){}
	bool operator < (const E &B) const {return p < B.p;}
};

struct data{
	int Num; LL dis; data(){}
	data(int Num,LL dis): Num(Num),dis(dis){}
	bool operator < (const data &B) const {return dis > B.dis;}
};

int n,m,s,ty,p[maxn],L[maxn],f[maxn][N],g[maxn][N],fa[maxn][N];
LL dis[maxn]; bool inq[maxn],vis[maxn];

vector <E> v[maxn];
priority_queue <data> Q;

inline int getint()
{
	char ch = getchar(); int ret = 0;
	while (ch < '0' || '9' < ch) ch = getchar();
	while ('0' <= ch && ch <= '9')
		ret = ret * 10 + ch - '0',ch = getchar();
	return ret;
}

void Dijkstra()
{
	for (int i = 1; i <= n; i++) dis[i] = INF;
	dis[s] = 0; Q.push(data(s,0));
	while (!Q.empty())
	{
		data k = Q.top(); Q.pop();
		if (inq[k.Num]) continue; inq[k.Num] = 1;
		for (int i = 0; i < v[k.Num].size(); i++)
		{
			E e = v[k.Num][i];
			if (dis[e.to] > dis[k.Num] + e.w)
			{
				dis[e.to] = dis[k.Num] + e.w;
				Q.push(data(e.to,dis[e.to]));
			}
		}
	}
}

inline void Dfs(int x)
{
	vis[x] = 1; sort(v[x].begin(),v[x].end());
	for (int i = 1; i < N; i++) fa[x][i] = fa[fa[x][i-1]][i-1];
	for (int i = 0; i < v[x].size(); i++)
	{
		E e = v[x][i];
		if (vis[e.to] || dis[e.to] != dis[x] + e.w) continue;
		fa[e.to][0] = x; L[e.to] = L[x] + 1; Dfs(e.to);
	}
}

inline int LCA(int p,int q)
{
	if (L[p] < L[q]) swap(p,q);
	for (int i = N - 1; i >= 0; i--)
		if (L[p] - (1 << i) >= L[p]) p = fa[p][i];
	if (p == q) return p;
	for (int i = N - 1; i >= 0; i--)
		if (fa[p][i] != fa[q][i]) p = fa[p][i],q = fa[q][i];
	return fa[p][0];
}

inline int Check(int x,int y)
{
	int ret = g[x][0];
	for (int now = 0; y; y >>= 1,now++)
		if (y & 1) ret = min(ret,f[x][now]),x = fa[x][now];
	return ret;
}

void Pre_Work()
{
	static pair <LL,int> p[maxn];
	for (int i = 1; i <= n; i++) p[i] = mp(dis[i],i);
	sort(p + 1,p + n + 1);
	for (int i = 1; i <= n; i++)
	{
		int &cur = g[p[i].sc][0],now = p[i].sc; cur = L[now];
		for (int j = 0; j < v[now].size(); j++)
		{
			E e = v[now][j];
			if (e.to == fa[now][0] || dis[now] != dis[e.to] + e.w) continue;
			int lca = LCA(now,e.to); cur = min(cur,Check(e.to,L[e.to] - L[lca]));
		}
		f[now][0] = min(g[now][0],g[fa[now][0]][0]);
		for (int j = 1; j < N; j++)
		{
			f[now][j] = min(f[now][j-1],f[fa[now][j-1]][j-1]);
			g[now][j] = min(f[now][j-1],g[fa[now][j-1]][j-1]);
		}
	}
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
	#else
		freopen("road.in","r",stdin);
		freopen("road.out","w",stdout);
	#endif
	
	n = getint(); m = getint(); s = getint(); ty = getint();
	for (int i = 1; i <= n; i++) p[i] = getint();
	while (m--)
	{
		int x = getint(),y = getint(),w = getint();
		v[x].push_back(E(y,p[y],w)); v[y].push_back(E(x,p[x],w));
	}
	Dijkstra(); L[s] = 1; Dfs(s); Pre_Work();
	int LastAns = 0,q = getint();
	while (q--)
	{
		int x = getint(),y = getint();
		if (ty == 1) x ^= LastAns,y ^= LastAns; LastAns = L[y] - L[x];
		for (int i = N - 1; i >= 0; i--)
		{
			if (g[y][i] <= L[x]) continue;
			LastAns -= (1 << i); y = fa[y][i];
		}
		printf("%d\n",LastAns);
	}
	return 0;
}
