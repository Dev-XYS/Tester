#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define ll long long
inline int read()
{
	int x;char c;
	while((c=getchar())<'0'||c>'9');
	for(x=c-'0';(c=getchar())>='0'&&c<='9';)x=x*10+c-'0';
	return x;
}
#define MN 100000
#define MM 200000
#define N 131072
#define K 17
struct edge{int nx,t,w;}e[MM*2+5];
int p[MN+5],h[MN+5],en,dep[MN+5],q[MN+5],qn,r[MN+5],fa[K][MN+5],td[MN+5];
ll d[MN+5];
vector<int> v[MN+5];
inline void ins(int x,int y,int w)
{
	e[++en]=(edge){h[x],y,w};h[x]=en;
	e[++en]=(edge){h[y],x,w};h[y]=en;
}
struct data{ll x;int f;}t[N*2+5];
data min(const data&a,const data&b){return a.x<b.x?a:b;}
void change(int k,ll x)
{
	t[k+N]=(data){x,k};
	for(k+=N;k>>=1;)t[k]=min(t[k<<1],t[k<<1|1]);
}
void dj(int s)
{
	memset(d,40,sizeof(d));
	memset(t,40,sizeof(t));
	change(s,d[s]=0);
	while(t[1].x<t[0].x)
	{
		int x=t[1].f,i;
		for(i=h[x];i;i=e[i].nx)if(d[x]+e[i].w<d[e[i].t])
			change(e[i].t,d[e[i].t]=d[x]+e[i].w);
		change(x,t[0].x);
	}
}
bool cmp(int a,int b){return p[a]<p[b];}
void dfs(int x)
{
	++dep[x];
	for(int i=h[x];i;i=e[i].nx)
		if(d[x]+e[i].w==d[e[i].t])v[x].push_back(e[i].t);
	sort(v[x].begin(),v[x].end(),cmp);
	for(int i=0;i<v[x].size();++i)if(!dep[v[x][i]])
		dep[v[x][i]]=dep[x],dfs(v[x][i]);
}
int lca(int x,int y)
{
	int dx=td[x]-td[y],i;
	if(dx<0)dx=-dx,swap(x,y);
	for(i=0;dx;++i,dx>>=1)if(dx&1)x=fa[i][x];
	if(x==y)return x;
	for(i=K;i--;)if(fa[i][x]!=fa[i][y])x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	int n,m,s,o,i,j,x,y,ls=0;
	n=read();m=read();s=read();o=read();
	for(i=1;i<=n;++i)p[i]=read();
	while(m--)x=read(),y=read(),ins(x,y,read());
	dj(s);dfs(s);
	for(i=1;i<=n;++i)for(j=h[i];j;j=e[j].nx)
		if(d[i]+e[j].w==d[e[j].t])++r[e[j].t];
	for(q[i=qn=0]=s;i<=qn;++i)
	{
		x=q[i];td[x]=td[fa[0][x]]+1;
		for(j=1;j<K;++j)fa[j][x]=fa[j-1][fa[j-1][x]];
		for(j=h[x];j;j=e[j].nx)if(d[x]+e[j].w==d[e[j].t])
		{
			if(!fa[0][e[j].t])fa[0][e[j].t]=x;
			else fa[0][e[j].t]=lca(fa[0][e[j].t],x);
			if(!--r[e[j].t])q[++qn]=e[j].t;
		}
	}
	for(j=read();j--;)
	{
		x=read()^(o*ls);y=read()^(o*ls);
		for(i=K;i--;)if(dep[fa[i][y]]>=dep[x])y=fa[i][y];
		printf("%d\n",ls=dep[y]-dep[x]);
	}
	fclose(stdin);fclose(stdout);return 0;
}
