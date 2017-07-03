#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int N=50;
const int M=2000;
int n,m,cnt,P,top,root;
int first[N],to[M],nxt[M],Av[M],Bv[M],Cv[M];
int sta[M]; bool vis[N];
int readin() {
	int x=0,f=1; char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void add(int u,int v) {
	to[++cnt]=v;
	nxt[cnt]=first[u];
	first[u]=cnt;
	return;
}
void read() {
	n=readin(),m=readin(),P=readin();
	for (int u,v,a,b,i=1;i<=m;i++) {
		u=readin(),v=readin(),a=readin(),b=readin();
		add(u,v),Av[cnt]=a,Bv[cnt]=b;
		add(v,u),Av[cnt]=-a,Bv[cnt]=b;
	}
	return;
}
int tr(int x) {
	x%=P;
	x=(x+P)%P;
	return x;
}
bool bfs(int x,int s1,int s2) {
	if (x==root&&vis[x])
		return s1==s2;
	for (int i=first[x];i;i=nxt[i]) 
		if (!vis[to[i]]) {
			vis[to[i]]=1;
			if (!bfs(to[i],tr(s1+Bv[i]*Cv[i]),tr(s2+Av[i])))
				return false;
			vis[to[i]]=0;
		}
	return true;
}
bool check() {
	for (int i=1;i<=n;i++) {
		int sum=0;
		for (int j=first[i];j;j=nxt[j])
			sum+=Cv[j];
		if (sum)
			return false;
	}
	for (int i=1;i<=n;i++) {
		root=i;
		memset(vis,0,sizeof vis);
		if (!bfs(root,0,0))
			return false;
	}
	return true;
}
void dfs(int step) {
	if (step>m) {
		if (check()) {
			for (int i=1;i<=m*2;i+=2)
				printf("%d\n",Cv[i]);
		}
		return;
	}
	for (int i=0;i<P;i++) {
		Cv[(step<<1)-1]=i;
		Cv[(step<<1)]=0-i;
		dfs(step+1);
	}
	return;
}
namespace wtf {
	int tot;
	ll mat[M][M],ans[M];
int tr(int x) {
	x%=P;
	(x+=P)%=P;
	return x;
}
int trans(int x) {
	if (x&1) x++;
	return x>>1;
}
void bfs(int x) {
	if (x==root&&vis[x]) {
		tot++;
		for (int i=1;i<=top;i++) {
			int t=trans(sta[i]);
			mat[tot][t]=Bv[sta[i]];
		}
		for (int i=1;i<=top;i++)
			mat[tot][m+1]+=Av[sta[i]];
		mat[tot][m+1]=tr(mat[tot][m+1]);
		return;
	}
	for (int i=first[x];i;i=nxt[i]) 
		if (!vis[to[i]]) {
			vis[to[i]]=1;
			sta[++top]=i,bfs(to[i]),top--;
			vis[to[i]]=0;
		}
	return;
}
void pre() {
	for (int i=1;i<=n;i++)
		root=i,bfs(i);
	return;
}
ll quick(ll p,int q) {
	ll res=1;
	while(q) {
		if (q&1)
			(res*=p)%=P;
		(p*=p)%=P;
		q>>=1;
	}
	return res;
}
void guass() {
	for (int i=1;i<=m;i++) {
		int p=i;
		for (int j=i+1;j<=tot;j++)
			if (mat[j][i]>mat[p][i]) p=j;
		if (p!=i)
			for (int j=i;j<=m+1;j++)
				swap(mat[i][j],mat[p][j]);
		for (int j=i+1;j<=tot;j++) {
			int t=quick(mat[i][i],P-2)*mat[j][i]%P;
			for (int k=i;k<=m+1;k++) {
				mat[j][k]-=mat[i][k]*t;
				mat[j][k]=tr(mat[j][k]);
			}
		}
	}
	for (int i=m;i>=1;i--) {
		ans[i]=quick(mat[i][i],P-2)*mat[i][m+1]%P;
		for (int j=i-1;j;j--) {
			mat[j][m+1]-=ans[i]*mat[i][i]%P;
			mat[j][m+1]=tr(mat[j][m+1]);
		}
	}
	for (int j=1;j<=m;j++)
		printf("%lld\n",ans[j]);
	return;
}
	void work()  {
		pre();
		guass();
		return;
	}
}
int main() {
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	read();
	if (n<=5) dfs(1);
	else wtf::work();
	return 0;
}