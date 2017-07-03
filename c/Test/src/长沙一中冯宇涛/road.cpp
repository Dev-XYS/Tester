#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 100005
#define Log 18
#define Pii pair<ll, int>
#define fi first
#define se second
#define mk make_pair
using namespace std;
typedef long long ll;
inline int read(){
	int sum = 0, t = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ sum = sum * 10 + ch - '0'; ch = getchar(); }
	return sum * t;
}

int n, m, S, ty;
int ans, p[N], dep[N];

struct edge{
	int to, w;
};

vector<edge>G[N];
vector<edge>T[N];

int nxt[N], fir[N], cnt, to[N], fa[N][Log];

void add(int x, int y){
	nxt[++cnt] = fir[x]; to[cnt] = y; fir[x] = cnt;
}

bool cmp(edge x, edge y){ return p[x.to] < p[y.to]; }

ll dis[N];
bool vis[N];

void spfa(){
	queue<int>q;
	memset(dis, 0x3f, sizeof(dis));
	q.push(S); dis[S] = 0;
	while(!q.empty()){
		int x = q.front(); q.pop();
		vis[x] = false;
		for(int i = 0; i < G[x].size(); i++){
			edge &e = G[x][i];
			if(dis[e.to] > dis[x] + e.w){
				dis[e.to] = dis[x] + e.w;
				if(!vis[e.to]) vis[e.to] = true, q.push(e.to);
			}
		}
	}
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < G[i].size(); j++)
			if(dis[G[i][j].to] == dis[i] + G[i][j].w)
				T[i].push_back(G[i][j]);
	for(int i = 1; i <= n; i++)
		sort(T[i].begin(), T[i].end(), cmp);
}

void build(int x){
	for(int i = 0; i < T[x].size(); i++) if(!fa[T[x][i].to][0]){
		int y = T[x][i].to;
		fa[y][0] = x;
		add(x, y);
		build(y);
	}
}

int low[N];

void dfs(int x){
	for(int i = 1; i < Log; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for(int i = fir[x]; i ; i = nxt[i]){
		int y = to[i];
		dep[y] = dep[x] + 1;
		dfs(y);
	}
}

int rt[N];

struct segment{
	struct node{
		int lc, rc, S;
	}tr[N*Log];
	#define ls tr[ri].lc
	#define rs tr[ri].rc
	#define mid (l + r >> 1)
	#define to_l ls, l, mid
	#define to_r rs, mid + 1, r
	int tot;
	
	void insert(int &ri, int l, int r, int pos){
		tr[++tot] = tr[ri]; ri = tot;
		tr[ri].S++;
		if(l == r) return ;
		if(pos <= mid) insert(to_l, pos);
		else insert(to_r, pos);
	}
	
	int query(int li, int ri, int l, int r){
		if(l == r) return l;
		if(tr[ls].S == tr[tr[li].lc].S) return query(tr[li].rc, to_r);
		else return query(tr[li].lc, to_l);
	}
}Seg;

int decode(int x){ return x ^ (ans * ty); }

int up(int x, int d){
	for(int i = 0; i < Log; i++)
		if(d >> i & 1) x = fa[x][i];
	return x;
}

int lca(int x, int y){
	if(dep[x] < dep[y]) swap(x, y);
	x = up(x, dep[x] - dep[y]);
	if(x == y) return x;
	for(int i = Log - 1; ~i ; i--)
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}
#undef mid
int solve(int x, int y){
	int l = 0, r = dep[y] - dep[x];
	while(l < r){
		int mid = l + r + 1 >> 1;
		if(Seg.query(rt[up(y, r - mid + 1)], rt[y], 1, n) <= dep[x]) l = mid;
		else r = mid - 1;
	}
	return l;
}

void calc_low(){
	priority_queue<Pii>q;
	q.push(mk(0, S));
	while(!q.empty()){
		Pii res = q.top(); q.pop();
		int x = res.se; 
		rt[x] = rt[fa[x][0]];
		Seg.insert(rt[x], 1, n, low[x]);
		for(int i = 0; i < T[x].size(); i++){
			int y = T[x][i].to;
			if(fa[y][0] != x){
				int L = lca(x, y);
				low[y] = min(low[y], Seg.query(rt[L], rt[x], 1, n));
				low[y] = min(low[y], dep[L]);
			}
			if(!vis[y]) vis[y] = true, q.push(mk(res.fi - T[x][i].w, y));
		}
	}
}

int main(){
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	n = read(); m = read(); S = read(); ty = read();
	for(int i = 1; i <= n; i++) p[i] = read();
	for(int i = 1; i <= m; i++){
		int x = read(), y = read(), l = read();
		G[x].push_back((edge){y, l});
		G[y].push_back((edge){x, l});
	}
	spfa();
	build(S);
	dep[S] = 1;
	dfs(S);
	for(int x = 1; x <= n; x++)
		low[x] = dep[x];
	calc_low();
	for(int q = read(); q ; q--){
		int x = decode(read()), y = decode(read());
		printf("%d\n", ans = solve(x, y));
	}
}

