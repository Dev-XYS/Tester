#include"bits/stdc++.h"

using namespace std;

const int N=100005;
typedef long long ll;
const ll inf=1E16;

namespace io{
	const int L=(1<<18)+1;
	char _buf[L],*S,*T,c;
	char gc(){
		if(S==T){
			T=(S=_buf)+fread(_buf,1,L,stdin);
			return S==T?EOF:*S++;
		}
		return*S++;
	}
	template<class T>
	void gi(T&x){
		for(c=gc();c<'0'||c>'9';c=gc());
		x=c&15;
		for(c=gc();c>='0'&&c<='9';c=gc())x=x*10+(c&15);
	}
	char buf[25],*outs=buf+20,*outr=buf+20;
	template<class T>
	inline void print(register T a,register char x=0){
		if(x)*--outs=x,x=0;
		if(a<0)a=-a,x='-';
		if(!a)*--outs='0';
		else while(a)*--outs=(a%10)+48,a/=10;
		if(x)*--outs=x;
		fwrite(outs,outr-outs,1,stdout);outs=outr;
	}
};
using io::gi;
using io::print;

int n,m,q,s,ty,lastans,p[N],qu[N],ql,qr,t[N],dep[N],lca[3005][3005];
ll dist[N];
bool inq[N],vis[N];
vector<int>E[N],e[N],us,vs;
vector<ll>len[N];
typedef pair<int,int>pii;
vector<pii>ee;

int comp(const int&x,const int&y){
	return p[x]<p[y];
}

void dfs(int x){
	dep[x]=dep[t[x]]+1;
	sort(e[x].begin(),e[x].end(),comp);
	for(int i=0,L=e[x].size(),v;i<L;i++){
		v=e[x][i];
		if(~t[v])continue;
		t[v]=x,dfs(v);
	}
}

int h[N],nxt[N],to[N],tmp;
void addedge(int u,int v){
	to[++tmp]=v,nxt[tmp]=h[u],h[u]=tmp;
}

void DFS(int x){
	vis[x]=1;for(int i=h[x];i;i=nxt[i])if(!vis[to[i]])dfs(to[i]);
}

int ask(int u,int v){
	register int i,l,a,b,x,y,p,ans=dep[v]-dep[u];
	l=us.size(),memset(vis,0,n+1),vis[1]=1,memset(h,0,(n+1)<<2);
	while(tmp)nxt[tmp]=to[tmp]=0,tmp--;
	for(i=0;i<l;i++){
		a=us[i],b=vs[i];
		if(lca[a][u]==u&&lca[a][v]==a&&lca[b][u]==u&&lca[b][v]==b)continue;
		if(vis[a])DFS(b);
		addedge(a,b);
	}
	b=v;
	while(!vis[v]&&b!=u){
		a=t[b];
		if(vis[a])DFS(b);
		b=a;ans--;
	}
	return ans;
}

int dfs(int x,int y){
	if(x==y)return lca[x][y]=x;
	if(lca[y][x])return lca[x][y]=lca[y][x];
	if(dep[x]>dep[y])return lca[x][y]=dfs(t[x],y);
	return lca[x][y]=dfs(x,t[y]);
}

int sz[N],son[N];
void dfs_(int x){
	sz[x]=1;
	for(int i=0,L=e[x].size(),v;i<L;i++){
		v=e[x][i];
		if(t[v]==x){
			dfs_(v),sz[x]+=sz[v];
			if(sz[v]>sz[son[x]])son[x]=v;
		}
	}
}

vector<int> Son[N];
int bel[N];
void idfs(int x,int b){
	bel[x]=b;Son[b].push_back(x);
	if(son[x])idfs(son[x],b);
	for(int i=0,L=e[x].size(),v;i<L;i++){
		v=e[x][i];
		if(t[v]==x&&v!=son[x])idfs(v,v);
	}
}

int getlca(int u,int v){
	while(bel[u]!=bel[v])
		if(dep[bel[u]]>dep[bel[v]])
			u=t[bel[u]];
		else
			v=t[bel[v]];
	return dep[u]<dep[v]?u:v;
}

int getlast(int x,int f){
	int r;
	while (bel[x] != bel[f])
		r = bel[x], x = t[r];
	return x == f ? r : Son[bel[x]][dep[f]-dep[bel[x]]+1];
}

int query(int u,int v){
	int l=ee.size(),ans=0,mx=dep[v]-dep[u],p=getlast(v,u);
	for(int i=0;i<l;i++){
		if (ans == mx) return ans;
		if (getlca(ee[i].first, p) != p && getlca(ee[i].second, v) == ee[i].second && getlca(ee[i].second, u) == u){
			ans = max(ans, dep[ee[i].second] - dep[u]);
			continue;
		}
	}
	return ans;
}

int main(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	gi(n),gi(m),gi(s),gi(ty);
	for(int i=1;i<=n;i++)gi(p[i]);
	for(int i=1,u,v,l;i<=m;i++){
		gi(u),gi(v),gi(l);
		E[u].push_back(v),len[u].push_back(l);
		E[v].push_back(u),len[v].push_back(l);
	}
	for(int i=2;i<=n;i++)dist[i]=inf;
	ql=1,qr=2,qu[ql]=1;
	while(ql!=qr){
		int u=qu[ql];(++ql)%=n+3;inq[u]=true;
		for(int i=0,L=E[u].size(),v;i<L;i++){
			v=E[u][i];
			if(dist[v]>dist[u]+len[u][i]){
				dist[v]=dist[u]+len[u][i];
				if(!inq[v])qu[qr]=v,(++qr)%=n+3,inq[v]=1;
			}
		}
	}
	for(int u=1;u<=n;u++){
		for(int i=0,L=E[u].size(),v;i<L;i++){
			v=E[u][i];
			if(dist[v]==dist[u]+len[u][i]){
				e[u].push_back(v);
				us.push_back(u);
				vs.push_back(v);
			}
		}
	}
	memset(t,-1,sizeof(t));
	t[1]=0;
	dfs(1);
	gi(q);
	if(n<=3000){
		for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
			if(!lca[i][j])dfs(i,j);
		for(int i=1,u,v;i<=q;i++){
			gi(u),gi(v);if(ty)u^=lastans,v^=lastans;
			print(lastans=ask(u,v),'\n');
		}
	}else{
		int l=us.size();
		for(int i=0;i<l;i++)if(t[vs[i]]!=us[i])
			ee.push_back(make_pair(us[i],vs[i]));
		dfs_(1),idfs(1,1);
		for(int i=1,u,v;i<=q;i++){
			gi(u),gi(v);if(ty)u^=lastans,v^=lastans;
			print(lastans=query(u,v),'\n');
		}
	}
	return 0;
}
