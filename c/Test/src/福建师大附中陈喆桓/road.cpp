#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define l(a) son[a][0]
#define r(a) son[a][1]
#define MS 19
#define MN 100005
#define MM 9000005
#define ll long long
using namespace std;
struct edge{int to; ll wt;};
struct meg{int x,y,l,r;}d[MN<<1];
struct hp{int x,y,z;}c[MN<<1];
vector <edge> e[MN];
ll dis[MN];
int q[MN*8],lev[MN],st[MN][2];
int fa[MS][MN],dep[MN],dfbg[MN],dfed[MN];
int son[MM][2],t[MM],tg[MM],rt[MN];
int dfn,hd,tl,pin,din,n,m,S,tp,que,typ,ans;
bool u[MN],inq[MN];

inline int read()
{
	int n=0,f=1; char c=getchar();
	while (c<'0' || c>'9') {if(c=='-')f=-1; c=getchar();}
	while (c>='0' && c<='9') {n=n*10+c-'0'; c=getchar();}
	return n*f;
}

inline void ins(int x,int y,int z) {e[x].push_back((edge){y,z});}

void dfs(int x,int fat,int depth)
{
	fa[0][x]=fat; u[x]=true; dfbg[x]=++dfn; dep[x]=depth;
	register int i;
	for (i=0;i<e[x].size();++i)
		if (!u[e[x][i].to]&&dis[x]+e[x][i].wt==dis[e[x][i].to]) dfs(e[x][i].to,x,depth+1);
	dfed[x]=dfn;
}

void spfa()
{
	memset(dis,127,sizeof(dis));
	register int i,x;
	for (dis[q[hd=tl=1]=S]=0;hd<=tl;inq[x]=false,++hd)
		for (x=q[hd],i=0;i<e[x].size();++i)
			if (dis[x]+e[x][i].wt<dis[e[x][i].to])
			{
				dis[e[x][i].to]=dis[x]+e[x][i].wt;
				if (!inq[e[x][i].to]) inq[e[x][i].to]=true,q[++tl]=e[x][i].to;
			}
}

inline void copi(int ox,int& x) {x=++pin; l(x)=l(ox); r(x)=r(ox); t[x]=t[ox]; tg[x]=tg[ox];}
inline void cg(int x,int L,int R) {t[x]=R-L+1; tg[x]=1;}
inline void down(int x,int L,int R)
{
	if (tg[x])
	{
		copi(l(x),l(x)); copi(r(x),r(x));
		int mid=L+R>>1;
		cg(l(x),L,mid); cg(r(x),mid+1,R);
		tg[x]=0;
	}
}
int getsum(int x,int L,int R,int ql,int qr)
{
	if (ql==L&&qr==R) return t[x];
	down(x,L,R);
	int mid=L+R>>1;
	if (qr<=mid) return getsum(l(x),L,mid,ql,qr);
	else if (ql>mid) return getsum(r(x),mid+1,R,ql,qr);
	else return getsum(l(x),L,mid,ql,mid)+getsum(r(x),mid+1,R,mid+1,qr);
}
void getcg(int ox,int& x,int L,int R,int ql,int qr)
{
	copi(ox,x);
	if (ql==L&&qr==R) {cg(x,L,R); return;}
	down(x,L,R);
	int mid=L+R>>1;
	if (qr<=mid) getcg(l(ox),l(x),L,mid,ql,qr);
	else if (ql>mid) getcg(r(ox),r(x),mid+1,R,ql,qr);
	else getcg(l(ox),l(x),L,mid,ql,mid),getcg(r(ox),r(x),mid+1,R,mid+1,qr);
	t[x]=t[l(x)]+t[r(x)];
}

bool cmp1(const edge& a,const edge& b) {return lev[a.to]<lev[b.to];}
bool cmp2(const meg& a,const meg& b)
{
	if (a.x!=b.x) return a.x<b.x;
	if (a.y!=b.y) return a.y>b.y;
	return a.l<b.l;
}

int lca(int x,int y)
{
	register int i,k;
	if (dep[x]<dep[y]) swap(x,y);
	for (k=dep[x]-dep[y],i=0;k;k>>=1,++i) if (k&1) x=fa[i][x];
	if (x==y) return x;
	for (i=MS-1;i>=0;--i) if (fa[i][x]!=fa[i][y]) x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}

int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	register int i,j,la,x,y,L,R;
	n=read(); m=read(); S=read(); typ=read();
	for (i=1;i<=n;++i) lev[i]=read();
	for (i=1;i<=m;++i)
	{
		c[i].x=read(); c[i].y=read(); c[i].z=read();
		ins(c[i].x,c[i].y,c[i].z); ins(c[i].y,c[i].x,c[i].z);
	}
	for (i=1;i<=n;++i) sort(e[i].begin(),e[i].end(),cmp1);
	spfa(); dfs(S,0,1);
	for (i=1;i<MS;++i)
		for (j=1;j<=n;++j) fa[i][j]=fa[i-1][fa[i-1][j]];
	for (i=1;i<=m;++i)
	{
		if (dis[c[i].x]>dis[c[i].y]) swap(c[i].x,c[i].y);
		if (fa[0][c[i].y]==c[i].x) continue;
		if (dis[c[i].x]+c[i].z!=dis[c[i].y]) continue;
		la=lca(c[i].x,c[i].y);
		d[++din]=(meg){dfbg[c[i].y],dfed[c[i].y],dep[la],dep[fa[0][c[i].y]]}; 
	}
	sort(d+1,d+din+1,cmp2);
//	for (i=1;i<=din;++i) printf("%d %d %d %d\n",d[i].x,d[i].y,d[i].l,d[i].r);	
	for (i=j=1;i<=n;++i)
	{
		for (;tp&&i>st[tp][0];--tp) rt[i]=st[tp][1];
		for (;j<=din&&i==d[j].x;++j) ++tp,st[tp][0]=d[j].y,st[tp][1]=rt[i],getcg(rt[i],rt[i],1,n,d[j].l,d[j].r);
	}
	que=read(); ans=0;
	while (que--)
	{	
//	puts("sb");	
		x=read(); y=read();
		if (typ) x^=ans,y^=ans;
		L=0; R=dep[y]-dep[x];
//		printf("%d %d\n",dep[x],dep[y]);		
		while (L<R)
		{
//			printf("%d %d\n",L,R);
			int mid=L+R+1>>1;
			if (getsum(rt[dfbg[y]],1,n,dep[x],dep[x]+mid-1)==mid) L=mid; else R=mid-1;
		}
		ans=L;
		printf("%d\n",ans);
	}
}
