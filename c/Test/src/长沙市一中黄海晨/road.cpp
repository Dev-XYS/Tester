#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define LL long long
using namespace std;
inline int read()
{
	int t=1,sum=0;char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') t=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		sum=sum*10+ch-'0',ch=getchar();
	return t*sum;
}
const int Max=1e5+10;
int fir[Max],vis[Max],siz[Max],son[Max],dfn[Max],ed[Max],top[Max];
int bel[Max],dep[Max],a[Max],w[Max],fa[Max][17],n,m,tot,cnt,ans,S;
int le[Max],ri[Max];
LL d[Max]; vector<int> G[Max],So[Max];
struct edge
{
	int to,nxt,w;
	edge () {}
	edge (int x,int y,int z)
	{
		to=y; nxt=fir[x]; w=z;
		fir[x]=cnt;
	}
}e[Max<<2];
void add(int x,int y,int z)
{
	e[++cnt]=edge(x,y,z);
	e[++cnt]=edge(y,x,z);
}
bool cmp1(int x,int y) { return d[x]<d[y]; }
bool cmp2(int x,int y) { return a[x]<a[y]; }
void spfa()
{
	int i,x; queue<int> q;
	for(i=1;i<=n;i++) d[i]=1e18;
	d[S]=0; q.push(S);
	while(!q.empty())
	{
		x=q.front(); q.pop();
		for(i=fir[x];i;i=e[i].nxt)
			if(d[e[i].to]>d[x]+e[i].w)
			{
				d[e[i].to]=d[x]+e[i].w;
				if(!vis[e[i].to])
					q.push(e[i].to),vis[e[i].to]=1;
			}
		vis[x]=0;
	}
}
void build(int x)
{
	int i,v; vis[x]=1;
	for(i=fir[x];i;i=e[i].nxt)
	{
		v=e[i].to;
		if(d[v]==d[x]+e[i].w)
			G[x].push_back(v);	
	}
	sort(G[x].begin(),G[x].end(),cmp2);
	for(i=0;i<G[x].size();i++)
	{
		v=G[x][i];
		if(vis[v]) continue;
		So[x].push_back(v);
		build(v);
	}
}
void dfs(int x)
{
	int i,v; siz[x]=1;
	for(i=1;fa[fa[x][i-1]][i-1];i++)
		fa[x][i]=fa[fa[x][i-1]][i-1];
	for(i=0;i<So[x].size();i++)
	{
		v=So[x][i];
		if(v==fa[x][0])	continue;
		fa[v][0]=x; dep[v]=dep[x]+1;
		dfs(v);
		if(!son[x]||siz[son[x]]<siz[v])
			son[x]=v;
		siz[x]+=siz[v];
	}
}
void gao(int x,int p)
{
	dfn[x]=++tot; bel[tot]=x; top[x]=p;
	if(son[x]) gao(son[x],p);
	for(int i=0;i<So[x].size();i++)
		if(So[x][i]!=fa[x][0]&&So[x][i]!=son[x])
			gao(So[x][i],So[x][i]);
	ed[x]=tot;
}
int get_kth(int x,int k)
{
	for(int i=0;i<17;i++)
		if(k>>i&1)
			x=fa[x][i];
	return x;
}
namespace seg
{
	int mi[Max<<2];
	#define lc o<<1
	#define rc o<<1|1
	void build(int o,int l,int r)
	{
		if(l==r)
		{
			mi[o]=w[bel[l]];
			return;
		}
		int mid=l+r>>1;
		build(lc,l,mid);
		build(rc,mid+1,r);
		mi[o]=min(mi[lc],mi[rc]);
	}
	int query(int o,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R)
			return mi[o];
		int mid=l+r>>1;
		if(R<=mid) return query(lc,l,mid,L,R);
		if(L>mid) return query(rc,mid+1,r,L,R);
		return min(query(lc,l,mid,L,R),query(rc,mid+1,r,L,R));
	}
	int ask(int o,int l,int r,int L,int R,int v)
	{
		int mid=l+r>>1;
		if(L<=l&&r<=R)
		{
			if(mi[o]>v) return -1;
			if(l==r) return l;
			if(mi[rc]<=v) return ask(rc,mid+1,r,L,R,v);
			else return ask(lc,l,mid,L,R,v);
		}
		int res=-1;
		if(R>mid) res=ask(rc,mid+1,r,L,R,v);
		if(res!=-1) return res;
		if(L<=mid) return ask(lc,l,mid,L,R,v); 
	}
}
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	int i,j,x,y,z,ty;
	n=read(); m=read(); S=read(); ty=read();
	for(i=1;i<=n;i++) a[i]=read();
	for(i=1;i<=m;i++)
	{
		x=read(); y=read(); z=read();
		add(x,y,z);
	}
	spfa(); 
	memset(vis,0,sizeof vis);
	build(1); 
	dfs(1); 
	gao(1,1);
	for(i=1;i<=n;i++) a[i]=i;
	sort(a+1,a+n+1,cmp1);
	for(i=1;i<=n;i++) le[i]=n+1,ri[i]=0;
	for(i=1;i<=n;i++)
	{
		x=a[i]; 
		le[x]=min(le[x],dfn[x]);
		ri[x]=max(ri[x],dfn[x]);
		for(j=fir[x];j;j=e[j].nxt)
			if(d[e[j].to]==d[x]+e[j].w)
			{
				y=e[j].to;
				if(fa[y][0]==x)
					continue;
				le[y]=min(le[y],le[x]);
				ri[y]=max(ri[y],ri[x]);
			}
		for(y=x,j=16;~j;j--)
		{
			if(!fa[y][j]) continue;
			z=get_kth(y,(1<<j)-1);
			if(le[x]<dfn[z]||ed[z]<ri[x])
				y=fa[y][j];
		}
		w[x]=dep[y];
	}
	seg::build(1,1,n);
	m=read();
	while(m--)
	{
		y=read(); x=read();
		if(ty)
			y^=ans,x^=ans;
		int flag=0;
		while(top[x]!=top[y])
		{
			z=seg::query(1,1,n,dfn[top[x]],dfn[x]);
			if(z<=dep[y])
			{
				z=seg::ask(1,1,n,dfn[top[x]],dfn[x],dep[y]);
				flag=1;
				break;
			}
			x=fa[x][0];
		}
		if(!flag)
			z=seg::ask(1,1,n,dfn[y],dfn[x],dep[y]);
		printf("%d\n",ans=dep[bel[z]]-dep[y]);
	}
	return 0;
}
