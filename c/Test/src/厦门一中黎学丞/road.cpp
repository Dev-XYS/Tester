#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#include<ctime>
#define eps 1e-9
#define ll long long
#define N 2000000
#define inf 1000000000
#define mkp make_pair
using namespace std;
int i,j,k,m,n,s,t,mn;
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
ll d[401000];
int n3,dfl[101000],dfr[101000],bin[50],faa[101000][20],bb[401000],t1;
int fir[2001000],zh[2001000],ne[2001000],qu[2001000],m2,ban[101000],vis[101000],mx,rt,last,tp,ans,s1,s2;
int quan[401000],zhi[401000],next[401000],first[401000],m1,b[401000],k1,k2,p[101000],dep[101000],fa[101000];
void ins(int u,int v,int w)
{
	ne[++m2]=fir[u];
	fir[u]=m2;
	zh[m2]=v;
	qu[m2]=w;
}
void dij()
{
	memset(d,63,sizeof(d));
	d[s]=0;
	q.push(mkp(0,s));
	int u,v,k;
	ll now;
	while (!q.empty())
	{
		u=q.top().second;
		now=q.top().first;
		q.pop();
		if (d[u]<now) continue;
		for (k=fir[u];k;k=ne[k])
		{
			v=zh[k];
			if (d[v]>now+qu[k])
			{
				d[v]=now+qu[k];
				q.push(mkp(d[v],v));
			}
		}
	}
}
int tt[201000],inm[201000],n1;
void insert(int u,int v)
{
	next[++m1]=first[u];
	first[u]=m1;
	zhi[m1]=v;
}
void build()
{
	n1=1;
	inm[s]=1;
	int c=s,k,v,yx,next,ne2;
	while (1)
	{
		yx=n+1;
		next=0;
		for (k=fir[c];k;k=ne[k])
		{
			v=zh[k];
			if (!inm[v])
			{
			  if (d[v]==d[c]+qu[k])
			    if (p[v]<yx)
				  yx=p[v],next=v,ne2=k;	
			}
		}
		if (!next)
		{
			c=tt[c];
			continue;
		}
		tt[next]=c;
		bb[ne2]=bb[ne2^1]=1;
		insert(c,next);
		insert(next,c);
		c=next;
		inm[c]=1;
		n1++;
		if (n1==n) break;
	}
}
void dfs1(int x,int ff)
{
	int k,v;
	dfl[x]=++n3;
	for (int i=1;i<=17;i++)
	if (bin[i]>dep[x]) break; else
	  faa[x][i]=faa[faa[x][i-1]][i-1];
	for (k=first[x];k;k=next[k])
	{
		v=zhi[k];
		if (v==ff) continue;
		dep[v]=dep[x]+1;
		fa[v]=x;
		faa[v][0]=x;
		dfs1(v,x);
	}
	dfr[x]=n3;
}
int bz(int u,int v)
{
	int j=0,dlt=dep[v]-dep[u]-1;
	while (dlt)
	{
		if (dlt&1) v=faa[v][j];
		j++;
		dlt>>=1;
	}
	return v;
}
void dfs2(int x)
{
	if (ban[x]) {mx=max(mx,dep[x]);return;}
	if (vis[x]) return;
	vis[x]=1;
	int k,v;
	for (k=first[x];k;k=next[k])
	{
		v=zhi[k];
		if (v==last&&x==s) continue;
		dfs2(v);
	}
}
bool in(int x,int u,int v)
{
	if (dfl[x]>=dfl[u]&&dfl[x]<=dfr[u]&&dfl[v]>=dfl[x]&&dfl[v]<=dfr[x]) return 1;
	return 0;
}
int main()
{
	bin[0]=1;
	for (i=1;i<=20;i++)
	  bin[i]=bin[i-1]<<1;
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	n=read();
	m=read();
	s=rt=read();
	tp=read();
	m2=1;
	for (i=1;i<=n;i++)
	  p[i]=read();
	for (i=1;i<=m;i++)
	{
		s1=read();
		s2=read();
		k=read();
		if (s1==s2) continue;
		ins(s1,s2,k);
		ins(s2,s1,k);
	}
	dij();
	build();
	dfs1(rt,0);
	if (n>0)
	{
		for (i=2;i<=m2;i++)
		  if (!bb[i])
		  {
		  	s1=zh[i];
		  	t1=zh[i^1];
		  	if (d[s1]+qu[i^1]==d[t1]) {;} else if (d[t1]+qu[i]==d[s1]) swap(s1,t1); else s1=t1=0;
		  	break;
		  }
		int T=read();
		while (T--)
		{
			s=read();
			t=read();
			if (tp)
			  s^=ans,t^=ans;
			if (!s1) ans=0; else
			{
			last=bz(s,t);
			if (in(t1,last,t)&&!in(s1,last,t))
			  ans=dep[t1]-dep[s]; else ans=0;
		    }
			printf("%d\n",ans);
		}
		return 0;
	}
	m1=0;
	memset(first,0,sizeof(first));
	for (i=1;i<=n;i++)
	  for (k=fir[i];k;k=ne[k])
	  	if (d[zh[k]]==d[i]+qu[k])
	  	  insert(i,zh[k]);
	int T=read();
	while (T--)
	{
		s=read();
		t=read();
		if (tp) s^=ans,t^=ans;
		for (i=1;i<=n;i++)
		  ban[i]=0,vis[i]=0;
		for (k=t;k!=s;last=k,k=fa[k])
		  ban[k]=1;
		mx=dep[s];
		dfs2(rt);
		printf("%d\n",ans=mx-dep[s]);
	}
}
