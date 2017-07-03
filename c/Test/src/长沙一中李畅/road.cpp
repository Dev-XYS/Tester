#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define LL long long

const int Maxn = 1e5+5,Maxm = 2e5+5;

inline int read(){
	int x = 0,f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch <= '9' && ch >= '0') 
		x = x*10+ch-'0',ch = getchar();
	return x * f;
}

int N,M,rt,type;
vector<int>G[Maxn];

namespace DominatorTree{

}

namespace MiniRoadTree{
	int val[Maxn],dfn[Maxn],fa[Maxn];
	int dep[Maxn],sz[Maxn],son[Maxn];
	int top[Maxn],rev[Maxn];
	int cnt , idx;

	bool cmp(int x,int y){return val[x] < val[y];}

	void dfs(int x){
		dep[x] = dep[fa[x]] + 1; sz[x] = 1;
		for(int i = 0,v; i < G[x].size() ; ++i)
			if(!dep[v = G[x][i]]{
				v = G[x][i];
				fa[v] = x; dfs(v);
				sz[v] += sz[x];
				if(sz[v] > sz[son[x]]) 
					son[x] = v;
			}
	}
	
	void init(int x,int toe){
		rev[dfn[x] = ++idx] = x; top[x] = toe;
		if(son[x]) init(son[x] , toe);
		
		for(int i = 0 ,v ; i < G[x].size() ; ++i)
			if(fa[v = G[x][i]] == x && v != son[x])
				init(v , v);
	}

	int Query(int y,int x){
		int ret = 0,SegRt = rt[x];
		while(top[x] != top[y]){
			ret = Seg.Query(SegRt,1,1,N,dfn[top[x]],dfn[x]);
			if(ret) break;
			x = fa[top[x]];
		}
		if(!ret) Seg.Query(SegRt,1,1,N,dfn[y],dfn[x]);
		if(!ret) return 0;

		ret = rev[ret];
		if(ret != fa[x]) ret = dep[ret] - dep[y] + 1;
		else ret = dep[ret] = dep[y];
		return ret;	
	}

	void main(){
		for(int i = 1 ; i <= N ; ++i)
			sort(G[i].begin() , G[i].end() , cmp);
		dfs(rt); init(rt , rt);

		for(int = 1 ; i <= N ; ++i)
			DominatorTree::id[i] = dfn[i];
		DominatorTree::init();

		int u , v , ans = 0;
		while(M--){
			u = read() , v = read();
			if(type) u ^= ans,v ^= ans;
			ans = Query(u , v);
			printf("%d\n",ans);
		}
	}
}

namespace Graph{
	
#define Pi paie<LL , int>
#define mk make_pair
#define fi first
#define se second

	int hed[Maxn],to[Maxn<<1];
	int len[Maxm<<1],nxt[Maxm<<1];
	int cnt; LL dis[Maxn];
	
	void Addedge(int x,int y,int z){
		nxt[++cnt] = hed[x]; to[cnt] = y;
		hed[x] = cnt;  len[cnt] = z;
		nxt[++cnt] = hed[y]; to[cnt] = x; 
		hed[y] = cnt; len[cnt] = z;
	}

	void Dijkstra{
		priority_queue<Pi , vector<int> greator<int> > Q; 
		for(int i = 1 ; i <= N ; ++i) dis[i] = 1LL << 60;
		dis[rt] = 0; Q.push(mk(dis[rt],rt));
		while(!Q.empty()){
			LL y = Q.top().fi; 
			int x = Q.top().se;
			Q.pop();
			if(dis[x] < y) continue;
			for(int v,i = hed[x] ; i ; i = nxt[i])
				if(dis[v = to[i]] > y + len[i])
					Q.push(mk(dis[v] = y + len[i],v));
		}
	}	

	void init(){
		for(int i = 1 ; i <= N ; ++i) 
			MiniRoadTree::val[i] = read();

		for(int x,y,z,i = 1 ; i <= M ; ++i){
			x = read(); y = read(); z = read();
			Addedge(x , y , z);
		}
		Dijkstra();

		for(int x = 1 ; x <= N ; ++x)
			for(int v,i = hed[x] ; i ; i = nxt[i])
				if(dis[v = to[i]] == dis[x] + len[i])
					G[x].push(v);
	}
}

int main(){
	N = read(); M = read();
	rt = read(); type = read();
	Graph::init();
	MiniRoadTree::main();
	return 0;
}
