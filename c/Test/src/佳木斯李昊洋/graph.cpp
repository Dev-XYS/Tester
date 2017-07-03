#include<cstdio>
#include<algorithm>
#define gm 2002
using namespace std;
typedef long long ll;
int n,m;
ll p;
inline ll mul(const ll& a,const ll &b)
{
	return ((a*b-(ll)((long double)(a)/p*b)*p)+p)%p;
}
inline ll rev(ll a)
{
	ll x=p-2,ans=1;
	while(x)
	{
		if(x&1) ans=mul(ans,a);
		a=mul(a,a);
		x>>=1;
	}
	return ans;
}
int X[gm],Y[gm];
ll A[gm],B[gm];
struct e
{
	int t,no;
	e *n;
	e(int t,e *n,int no):t(t),n(n),no(no){}
}*f[gm];
ll a[gm][gm];
bool tr[gm],vis[gm];
int fa[gm],lk[gm],dep[gm];
int top;
void dfs(int x)
{
	vis[x]=1;
	for(e *i=f[x];i;i=i->n)
	{
		if(!vis[i->t])
		{
			dep[i->t]=dep[x]+1;
			fa[i->t]=x; tr[abs(i->no)]=1;
			lk[i->t]=-i->no; dfs(i->t);
		}
	}
}
void push(int x)
{
	if(tr[x]) return;
	ll* t=a[++top];
	int u=X[x],v=Y[x];
	if(dep[u]<dep[v]) swap(u,v);
	for(;u!=v;u=fa[u])
	{
		int r=lk[u];
		if(r>0)
		{
			t[r]=B[r];
			(t[m+1]+=A[r])%=p;
		}
		else
		{
			t[-r]=p-B[-r];
			(t[m+1]+=p-A[-r])%=p;
		}
	}
	if(dep[X[x]]<dep[Y[x]])
	{
		t[x]=B[x];
		(t[m+1]+=A[x])%=p;
	}
	else
	{
		t[x]=p-B[x];
		(t[m+1]+=p-A[x])%=p;
	}
}
void cosmos()
{
	for(int i=1;i<=m;++i)
	{
		int j=i;
		while(!a[j][i]) ++j;
		if(i!=j)
		{
			for(int k=i;k<=m+1;++k) swap(a[i][k],a[j][k]);
		}
		ll g=rev(a[i][i]);
		for(++j;j<=m+1;++j)
		{
			if(a[j][i])
			{
				ll rat=mul(a[j][i],g);
				for(int k=i;k<=m+1;++k)
				a[j][k]=(a[j][k]-mul(a[i][k],rat)+p)%p;
			}
		}
	}
	for(int i=m;i;--i)
	{
		a[i][i]=mul(a[i][m+1],rev(a[i][i]));
		for(int j=i-1;j;--j)
		{
			if(a[j][i])
			{
				a[j][m+1]=(a[j][m+1]-mul(a[j][i],a[i][i])+p)%p;
			}
		}
	}
}
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d%d%lld",&n,&m,&p);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%lld%lld",X+i,Y+i,A+i,B+i);
		f[X[i]]=new e(Y[i],f[X[i]],i);
		f[Y[i]]=new e(X[i],f[Y[i]],-i);
	}
	for(int i=1;i<=n;++i)
	{
		for(e *j=f[i];j;j=j->n)
		{
			int x=j->no;
			if(x>0) a[i][x]=1;
			else a[i][-x]=p-1;
		}
	}
	dfs(1); top=n;
	for(int i=1;i<=m;++i) push(i);
	cosmos(); for(int i=1;i<=m;++i) printf("%lld\n",a[i][i]);
	return 0;
}
