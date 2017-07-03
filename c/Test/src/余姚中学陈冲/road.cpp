#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define MP make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
const ll oo = 1e17;
const int LEN = 1e5 + 5;
typedef pair <ll, int> pa;
int i, j, k, n, m, s, t, ans, ty, tot, Q;
priority_queue< pa, vector <pa>, greater<pa> > q;
int head[LEN], a[LEN], size[LEN], fa[LEN][22], dep[LEN], pre[LEN];
int p[LEN], dq[LEN], ind[LEN], D[LEN], fa2[LEN][22], lab[LEN];
int Time;
ll dis[LEN];
bool flag[LEN];
vector <int> g[LEN], T[LEN], F[LEN];
struct edge {
	int vet, next, len;
} E[LEN * 4];
void add(int u, int v, int c) {
	E[++tot] = (edge){v, head[u], c};
	head[u] = tot;
}
void dijkstra(int s) {
	for (int i = 1; i <= n; i++) {
		dis[i] = oo;
		flag[i] = false;
	}
	dis[s] = 0;
	q.push(MP(dis[s], s));
	while (!q.empty()) {
		int u = q.top().se;
		q.pop();
		if (flag[u]) {
			continue;
		}
		flag[u] = true;
		for (int e = head[u]; e != -1; e = E[e].next) {
			int v = E[e].vet;
			if (dis[v] > dis[u] + E[e].len) {
				dis[v] = dis[u] + E[e].len;
				q.push(MP(dis[v], v));
			}
		}
	}
}
bool cmp(const int &x, const int &y) {
	return a[x] < a[y];
}
void init() {
	for (int u = 1; u <= n; u++) {
		for (int e = head[u]; e != -1; e = E[e].next) {
			int v = E[e].vet;
			if (dis[v] == dis[u] + E[e].len) {
				g[u].push_back(v);
				F[v].push_back(u);
				ind[v]++;
			}
		}
		sort(g[u].begin(), g[u].end(), cmp);
	}
	int now = 0;
	memset(flag, false, sizeof(flag));
	flag[now = 1] = true;
	dep[1] = 1;
	for (int i = 2; i <= n; i++) {
		while (p[now] >= g[now].size()) {
			now = pre[now];
		}
		for (int j = p[now]; j < g[now].size(); j++) {
			int v = g[now][j];
			if (flag[v] == false) {
				flag[v] = true;
				p[now] = j + 1;
				T[now].push_back(v);
				dep[v] = dep[now] + 1;
				pre[v] = now;
				now = v;
				break;
			}
		}
	}
}
int lca(int x, int y) {
    if (x == 0) {
	    return y;
	}
    if (D[x] > D[y]) {
	    swap(x,y);
	}
    int j =  17;
    while (j >= 0) {
        if (D[fa[y][j]] >= D[x]) {
		    y = fa[y][j];
		}
        j--;
    }
    j = 17;
    while (j >= 0) {
        if (fa[x][j] != fa[y][j]) {
            x = fa[x][j];
            y = fa[y][j];
        }
        j--;
    }
    if (x == y) {
	    return x;
	} else {
	    return fa[x][0];
	}
}
void dfs(int u) {
	lab[u] = ++Time;
	size[u] = 1;
	for (int j = 0; j < T[u].size(); j++) {
		int v = T[u][j];
		dfs(v);
		size[u] += size[v];
	}
}
void build_DT() {
    int qhead = 0, qtail = 0;
    dq[++qtail] = s;
    while (qhead<qtail) {
        int u = dq[++qhead];
        for (int j = 0; j < g[u].size(); j++) {
        	int v = g[u][j];
            ind[v]--;
            if (ind[v] == 0) {
			    dq[++qtail] = v;
			}
        }
    }
	D[1] = 1;
    for (int i = 1; i <= n; i++) {
        int u = dq[i], root = 0;
        for (int j = 0; j < F[u].size(); j++) {
        	int v = F[u][j];
        	root = lca(root, v);
        }
        fa[u][0] = root;
        D[u] = D[root] + 1;
        for (int j = 1; j <= 17; j++) {
        	fa[u][j] = fa[fa[u][j - 1]][j - 1];
        }
    }
    dfs(s);
}
bool issub(int x, int y) {
	return lab[x] <= lab[y] && lab[y] <= lab[x] + size[x] - 1;
}
int ask(int x, int y) {
	int mindep = dep[y];
	y = fa[y][0];
	while (y) {
		if (issub(x, y)) {
			mindep = min(mindep, dep[y]);
		}
		y = fa[y][0];
	}
	return mindep - dep[x];
}
int main() {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	memset(head, -1, sizeof(head));
	tot = -1;
	scanf("%d %d %d %d", &n, &m, &s, &ty);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
	}
	dijkstra(s);
	init();
	build_DT();
	scanf("%d", &Q);
	while (Q--) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (ty) {
			x ^= ans;
			y ^= ans;
		}
		printf("%d\n", ans = ask(x, y));
	}
	return 0;
}
