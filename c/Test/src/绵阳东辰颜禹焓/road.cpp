#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

inline int read(){
	int ret=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	for(;ch>='0'&&ch<='9';ch=getchar()) ret=ret*10+ch-'0';
	return ret;
}

const int maxn=100000+10;
const int maxm=400000+10;

typedef long long ll;

struct Edge{
	int u,v,w;
	Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
};

struct Graph{
	Edge e[maxm];
	int first[maxn],next[maxm],ecnt;
	inline void init(){
		memset(first,-1,sizeof first);ecnt=0;
	}
	inline void add_edge(int u,int v,int w){
		next[ecnt]=first[u];first[u]=ecnt;e[ecnt++]=Edge(u,v,w);
		next[ecnt]=first[v];first[v]=ecnt;e[ecnt++]=Edge(v,u,w);
	}
	inline void output(){
		for(int i=0;i<ecnt;++i) printf("e[%d]=(%d,%d,%d)\n",i,e[i].u,e[i].v,e[i].w);
	}
}g,tr;

/********************原图读入以及最短路*********************/
int n,m,s,ty,p[maxn];
inline void init_data()
{
	cin>>n>>m>>s>>ty;
	g.init();
	for(int i=1;i<=n;++i) p[i]=read();
	for(int i=1,u,v,w;i<=m;++i)
	{
		u=read();v=read();w=read();
		g.add_edge(u,v,w);
	}
}

const int INF=1<<29;

ll d[maxn];
int inq[maxn];

inline void SPFA()
{
	for(int i=1;i<=n;++i) d[i]=INF;
	queue<int>q;q.push(s);d[s]=0;inq[s]=1;
	while(!q.empty()){
		int u=q.front();q.pop();inq[u]=0;
		for(int i=g.first[u];i!=-1;i=g.next[i]){
			int v=g.e[i].v;
			if(d[v] > d[u] +g.e[i].w){
				d[v]=d[u]+g.e[i].w;
				if(!inq[v]) q.push(v),inq[v]=1;
			}
		}
	}
}

/***********************建树**********************************/
int val[maxn],fa[maxn];//val[i]=1表示有往上连的最短路边,即黑点

inline int cmp(const int &a,const int &b){
	return p[a] < p[b];
}

vector<int>son[maxn];
void dfs(int u,int pre)
{
	for(int i=g.first[u];i!=-1;i=g.next[i])
	{
		int v=g.e[i].v;
		if(v==pre) continue;

		if(d[u] + g.e[i].w == d[v])
			son[u].push_back(v);

	}

	if(!son[u].size()) return ;
	sort(son[u].begin(),son[u].end(),cmp);

	for(int i=0,sz=son[u].size();i<sz;++i)
	{
		if(!fa[son[u][i]]) {
			fa[son[u][i]]=u,tr.add_edge(u,son[u][i],0);
			dfs(son[u][i],u);
		}
		else val[son[u][i]]=1;
	}
}

/******************************线段树****************************/
struct Node{
	int r;
	Node *lc,*rc;
	Node(){r=-1;lc=rc=0;}
	inline void up(){r= rc->r==-1 ? lc->r : rc->r;}
}*root;

#define mid ((l+r)>>1)
void build(Node* &p,int l,int r)
{
	p=new Node();if(l==r) return ;
	build(p->lc,l,mid);build(p->rc,mid+1,r);
}

void updata(Node* p,int l,int r,int pos,int v)
{
	if(l==r) {p->r= v? pos : -1; return ;}
	if(pos<=mid) updata(p->lc,l,mid,pos,v);
	else updata(p->rc,mid+1,r,pos,v);  p->up();
}

int query(Node* p,int l,int r,int L,int R)
{
	if(L<=l&&r<=R) return p->r;
	int ret=-1;
	if(L<=mid) ret=max(ret,query(p->lc,l,mid,L,R));
	if(mid<R ) ret=max(ret,query(p->rc,mid+1,r,L,R));
	return ret;
}

/******************************树剖******************************/

int tid[maxn],ID[maxn],id_cnt;
int sz[maxn],hv[maxn],dep[maxn],top[maxn];
void dfs1(int u)
{
	sz[u]=1;int M=0;dep[u]=dep[fa[u]]+1;
	for(int i=tr.first[u];i!=-1;i=tr.next[i])
	{
		int v=tr.e[i].v;
		if(v==fa[u]) continue;
		dfs1(v);sz[u]+=sz[v];
		if(sz[v] > M) M=sz[v],hv[u]=v;
	}
}

void dfs2(int u,int Top)
{
	top[u]=Top;tid[u]=++id_cnt;ID[id_cnt]=u;
	updata(root,1,n,id_cnt,val[u]);
	if(sz[u]==1) return ;
	dfs2(hv[u], Top);

	for(int i=tr.first[u];i!=-1;i=tr.next[i])
		if(tr.e[i].v!=hv[u] && tr.e[i].v!=fa[u]) dfs2(tr.e[i].v,tr.e[i].v);
}

/*********************回答询问***************************/

inline void solve()
{
//	for(int i=1;i<=n;++i) printf("val[%d]=%d\n",i,val[i]);
	int q,u,v,lastans=0;
	cin>>q;
	while(q--)
	{
		u=read();v=read();
		if(ty) u^=lastans;v^=lastans;

		int ans=0;
		while(dep[v] > dep[u])
		{
			int t=query(root,1,n,max(tid[top[v]],tid[u]),tid[v]);
//			printf("u=%d top[v]=%d v=%d query=%d\n",u,top[v],v,t);
			if(t!=-1) {ans=dep[ID[t]]-dep[u];break;}
			v=fa[top[v]];
		}
		printf("%d\n",ans);
	}
}

int main()
{
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
	
	init_data();
	SPFA();

	tr.init();
	dfs(s,s);
//	tr.output();

	build(root,1,n);

	dfs1(s);dfs2(s,s);

	solve();
	return 0;
}

