#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
struct edge{
	int to, id; bool rev;
	edge(int t, int i, bool r):to(t), id(i), rev(r){}
};
int n, m, eT, x[2010], y[2010], st, stk[2010], h; ll P, A[2010], B[2010];
ll mat[2010][2010], ans[2010]; bool in[110], stk2[2010];
vector<edge> g[110]; typedef vector<edge>::iterator veit;
inline ll rd(){
	ll a=0, f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1; c=getchar();}
	while(isdigit(c)) (a*=10)+=c-'0', c=getchar();
	return a*f;
}
bool dfs(int p, int f){
	if(p==st) return true;
	in[p]=1; random_shuffle(g[p].begin(), g[p].end());
	for(veit t=g[p].begin();t!=g[p].end();t++){
		if(t->to==f) continue;
		if(in[t->to]) continue;
		stk2[h]=t->rev; stk[h++]=t->id;
		if(dfs(t->to, p)) return true;
		h--;
	}
	return in[p]=0;
}
ll qmul(ll a, ll b){
	ll ret=0, f=1; if(b<0) b=-b, f=-f;
	while(b){
		if(b&1) ret=(ret+a)%P;
		a=(a+a)%P, b>>=1;
	}
	return ret*f;
}
ll qpow(ll a, ll p){
	ll ret=1;
	while(p){
		if(p&1) ret=qmul(ret, a);
		a=qmul(a, a); p>>=1;
	}
	return ret;
}
ll inv(ll a){
	return qpow(a, P-2);
}
void Gauss(){
	for(int i=0;i<m;i++){
		for(int j=i;j<m;j++)
			if(mat[j][i]){
				for(int k=i;k<=m;k++)
					swap(mat[i][k], mat[j][k]);
				break;
			}
		ll o=inv(mat[i][i]);
		for(int j=i+1;j<m;j++){
			ll p=qmul(mat[j][i], o);
			for(int k=i;k<=m;k++)
				mat[j][k]=(mat[j][k]-qmul(p, mat[i][k])+P)%P;
		}
	}
	for(int i=m-1;~i;i--){
		for(int j=i+1;j<m;j++)
			mat[i][m]=(mat[i][m]-qmul(mat[i][j], ans[j])+P)%P;
		ans[i]=qmul(mat[i][m], inv(mat[i][i]));
	}
}
int main(){
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w", stdout);
	srand(212109);
	n=rd(), m=rd(), P=rd();
	for(int i=0;i<m;i++){
		x[i]=rd(), y[i]=rd(), A[i]=rd(), B[i]=rd();
		g[x[i]].push_back(edge(y[i], i, 0));
		g[y[i]].push_back(edge(x[i], i, 1));
	}
	for(int i=1;i<=n;i++)
		random_shuffle(g[i].begin(), g[i].end());
	for(int i=1;i<n;i++)
		for(veit t=g[i].begin();t!=g[i].end();t++)
			if(!t->rev) mat[i-1][t->id]=1;
			else mat[i-1][t->id]=P-1;
	int pt=n-1;
	for(int i=m-n-1;i<m;i++){
		int d=rand()%m; st=x[d];
		h=0; stk[h++]=d;
		if(!dfs(y[d], x[d])) i--;
		else{
			while(h--){
				mat[pt][stk[h]]=(P+B[stk[h]]*(stk2[h]?-1:1))%P;
				mat[pt][m]+=(P+A[stk[h]]*(stk2[h]?-1:1))%P;
			}
			pt++;
		}
	}
	Gauss();
	for(int i=0;i<m;i++)
		printf("%lld\n", ans[i]);
	return 0;
}