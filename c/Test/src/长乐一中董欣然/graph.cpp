#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int str[4005],end[4005],nxt[4005],bo[4005],poi[105];
ll A[4005],B[4005];
int que[4005],vis[4005];
ll a[2105][2005],mod;
int tot=1,q,n,m,cnt,mark;
void add(int x,int y,ll z,ll w)
{
	nxt[++tot]=poi[x];
	poi[x]=tot;
	str[tot]=x, end[tot]=y;
	A[tot]=z, B[tot]=w;
}
int dfs(int x,int la,int des)
{
	if (x==des) return 1;
	if (vis[x]==mark) return 0;
	vis[x]=mark;
//	printf("s");
	for (int i=poi[x],y; y=end[i],i; i=nxt[i])
	if (la!=y){
		if (dfs(y,x,des)){
			bo[i]=1;
			que[++q]=i;
			return 1;
		}
	}
	return 0;
}
void build()
{
	for (int i=2; i<=tot; i+=2)
//	if (!bo[i] && !bo[i+1])
	{
		que[q=1]=i; mark=i;
		if (dfs(end[i],0,str[i])){
			++cnt;
			for (int j=1; j<=q; ++j){
			//	printf("%d ",que[j]/2);
				a[cnt][que[j]/2]=B[que[j]];
				(a[cnt][0]+=A[que[j]])%=mod;
			}
		//	printf("\n");
		}
	}
/*for (int i=1; i<=cnt; ++i){
		for (int j=0; j<=m; ++j) printf("%lld ",a[i][j]);
		printf("\n");
	}*/
}
ll ksm(ll x,ll d)
{
	ll res=1;
	for (; d; d/=2,x=x*x%mod)
	if (d%2) res=res*x%mod;
	return res;
}
void Gauss()
{
//	printf("c %d ",cnt);
	int r=1;
	for (int k=1; k<=m; ++k){
		int d=0;
		for (int i=r; i<=cnt; ++i)
		if (a[i][k]){
			d=i; break;
		}
		if (!d) continue;
		swap(a[d],a[r]);
	//	printf("ex %d ",k);
		ll fm=ksm(a[r][k],mod-2);
		for (int i=r; i<=cnt; ++i)
		if (i!=r && a[i][k]){
			ll tmp=a[i][k]*fm%mod;
			for (int j=0; j<=m; ++j)
			if (a[r][j]) (a[i][j]-=a[r][j]*tmp%mod)%=mod;
		}
		++r;
	}
	for (int i=1; i<=m; ++i){
		ll ans=a[i][0]*ksm(a[i][i],mod-2)%mod;
		ans=(ans+mod)%mod;
		printf("%lld\n",ans);
	} 
}
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
//	freopen("test.in","r",stdin);
	scanf("%d%d%lld",&n,&m,&mod);
	for (int i=1; i<=m; ++i){
		int x,y; 
		ll z,w;
		scanf("%d%d%lld%lld",&x,&y,&z,&w);
	//	scanf("%d%d",&A[x][y],&B[x][y]);
		z%=mod, w%=mod;
		add(x,y,z,w); add(y,x,-z,-w);
		a[x][i]=1; a[y][i]=-1;
	}
	cnt=n;
	build();
//	printf("s");
	Gauss();	
}
