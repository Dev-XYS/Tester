#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;
typedef long long LL;
const int N=4050;
const int M=400050;

LL dis[N],cnt[N];
int n,m,s,ty,Q,fa[N],ban[N];
int lans,p[N],q[30*N],dm,st[N];

struct graph{
	graph(){tot=0;}
	int head[N],to[M];
	int next[M],cost[M],tot;
	void addedge(int u,int v,int c){
		tot++;to[tot]=v,cost[tot]=c;
		next[tot]=head[u],head[u]=tot;
	}
}y,d;
struct edg{
	int u,v,c;
	friend bool operator<(edg a,edg b){
		return p[a.v]>p[b.v];
	}
}E[M];

void spfa(){
	int f,r,i;
	for(i=1;i<=n;i++)
		dis[i]=1ll<<50;
	dis[q[f=r=1]=s]=0;
	while(f<=r){
		for(i=y.head[q[f]];i;i=y.next[i]){
			if(dis[y.to[i]]>dis[q[f]]+y.cost[i]){
				dis[y.to[i]]=dis[q[f]]+y.cost[i];
				q[++r]=y.to[i];
			}
		}
		f++;
	}
}

void dfs(int x,int f){
	fa[x]=f;
	for(int i=d.head[x];i;i=d.next[i])
		if(fa[d.to[i]]==0)
			dfs(d.to[i],x);
}
void bfs(int x){
	int f,r,i;
	memset(cnt,0,sizeof(cnt));
	memset(ban,0,sizeof(ban));
	q[f=r=cnt[s]=1]=s;
	for(i=st[0];i>x;i--)ban[st[i]]=st[i-1];
	while(f<=r){
		for(i=d.head[q[f]];i;i=d.next[i]){
			if(ban[q[f]]!=d.to[i]&&cnt[d.to[i]]==0){
				cnt[d.to[i]]=1;
				q[++r]=d.to[i];
			}
		}
		f++;
	}
}

int main(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	
	int i,j,k,c;
	scanf("%d%d%d%d",&n,&m,&s,&ty);
	for(i=1;i<=n;i++)scanf("%d",&p[i]);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&j,&k,&c);
		y.addedge(j,k,c),y.addedge(k,j,c);
	}
	
	spfa();
	for(i=1;i<=n;i++)
		for(j=y.head[i];j;j=y.next[j])
			if(dis[i]+y.cost[j]==dis[y.to[j]])
				E[++dm]=(edg){i,y.to[j],y.cost[j]};
	sort(E+1,E+dm+1);
	for(i=1;i<=dm;i++)
		d.addedge(E[i].u,E[i].v,E[i].c);
	dfs(s,0);
	
	scanf("%d",&Q);
	for(i=1;i<=Q;i++){
		scanf("%d%d",&j,&k);
		if(ty)j^=lans,k^=lans;
		for(c=st[st[0]=1]=k;c!=j;c=fa[c])
			st[++st[0]]=fa[c];
		int lb=1,rb=st[0];
		while(lb<=rb){
			int mid=(lb+rb)>>1;
			if(bfs(mid),cnt[k])rb=mid-1;
			else lb=mid+1;
		}
		printf("%d\n",lans=st[0]-lb);
	}

	return 0;
}

