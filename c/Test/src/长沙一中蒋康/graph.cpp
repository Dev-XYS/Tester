#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1005
using namespace std;
long long n,m,MOD,cnt=1,fir[N],nxt[N],to[N],a[N],b[N],ma[N][N];
long long fa[N],up[N],tot,u,v,w,z,bac,now;
long long bz[N];
long long read(){
	long long x=0,t=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')  t=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*t;
}
void add(long long x,long long y){
	nxt[++cnt]=fir[x];to[cnt]=y;fir[x]=cnt;a[cnt]=w;b[cnt]=z;
	nxt[++cnt]=fir[y];to[cnt]=x;fir[y]=cnt;a[cnt]=-w;b[cnt]=z;
}
void go_on(long long x,long long y,long long z){
	++tot;
	while(x!=y){
		if(up[x]&1)  ma[tot][up[x]>>1]=-b[up[x]];
		else  ma[tot][up[x]>>1]=b[up[x]];
		ma[tot][m+1]+=a[up[x]];
		x=fa[x];
	}
	if(z&1)  ma[tot][z>>1]=-b[z];
	else  ma[tot][z>>1]=b[z];
	ma[tot][m+1]+=a[z];
}
long long ksm(long long x,long long y){
	long long ret=1;
	while(y){
		if(y&1)  ret=ret*x%MOD;
		x=x*x%MOD;
		y>>=1;
	}
	return ret;
}
void dfs(long long x){
	for(long long i=fir[x];i;i=nxt[i])
		if(to[i]!=fa[x]){
			if(!bz[to[i]]){
				fa[to[i]]=x;
				up[to[i]]=i^1;
				bz[to[i]]=bz[x]+1;
				dfs(to[i]);
			}
			else if(bz[to[i]]<bz[x])  go_on(x,to[i],i^1);
		}
}
int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	n=read();m=read();MOD=read();
	for(long long i=1;i<=m;++i){
		u=read();v=read();w=read();z=read();
		add(u,v);
	}
	for(long long i=1;i<=n;++i){
		++tot;
		for(long long j=fir[i];j;j=nxt[j])
			if(j&1)  ma[tot][j>>1]=-1;
			else  ma[tot][j>>1]=1;
	}
	bz[1]=1;
	dfs(1);
	for(long long i=1;i<=m;++i){
		for(long long j=i;j<=tot;++j)
			if(ma[j][i]){
				for(long long k=1;k<=m+1;++k)
					swap(ma[j][k],ma[i][k]);	
			}
		ma[i][i]=(ma[i][i]+MOD)%MOD;
		bac=ksm(ma[i][i],MOD-2);
		for(long long j=1;j<=tot;++j)
			if(j!=i&&ma[j][i]){
				now=ma[j][i]*bac%MOD;
				for(long long k=1;k<=m+1;++k)
					ma[j][k]=(ma[j][k]-ma[i][k]*now)%MOD;
			}
	}
	for(long long i=1;i<=m;++i){
		ma[i][m+1]=(ma[i][m+1]+MOD)%MOD;
		printf("%lld\n",ma[i][m+1]*ksm(ma[i][i],MOD-2)%MOD);
	}
	return 0;
}
