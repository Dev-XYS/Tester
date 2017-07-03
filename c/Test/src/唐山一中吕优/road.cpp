#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 400005
typedef long long LL;
int n,m,s,ty,a[N],que[N+2],ban[N],cur;
int dep[N],father[N],ans,q;
int pre[N],last[N],other[N],len[N],l;
int Pre[N],Last[N],Other[N],L;
LL dis[N];
bool vis[N],flag[N];

inline int read(void)
{
	int x=0;
	char ch=getchar();
	while (ch>'9'||ch<'0') ch=getchar();
	while (ch>='0'&&ch<='9') 
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x;
}

void connect(int x,int y,int z)
{
	l++;
	pre[l]=last[x];
	last[x]=l;
	other[l]=y;
	len[l]=z;
}

void Connect(int x,int y)
{
	L++;
	Pre[L]=Last[x];
	Last[x]=L;
	Other[L]=y;
}

void spfa(void)
{
	for (int i=1;i<=n;i++) dis[i]=1e14;
	int h=0,t=1;
	que[1]=s;dis[s]=0;
	while (h!=t) 
	{
		h=h%N+1;
		int u=que[h];vis[u]=0;
		for (int p=last[u];p;p=pre[p]) 
		{
			int v=other[p];
			if (dis[v]>dis[u]+len[p]) 
			{
				dis[v]=dis[u]+len[p];
				if (!vis[v]) 
				{
					t=t%N+1;
					que[t]=v;
					vis[v]=1;
				}
			}
		}
	}
}

void build(void)
{
	for (int i=1;i<=n;i++)
		for (int p=last[i];p;p=pre[p]) 
		{
			int v=other[p];
			if (dis[v]==dis[i]+len[p]) 
				Connect(i,v);
		}
}

bool dfs(int u,int goal)
{
	vis[u]=1;
	if (u==goal) return 1;
	for (int p=Last[u];p;p=Pre[p]) 
	{
		int v=Other[p];
		if (ban[u]==v) continue;
		if (vis[v]) continue;
		if (dfs(v,goal)) return 1;
	}
	return 0;
}

bool check(int v,int u,int d)
{
	int tmp1=v;
	while (d--) v=father[v];
	int tmp2=v;
	while (v!=u) 
	{
		ban[father[v]]=v;
		v=father[v];
	}
	for (int i=1;i<=n;i++) vis[i]=0;
	bool pd=dfs(s,tmp1);
	v=tmp2;
	while (v!=u) 
	{
		ban[father[v]]=0;
		v=father[v];
	}
	return pd;
}

int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	n=read();m=read();s=read();ty=read();a[0]=n+1;
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=m;i++) 
	{
		int x=read(),y=read(),z=read();
		connect(x,y,z);
		connect(y,x,z);
	}
	spfa();
	cur=s;flag[s]=1;
	while (1) 
	{
		int tmp=0;
		for (int p=last[cur];p;p=pre[p]) 
		{
			int v=other[p];
			if (flag[v]) continue;
			if (dis[v]!=dis[cur]+len[p]) continue;
			if (a[tmp]>a[v]) tmp=v;
		}
		if (tmp) 
		{
			father[tmp]=cur;
			dep[tmp]=dep[cur]+1;
			cur=tmp;
			flag[tmp]=1;
		}
		else tmp=father[cur],cur=tmp;
		if (tmp==0) break;
	}
	build();
	q=read();
	for (int i=1;i<=q;i++) 
	{
		int x=read(),y=read();
		x= ty?x^ans:x;
		y= ty?y^ans:y;
		ans=dep[y]-dep[x];
		int L=0,R=dep[y]-dep[x]-1;
		while (L<=R) 
		{
			int mid=(L+R)>>1;
			if (check(y,x,mid)) ans=mid,R=mid-1;
			else L=mid+1;
		}
		ans=dep[y]-dep[x]-ans;
		printf("%d\n",ans);
	}
	return 0;
}