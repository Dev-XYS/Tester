#include<cstdio>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=a;i<=b;++i)
#define Fdn(i,b,a) for(register int i=b;i>=a;--i)
using namespace std;
typedef long long LL;
const int MAXN=105, MAXM=2005;

int n,m,x,y,totl,tot,last[MAXN],pre[2*MAXM],oth[2*MAXM],fp[MAXN],de[MAXN];
bool vis[MAXN];
LL mo,xa,xb,g[MAXM][MAXM],va[2*MAXM],vb[2*MAXM];

inline LL inm(LL x){return x<0?x+mo:(x>=mo?x-mo:x);}

inline void conn(int x,int y,LL a,LL b){
	//printf("co: %d->%d %lld,%lld\n",x,y,a,b);
	pre[++totl]=last[x]; last[x]=totl; oth[totl]=y;
	va[totl]=a; vb[totl]=b;
}

void dfs(int x){
	//printf("-->%d\n",x);
	vis[x]=1;
	for(int p=last[x];p;p=pre[p]){
		if(p==(fp[x]^1)) continue;
		int r=oth[p];
		if(!vis[r]){
			de[r]=de[x]+1; fp[r]=p;
			dfs(r);
		}else if(de[r]<de[x]){
			tot++;
			int u=x;
			while(u!=r){
				//printf("%d %d\n",u,r);
				//char ch=getchar();
				g[tot][fp[u]>>1]=vb[fp[u]];
				if(fp[u]&1) g[tot][fp[u]>>1]=inm(-g[tot][fp[u]>>1]);
				//printf("???%d: %lld\n",u,va[fp[u]]);
				g[tot][m+1]=inm(g[tot][m+1]+va[fp[u]]);
				u=oth[fp[u]^1];
			}
			g[tot][p>>1]=vb[p];
			if(p&1) g[tot][p>>1]=inm(-g[tot][p>>1]);
			g[tot][m+1]=inm(g[tot][m+1]+va[p]);
		}
	}
}

inline LL mul(LL x,LL y){
	return x*y - ((LL)((long double)x/mo *y)*mo);
}
inline LL qpow(LL x,LL p){
	LL ret=1;
	for(;p;x=mul(x,x),p>>=1) if(p&1) ret=mul(ret,x);
	return ret;
}

void gauss(){
	For(i,1,m){
		int u=0;
		For(j,i,tot) if(g[j][i]>0){u=j; break;}
		if(u!=i) For(k,i,m+1) swap(g[i][k],g[u][k]);
		For(j,i+1,tot){
			if(g[j][i]==0) continue;
			LL t=mul(g[j][i],qpow(g[i][i],mo-2));
			For(k,i,m+1) g[j][k]=inm(g[j][k]-mul(g[i][k],t));
		}
	}
	
	/*For(i,1,tot){
		For(j,1,m+1) printf("%lld ",g[i][j]); puts("");
	}*/
	Fdn(i,m,1){
		g[i][m+1]=mul(g[i][m+1],qpow(g[i][i],mo-2));
		Fdn(j,i-1,1){
			g[j][m+1]=inm(g[j][m+1]-mul(g[j][i],g[i][m+1]));
		}
	}
}
		
int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	
	scanf("%d%d%lld",&n,&m,&mo);
	totl=1;
	For(i,1,m){
		scanf("%d%d%lld%lld",&x,&y,&xa,&xb);
		conn(x,y,xa,xb); conn(y,x,inm(-xa),xb);
	}
	For(i,1,n){
		for(int p=last[i];p;p=pre[p]) g[i][p>>1]=((p&1)?-1:1);
	}
	tot=n;
	//printf("mo: %lld\n",mo);
	//printf("test: %lld\n",mul(5,6));
	dfs(1);
	/*For(i,1,tot){
		For(j,1,m+1) printf("%lld ",g[i][j]); puts("");
	}*/
	//puts("");
	gauss();
	For(i,1,m) printf("%lld\n",g[i][m+1]);
	
	return 0;
}
	
	
	
