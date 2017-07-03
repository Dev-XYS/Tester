#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 100;
int n, m, P, sum[MAXN], flag, vis[MAXN], link[MAXN][MAXN];
struct edge { int u, v, a, b, c; } s[MAXN];

inline bool check_circle(int now, int head, int sum) {
	vis[now] = 1;
	for(int nxt = 1; nxt <= n; ++nxt) if(link[now][nxt] != 0) {
		int k = link[now][nxt];
		int nxt_sum = (sum + (k > 0 ? s[k].a - s[k].b*s[k].c : -s[-k].a + s[-k].b*s[-k].c)) % P;
		if(nxt == head && nxt_sum != 0) return false;
		if(vis[nxt]) continue;
		if(!check_circle(nxt, head, nxt_sum))
			{ vis[now] = 0; return false; }
	}
	vis[now] = 0;
	return true;
}

inline void dfs(int k) {
	if(k > m) {
		for(int i = 1; i <= n; ++i) vis[i] = sum[i] = 0;
		for(int i = 1; i <= m; ++i) { (sum[s[i].u] += s[i].c) %= P; (sum[s[i].v] -= s[i].c) %= P;}
		for(int i = 1; i <= n; ++i) if(sum[i] != 0) return;
		for(int i = 1; i <= n; ++i)
			if(!check_circle(i, i, 0)) return ;
		flag = 1;
		return ;
	}
	for(int w = 0; w < P && !flag; ++w) {
		s[k].c = w;
		dfs(k + 1);
	}
}

int main() {
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	
	scanf("%d%d%d", &n, &m, &P);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d%d%d", &s[i].u, &s[i].v, &s[i].a, &s[i].b);
		link[s[i].u][s[i].v] = i; link[s[i].v][s[i].u] = -i;
	}
	
	dfs(1);
	
	for(int i = 1; i <= m; ++i) printf("%d\n", s[i].c % P);
	
	return 0;
}
