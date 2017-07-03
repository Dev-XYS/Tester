#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
#define gm 100005
using namespace std;
typedef long long ll;
int n,m,s,q,tp;
int p[gm];
struct e
{
	int t,c;
	e *n;
	e(int t,e *n,int c):t(t),c(c),n(n){}
}*f[gm];
ll dis[gm];
bool inq[gm];
void spfa()
{
	memset(dis,0x7f,sizeof dis); dis[s]=0;
	queue<int> q; q.push(s);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		inq[x]=0;
		for(e *i=f[x];i;i=i->n)
		{
			if(dis[x]+i->c<dis[i->t])
			{
				dis[i->t]=dis[x]+i->c;
				if(!inq[i->t])
				{
					inq[i->t]=1;
					q.push(i->t);
				}
			}
		}
	}
}
namespace tree
{
	typedef ::e global_edge;
	global_edge** g=::f;
	struct e
	{
		int t;
		e *n;
		e(int t,e *n):t(t),n(n){}
	}*f[gm],*r[gm];
	int fa[gm][17],dep[gm],low[gm][17];
	int w,ord[gm]; bool used[gm];
	struct cmp{inline bool operator()(int a,int b){return dis[a]<dis[b];}};
	int LCA(int a,int b)
	{
		if(dep[a]<dep[b]) swap(a,b);
		int x=dep[a]-dep[b],cnt=0;
		while(x)
		{
			if(x&1) a=fa[a][cnt];
			x>>=1; ++cnt;
		}
		if(a==b) return a;
		for(int i=w;~i;--i)
		if(fa[a][i]!=fa[b][i])
		{
			a=fa[a][i];
			b=fa[b][i];
		}
		return *fa[a];
	}
	int get(int a,int b)
	{
		if(dep[a]<dep[b]) swap(a,b);
		int x=dep[a]-dep[b],cnt=0;
		int res=0x7fffffff;
		while(x)
		{
			if(x&1)
			{
				res=min(res,low[a][cnt]);
				a=fa[a][cnt];
			}
			x>>=1; ++cnt;
		}
		return min(res,*low[b]);
	}
	int solve(int a,int b)
	{
		if(dep[a]<dep[b]) swap(a,b);
		int res=dep[a]-dep[b];
		for(int i=w;~i;--i)
		{
			if(low[a][i]>dep[b])
			{
				res-=1<<i;
				a=fa[a][i];
			}
		}
		return res;
	}
	void build()
	{
		w=log2(n); memset(low,0x7f,sizeof low);
		for(int i=1;i<=n;++i)
		{
			ord[i]=i;
			for(global_edge* j=g[i];j;j=j->n)
			{
				if(dis[i]+j->c==dis[j->t])
				{
					f[i]=new e(j->t,f[i]);
					r[j->t]=new e(i,r[j->t]);
				}
			}
		}
		int c=s; used[s]=1; int cnt=n-1;
		dep[s]=1;
		while(cnt)
		{
			int x=0,minn=0x7fffffff;
			for(e *i=f[c];i;i=i->n)
			{
				if(!used[i->t]&&p[i->t]<minn)
				{
					x=i->t;
					minn=p[i->t];
				}
			}
			if(x)
			{
				*fa[x]=c; dep[x]=dep[c]+1;
				used[x]=1; c=x; --cnt;
			}
			else c=*fa[c];
		}
		sort(ord+1,ord+n+1,cmp());
		for(int i=1;i<=w;++i)
		{
			for(int j=1;j<=n;++j)
			fa[j][i]=fa[fa[j][i-1]][i-1];
		}
		for(int i=1;i<=n;++i)
		{
			int x=ord[i];
			*low[x]=dep[x];
			for(e *j=r[x];j;j=j->n)
			{
				if(j->t==*fa[x]) continue;
				*low[x]=min(*low[x],get(j->t,LCA(x,j->t)));
			}
			for(int i=1;i<=w;++i)
			low[x][i]=min(low[x][i-1],low[fa[x][i-1]][i-1]);
		}
	}
}
int ans=0;
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&s,&tp);
	for(int i=1;i<=n;++i) scanf("%d",p+i);
	for(int i=1;i<=m;++i)
	{
		int u,v,l; scanf("%d%d%d",&u,&v,&l);
		f[u]=new e(v,f[u],l); f[v]=new e(u,f[v],l);
	}
	spfa(); tree::build(); scanf("%d",&q);
	for(int i=1;i<=q;++i)
	{
		int u,v; scanf("%d%d",&u,&v);
		if(tp) u^=ans,v^=ans;
		printf("%d\n",ans=tree::solve(u,v));
	}
	return 0;
}
