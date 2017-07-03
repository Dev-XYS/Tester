#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
struct edge{
	int to, len; edge *next, *rev;
	bool ban;
	edge(){}
	edge(int t, int l, edge *n):to(t), len(l), next(n){ban=0;}
}pe[400010], *g[100010], *pp[100010];
int n, m, eT, s, ty, q, pri[100010], t[100010];
bool M[100010];
long long dist[100010], len[100010], dep[100010]; bool in[100010];
long long mp[510][510];
queue<int> Q;
int dp[1000010], stk[100010];
inline int rd(){
	int a=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) (a*=10)+=c-'0', c=getchar();
	return a;
}
void spfa(){
	memset(dist, 0x3f, sizeof dist);
	Q.push(s); dist[s]=0; in[s]=1; int w;
	while(!Q.empty()){
		w=Q.front(); Q.pop(); in[w]=0;
		for(edge *t=g[w];t;t=t->next)
			if(dist[t->to]>dist[w]+t->len){
				dist[t->to]=dist[w]+t->len;
				if(!in[t->to])
					Q.push(t->to), in[t->to]=1;
			}
	}
}
int main(){
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	n=rd(), m=rd(), s=rd(), ty=rd();
	for(int i=1;i<=n;i++) pri[i]=rd();
	int u, v, l;
	for(int i=0;i<m;i++){
		u=rd(), v=rd(), l=rd();
		g[u]=&(pe[eT++]=edge(v, l, g[u]));
		g[v]=&(pe[eT++]=edge(u, l, g[v]));
		g[u]->rev=g[v]; g[v]->rev=g[u];
	}
	spfa();
	int c=s, cnt=1; M[s]=1;
	while(cnt<n){
		edge *k=NULL;
		for(edge *t=g[c];t;t=t->next){
			if(M[t->to]) continue;
			if(dist[t->to]!=dist[c]+t->len) continue;
			if(k){if(pri[t->to]<pri[k->to]) k=t;}
			else k=t;
		}
		if(!k) c=t[c];
		else k->ban=1, k->rev->ban=1, len[k->to]=k->len+len[c], dep[k->to]=dep[c]+1, pp[k->to]=c, c=k->to;
	}
	memset(mp, 0x3f, sizeof mp);
	for(int i=1;i<=n;i++){
		for(edge *t=g[i];t;t=t->next)
			if(!t->ban) mp[i][t->to]=min(mp[i][t->to], t->len);
		mp[i][i]=1;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				mp[j][k]=min(mp[j][k], mp[j][i]+mp[i][k]);
	q=rd(); int ans=0;
	while(q--){
		u=rd()^(ans*ty), v=rd()^(ans*ty);
		int cnt=0;
		memset(dp, 0, sizeof dp);
		while(v!=u){
			for(int i=0;i<cnt;i++)
				if(mp[stk[i]][v]==len[stk[i]]-len[v])
					dp[cnt]=max(dp[cnt], dep[stk[i]]-dep[v]+dp[i]);
			v=pp[v]->to;
		}
		printf("%d\n", dp[cnt]);
	}
	return 0;
}