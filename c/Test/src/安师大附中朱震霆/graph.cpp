#include"bits/stdc++.h"

using namespace std;
typedef long long ll;

ll P;

void exgcd(ll a,ll b,ll&x,ll&y){
	if(b==0){x=a>0?1:-1,y=0;return;}
	exgcd(b,a%b,y,x);y-=a/b*x;
}

ll inv(ll a){
	ll x,y;exgcd(a,P,x,y);
	return (x%P+P)%P;
}

ll mult(ll x,ll y){
	return ((x*y-(ll)((long double)x*y/P+0.5)*P)%P+P)%P;
}

const int N=105,M=2005;

int n,m,u[M],v[M],fa[N],l,E[N][N];
ll X[M],Y[M],A[M][M],B[M];
bool ist[N],vis[N];

void dfs(int x,int f){
	vis[x]=true,ist[x]=true;
	for(int v=1;v<=n;v++)if(E[x][v]){
		if(v==f)continue;
		if(ist[v]){
			l++;int p,q;
			for(p=x;p!=v;p=fa[p]){
				q=E[fa[p]][p];
				if(q>0)A[l][q]+=Y[q],B[l]+=X[q];
				else A[l][-q]-=Y[-q],B[l]-=X[-q];
			}
			q=E[x][v];
			if(q>0)A[l][q]+=Y[q],B[l]+=X[q];
			else A[l][-q]-=Y[-q],B[l]-=X[-q];
		}else if(!vis[v])fa[v]=x,dfs(v,x);
	}
	ist[x]=false;
}

void gauss(){
	register int i,j,k,l;
	for(i=1;i<=m;i++){
		for(l=0,j=i;j<=m;j++)if(A[j][i]){l=j;break;}
		for(j=i;j<=m;j++)swap(A[i][j],A[l][j]);swap(B[i],B[l]);
		ll y=inv(A[i][i]);
		for(j=i;j<=m;j++)A[i][j]=mult(A[i][j],y);
		B[i]=mult(B[i],y);
		for(j=1;j<=m;j++)if(i!=j){
			y=A[j][i];
			if(!y)continue;
			for(k=i;k<=m;k++)A[j][k]=(A[j][k]-mult(A[i][k],y)+P)%P;
			B[j]=(B[j]-mult(B[i],y)+P)%P;
		}
	}
}

int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d%d%d",&n,&m,&P);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",u+i,v+i,X+i,Y+i);
		E[u[i]][v[i]]=i,E[v[i]][u[i]]=-i;
	}
	for(int u=2;u<=n;u++){
		l++;
		for(int v=1;v<=n;v++)if(E[u][v]){
			if(E[u][v]>0)A[l][E[u][v]]++;
			else A[l][-E[u][v]]--;
		}
		B[l]=0;
	}
	dfs(1,0);
	gauss();
	for(int i=1;i<=m;i++)printf("%lld\n",B[i]);
	return 0;
}
