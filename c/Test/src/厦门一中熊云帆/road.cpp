#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 201000;

struct Edge{
	int next,end,dis;
}edge[N<<1];
struct Node{
	ll dis;int id;
	Node(){}
	Node(ll dis,int id):dis(dis),id(id){}
};
bool operator < (const Node &a,const Node &b){
	return a.dis > b.dis;
}
priority_queue < Node > q;
vector <int> mp[N],rmp[N];
ll dis[N];
int f[N],g[N<<2];
int dfn[N],tot,fx[N],fat[N][20],dep[N];
int last[N][20];
int first[N],efn,rig[N];
int n,m,s,ty,a[N],fa[N],Q,ans;
void addedge(int,int,int);
void dij();
void dfs(int);
void init(int,int,int);
void dfs2(int,int);
int getval(int,int,int,int);
void change(int,int,int,int,int,int);
int lca(int,int);
int main(){
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&s,&ty);
	for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
	for (int i = 1;i <= m;i++){
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		addedge(x,y,z);
	}
	dij();
	for (int i = 1;i <= n;i++) f[i] = n;
	init(1,1,n);	
	dfs(s);
	fat[1][0] = 1;//?
	for (int i = 1;i <= 17;i++) 
		for (int j = 1;j <= n;j++)
			fat[j][i] = fat[fat[j][i-1]][i-1];
	dfs2(s,0);
//	for (int i = 1;i <= n;i++) printf("%d ",f[i]);printf("\n");
	for (int i = 1;i <= n;i++) last[i][0] = f[i];
	for (int i = 1;i <= 17;i++) 
		for (int j = 1;j <= n;j++) 
			last[j][i] = min(last[j][i-1],last[fat[j][i-1]][i-1]);
	scanf("%d",&Q);
	for (int i = 1;i <= Q;i++){
		int x,y,z;scanf("%d%d",&x,&y);
		if (ty) {x ^= ans;y ^= ans;}
//		printf("%d %d\n",dep[x],dep[y]);
		ans = 0;z = dep[y]-dep[x];
		for (int j = 17;j >= 0;j--)
			if (last[y][j] > dfn[x]) y = fat[y][j]; 
		if (last[y][0] > dfn[x]) y = fa[y];
		ans = dep[y]-dep[x];
		if (ans < 0) ans = 0;
		if (ans > z) ans = z;
		printf("%d\n",ans);
	}
	return 0;
}
void addedge(int x,int y,int z){
//	printf("%d %d %d\n",x,y,z);
	edge[++efn].end = y;
	edge[  efn].dis = z;
	edge[  efn].next = first[x];
	first[x] = efn;
	edge[++efn].end = x;
	edge[  efn].dis = z;
	edge[  efn].next = first[y];
	first[y] = efn;
}
void dij(){
	memset(dis,0x3f,sizeof(dis));
	int t = 1,w = 1;dis[s] = 0;
	q.push(Node(0,s));
	while (!q.empty()){
		Node x = q.top();q.pop();
		while (!q.empty() && x.dis != dis[x.id]){
			x = q.top();q.pop();
		}
		if (x.dis != dis[x.id]) break;
		int u = x.id;
		for (int h = first[u];h;h = edge[h].next){
			int v = edge[h].end;
			if (dis[v] > dis[u]+edge[h].dis){
				dis[v] = dis[u]+edge[h].dis;
				q.push(Node(dis[v],v));
			}
		}
	}
//	for (int i = 1;i <= n;i++) printf("%lld ",dis[i]);printf("\n");
	for (int i = 1;i <= n;i++) {
		while (!q.empty()) q.pop();
		for (int h = first[i];h;h = edge[h].next){
			int j = edge[h].end;
			if (dis[i]+edge[h].dis == dis[j]){
				q.push(Node(a[j],j));
			}
		}
		while (!q.empty()){
			Node g = q.top();q.pop();
			mp[i].push_back(g.id);
			rmp[g.id].push_back(i);
		}
	}
}
void dfs(int p){
//	printf("%d\n",p);
	dfn[p] = ++tot;fx[tot] = p;
	for (int i = 0;i < mp[p].size();i++){
		int u = mp[p][i];
		if (dfn[u] == 0) {
			fa[u] = p;
			dep[u] = dep[p]+1;
			fat[u][0] = p;
			dfs(u);
		}
		else if (dfn[u] > dfn[p]){
			f[u] = min(f[u],dfn[p]);
		}
	}
	rig[p] = tot;
}
void init(int p,int l,int r){
	g[p] = n;
	if (l == r) return;
	int mid = l + r >> 1;
	init(p<<1,l,mid);
	init(p<<1|1,mid+1,r);
}
void dfs2(int p,int mn){
	
	for (int i = mp[p].size()-1;i >= 0;i--) {
		int u = mp[p][i];
		if (fa[u] == p) 
			dfs2(u,dfn[u]-1);
	}
	int val = dfn[p];
	for (int i = 0;i < rmp[p].size();i++){
		int u = rmp[p][i];
		if (dfn[u] > mn){
			val = min(val,getval(1,1,n,dfn[u]));
			f[p] = min(f[p],min(dfn[lca(p,u)],getval(1,1,n,dfn[u])));
		}
	}
	val = min(val,f[p]);
	change(1,1,n,dfn[p],rig[p],val);
}
int getval(int p,int l,int r,int x){
	if (l == r) return g[p];
	int mid = l + r >> 1,ans;
	if (x <= mid) ans = getval(p<<1,l,mid,x);
	else ans = getval(p<<1|1,mid+1,r,x);
	return min(ans,g[p]);
}
void change(int p,int l,int r,int x,int y,int z){
	if (l == x && r == y) {
		g[p] = min(g[p],z);return;
	}
	int mid = l + r >> 1;
	if (y <= mid) change(p<<1,l,mid,x,y,z);
	else if (mid < x) change(p<<1|1,mid+1,r,x,y,z);
	else{
		change(p<<1,l,mid,x,mid,z);
		change(p<<1|1,mid+1,r,mid+1,y,z);
	}
}
int lca(int x,int y){
	if (dep[x] < dep[y]) swap(x,y);
	for (int i = 17;i >= 0;i--)
		if (dep[fat[x][i]] >= dep[y]) x = fat[x][i];
	if (x == y) return x;
	for (int i = 17;i >= 0;i--) 
		if (fat[x][i] != fat[y][i]){
			x = fat[x][i];
			y = fat[y][i];
		}
	return fa[x];
}

