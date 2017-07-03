#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define For(i,a,b) for(register int i=a;i<=b;++i)
#define Fdn(i,b,a) for(register int i=b;i>=a;--i)
using namespace std;
typedef long long LL;
const int MAXN=100005, INF=0x3f3f3f3f;

int n,m,qe,s,typ,x,y,z,pp[MAXN],ind[MAXN],cind[MAXN],f[MAXN],q[MAXN+10],dd[MAXN],
	fa[MAXN],de[MAXN],ans,dis[MAXN];
bool vis[MAXN],mark[MAXN];
vector<int> zz[MAXN];

struct graph{
	int totl,last[MAXN],pre[4*MAXN],frm[4*MAXN],oth[4*MAXN],len[4*MAXN];
	inline void conn(int x,int y,int z){
		pre[++totl]=last[x]; last[x]=totl; frm[totl]=x; oth[totl]=y; len[totl]=z;
	}
}ga,gb;

void spfa(int s){
	memset(dis,0x3f,sizeof(dis)); dis[s]=0;
	int he=0, ta=1; q[1]=s;
	while(he!=ta){
		he=he%MAXN+1; int u=q[he];
		vis[u]=0;
		for(int p=ga.last[u];p;p=ga.pre[p]){
			int r=ga.oth[p];
			if(dis[u]+ga.len[p]<dis[r]){
				dis[r]=dis[u]+ga.len[p];
				if(!vis[r]){
					ta=ta%MAXN+1; q[ta]=r;
					vis[r]=1;
				}
			}
		}
	}
}

inline bool cmp(int a,int b){return pp[a]<pp[b];}

void dfs(int x){
	vis[x]=1;
	for(int p=gb.last[x];p;p=gb.pre[p]){
		int r=gb.oth[p];
		if(vis[r]) continue;
		zz[x].push_back(r);
	}
	if(!zz[x].size()) return;
	sort(zz[x].begin(),zz[x].end(),cmp);
	for(int i=0;i<zz[x].size();++i){
		int r=zz[x][i];
		if(vis[r]) continue;
		fa[r]=x; de[r]=de[x]+1; dfs(r);
	}
}

void topo(){
	For(i,1,n) cind[i]=ind[i], f[i]=INF;
	f[s]=mark[s]?s:0;
	int he=0, ta=1; q[1]=s;
	while(he<ta){
		int u=q[++he];
		if(u==y) return;
		if(mark[u]&&!f[u]) f[u]=u;
		for(int p=gb.last[u];p;p=gb.pre[p]){
			int r=gb.oth[p];
			cind[r]--;
			if(!f[u]) f[r]=0;
			else if(f[r]==INF||de[f[u]]<de[f[r]]) f[r]=f[u];
			if(!cind[r]) q[++ta]=r;
		}
	}
	//printf("%d\n",f[4]);
}

int main(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	
	scanf("%d%d%d%d",&n,&m,&s,&typ);
	For(i,1,n) scanf("%d",pp+i);
	For(i,1,m){
		scanf("%d%d%d",&x,&y,&z);
		ga.conn(x,y,z); ga.conn(y,x,z);
	}
	spfa(s);
	For(i,1,ga.totl) if(dis[ga.frm[i]]+ga.len[i]==dis[ga.oth[i]]){
		gb.conn(ga.frm[i],ga.oth[i],ga.len[i]);
		//printf("b.conn %d->%d %d\n",ga.frm[i],ga.oth[i],ga.len[i]);
		ind[ga.oth[i]]++;
	}
	//puts("ok");
	dfs(s);
	//puts("ok");
	
	//For(i,1,n) printf("%d ",fa[i]); puts("");
	
	scanf("%d",&qe);
	For(i,1,qe){
		scanf("%d%d",&x,&y);
		if(typ) x^=ans, y^=ans;
		int u=y; dd[y]=0;
		do{
			dd[fa[u]]=dd[u]+1;
			u=fa[u];
			mark[u]=1;
		}while(u!=x);
		topo();
		//printf("%d %d %d\n",f[1],f[2],f[3]);
		ans=dd[x]-dd[f[y]];
		printf("%d\n",ans);
		u=y;
		do{
			u=fa[u];
			mark[u]=0;
		}while(u!=x);
	}
	return 0;
}
	
	
	
