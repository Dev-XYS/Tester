#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<algorithm>
#include<ctime>
using namespace std;
typedef long long ll;
const int N=100010,M=400010;
const ll INF=10000000000000LL;
struct trnode
{
	int l,r,cnt,num;
}tr[N*4];
struct enode
{
	int a,b;ll l;
}e2[M],e[M];
int fi[N],ne[M],fi2[N],ne2[M],vis[N];
ll d[N];
int dep[N],dfn[N],end[N],ans[N];
int c[N],que[N],head,tail,du[N],pr[N];
int mxnu[N],qz[N],top[N],size[N],fa[N],val[N];
int i,n,m,s,t,pE,pE2,j,p=0;
int st[N][18],p0,root[N],opt;
struct Tnode
{
	int ls,rs,cnt;
}T[N*20];
int read()
{
	int x=0;char ch=getchar();
	while (!isdigit(ch)) ch=getchar();
	while (isdigit(ch)) {x=x*10+ch-'0';ch=getchar();}
	return x;
}
bool cmp(const enode &a,const enode &b)
{
	return val[a.b]>val[b.b];
}
void addE(int u,int v)
{
    pE++;
    e[pE].a=u;e[pE].b=v;
    ne[pE]=fi[u];
    fi[u]=pE;
}
void addE2(int u,int v,ll w)
{
    pE2++;
    e2[pE2].a=u;e2[pE2].b=v;
    e2[pE2].l=w;
    ne2[pE2]=fi2[u];
    fi2[u]=pE2;
}
priority_queue<pair<ll,int> > q;
void dijkstra(int s)
{
    for (int i=1;i<=n;i++) d[i]=INF;
    d[s]=0;
    q.push(make_pair(0,s));
    while (!q.empty())
    {
    	int u=q.top().second,dis=-q.top().first;
    	q.pop();if (d[u]!=dis) continue;
    	for (int j=fi2[u];j;j=ne2[j])
    		if (d[u]+e2[j].l<d[e2[j].b])
    		{
    			d[e2[j].b]=d[u]+e2[j].l;
    			q.push(make_pair(-d[e2[j].b],e2[j].b));
    		}	
    }
}
void dfs1(int u)
{
    size[u]=1;vis[u]=1;
    for (int j=fi[u];j>0;j=ne[j])
    {
        if (vis[e[j].b]) continue;
        e[j].l=1;
        fa[e[j].b]=u;
        dep[e[j].b]=dep[u]+1;
        dfs1(e[j].b);
        size[u]+=size[e[j].b];
        if (size[mxnu[u]]<size[e[j].b]) mxnu[u]=e[j].b;
    }
}
void dfs2(int u)
{
    p++;dfn[u]=p;
    if (mxnu[u]!=0)
    {
        qz[mxnu[u]]=1;
        if (qz[u]) top[mxnu[u]]=top[u];
            else top[mxnu[u]]=mxnu[u];
        dfs2(mxnu[u]);
    }
    for (int j=fi[u];j>0;j=ne[j])
    {
        if (dfn[e[j].b]>0||e[j].l==0) continue;
        top[e[j].b]=e[j].b;
        dfs2(e[j].b);
    }
    end[u]=p;
}
void insert(int l,int r,int x,int c1,int &c2)
{
	p0++;c2=p0;T[c2]=T[c1];
	T[c2].cnt++;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (x<=mid) insert(l,mid,x,T[c1].ls,T[c2].ls);
		else insert(mid+1,r,x,T[c1].rs,T[c2].rs);
}
void dfs(int u)
{
	vis[u]=1;
	insert(1,n,dep[c[u]],root[st[u][0]],root[u]);
	for (int j=fi[u];j;j=ne[j])
		if (!vis[e[j].b])
		{
			st[e[j].b][0]=u;
			dfs(e[j].b);
		}
}
void build(int ls,int rs,int c)
{
	tr[c].l=ls;tr[c].r=rs;
	tr[c].num=0;tr[c].cnt=0;
	if (ls==rs) return;
	int mid=(ls+rs)>>1;
	build(ls,mid,(c<<1));
	build(mid+1,rs,(c<<1)+1);
}
int qnum(int ls,int rs,int c)
{
	if (tr[c].l==ls&&tr[c].r==rs) return tr[c].num;
	int mid=(tr[c].l+tr[c].r)>>1,ret=0,preret;
	if (ls<=mid)
	{
		preret=qnum(ls,min(mid,rs),(c<<1));
		if (dep[ret]>dep[preret]) ret=preret;
	}
	if (rs>mid)
	{
		preret=qnum(max(mid+1,ls),rs,(c<<1)+1);
		if (dep[ret]>dep[preret]) ret=preret;
	}
	return ret;
}
void change(int x,int k,int c)
{
	if (dep[k]<dep[tr[c].num]) tr[c].num=k;
	if (tr[c].l==tr[c].r) return;
	int mid=(tr[c].l+tr[c].r)>>1;
	if (x<=mid) change(x,k,(c<<1));
		else change(x,k,(c<<1)+1);
}
bool check(int l,int r,int x,int c1,int c2)
{
	if (r<=x&&T[c2].cnt-T[c1].cnt>0) return true;
	if (r<=x) return false;
	if (T[c2].cnt==0) return false;
	int mid=(l+r)>>1;bool ret=false;
	ret|=check(l,mid,x,T[c1].ls,T[c2].ls);
	if (!ret&&x>mid) ret|=check(mid+1,r,x,T[c1].rs,T[c2].rs);
	return ret;
}
int getc(int u,int v)
{
	int ret=0,j,preret;
	while (top[u]!=top[v])
	{
		if (dep[top[u]]>=dep[top[v]])
		{
			if (qz[u]) preret=qnum(dfn[top[u]],dfn[u],1);
			    else preret=c[u];
			if (dep[ret]>dep[preret]) ret=preret;
			u=fa[top[u]];
		}
		else v=fa[top[v]];
	}
	if (u==v) preret=c[u];
	else
	{
	    if (dep[u]<dep[v]) preret=qnum(dfn[u],dfn[u],1);
	        else preret=qnum(dfn[v],dfn[u],1);
	}
	if (dep[ret]>dep[preret]) ret=preret;
	return ret;
}
int up(int u,int d)
{
	for (int j=17;j>=0;j--)
		if (st[u][j]&&dep[st[u][j]]>=d) u=st[u][j];
	return u;
}
int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	n=read();m=read();s=read();opt=read();
	for (i=1;i<=n;i++) val[i]=read();
	for (i=1;i<=m;i++)
	{
		int u=read(),v=read();ll w=(ll)read();
		addE2(u,v,w);addE2(v,u,w);
	}
	dijkstra(s);
	sort(e2+1,e2+pE2+1,cmp);
	for (i=1;i<=pE2;i++)
		if (d[e2[i].a]+e2[i].l==d[e2[i].b]) {addE(e2[i].a,e2[i].b);du[e2[i].b]++;}
	memset(vis,0,sizeof(vis));
	build(1,n,1);dep[s]=1;
	dfs1(s);p=0;qz[s]=1;top[s]=s;dfs2(s);
	dep[0]=n+1;head=0;tail=1;que[1]=s;
	for (i=1;i<=n;i++) c[i]=i;
	while (head<tail)
	{
		head++;
		int u=que[head];
		if (qz[u]) change(dfn[u],c[u],1);
		for (int j=fi[u];j>0;j=ne[j])
		{
			int v=e[j].b;du[v]--;
			if (du[v]==0){tail++;que[tail]=v;}
			if (e[j].l==0)
			{
				int prec=getc(u,v);
				if (dep[prec]<dep[c[v]]) c[v]=prec;
			}
		}
	}
	memset(vis,0,sizeof(vis));
	dfs(s);
	for (i=1;i<=17;i++)
		for (j=1;j<=n;j++)
			if (st[j][i-1]) st[j][i]=st[st[j][i-1]][i-1];
	int qnum=read(),ans=0;
	while (qnum--)
	{
		int u=read(),v=read();
		if (opt) u^=ans,v^=ans;
		int d=dep[u];
		for (j=17;j>=0;j--)
		{
			if (st[v][j]&&dep[st[v][j]]>=d&&!check(1,n,d,root[st[v][j]],root[v]))
				v=st[v][j];
		}	
		ans=dep[v]-d;
		printf("%d\n",ans);
	}
	return 0;
}

