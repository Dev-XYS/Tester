#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 100000000000000000LL
#define N 5005
using namespace std;
long long fir[N],nxt[N<<1],to[N<<1],l[N<<1],fa[N],q,tmp;
long long dl[N*10],dis[N],tan[N],st,ed,u,v,s,ty;
long long p[N],cnt=1,ans,tot,n,m,w,now,fib[N];
bool in[N],bz[N];
int no[N<<1];
long long read(){
	long long x=0,t=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')  t=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*t;
}
void add(long long x,long long y,long long z){
	nxt[++cnt]=fir[x];to[cnt]=y;fir[x]=cnt;l[cnt]=z;
	nxt[++cnt]=fir[y];to[cnt]=x;fir[y]=cnt;l[cnt]=z;	
}
int main(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	n=read();m=read();s=read();ty=read();
	for(long long i=1;i<=n;++i)  p[i]=read(); 
	for(long long i=1;i<=m;++i){
		u=read();v=read();w=read();
		add(u,v,w);dis[i]=INF;
	}
	dis[s]=0;
	st=ed=1;
	dl[1]=s;in[s]=1;
	while(st<=ed){
		now=dl[st++];
		for(long long i=fir[now];i;i=nxt[i])
			if(dis[to[i]]>dis[now]+l[i]){
				dis[to[i]]=dis[now]+l[i];
				if(!in[to[i]]){
					in[to[i]]=1;
					dl[++ed]=to[i];
				}
			}
		in[now]=0;
	}
	now=s;p[0]=INF;bz[s]=1;
	while(now){
		u=0;
		for(long long i=fir[now];i;i=nxt[i])
			if(!bz[to[i]]&&dis[to[i]]==dis[now]+l[i]){
				if(p[to[i]]<p[u]){
					v=i;
					u=to[i];
				}
			}
		if(!u)  now=fa[now];
		else {
			fa[u]=now;
			fib[u]=v;
			now=u;
			bz[u]=1;	
		}
	}
//	for(int i=1;i<=n;++i)  printf("%d\n",dis[i]);
	q=read();
	while(q--){
		u=read();v=read();
		if(ty)  u=u^ans,v=v^ans;
		tmp=v;tot=0;
		while(v!=u){
			no[fib[v]]=q+1;no[fib[v]^1]=q+1;
			v=fa[v];++tot;	
		}
		for(long long i=1;i<=n;++i)  tan[i]=INF;
		st=ed=1;tan[s]=0;
		dl[1]=s;in[s]=1;
		while(st<=ed){
			now=dl[st++];
			for(long long i=fir[now];i;i=nxt[i])
				if(no[i]!=q+1&&tan[to[i]]>tan[now]+l[i]){
					tan[to[i]]=tan[now]+l[i];
					if(!in[to[i]]){
						in[to[i]]=1;
						dl[++ed]=to[i];
					}
				}
			in[now]=0;
		}
		v=tmp;
		while(v!=u){
			if(dis[v]==tan[v])  break;
			--tot;v=fa[v];	
		}
		ans=tot;
		printf("%lld\n",ans);
	}
	return 0;
}
