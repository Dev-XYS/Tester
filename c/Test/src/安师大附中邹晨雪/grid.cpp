#include<bits/stdc++.h>
using namespace std;
#define pc(x) putchar(x)
namespace ib {char b[100];}
inline void pi(int x){
	if(x==0) {pc(48); return;}
	if(x<0) {pc('-'); x=-x;}
	char *s=ib::b;
	while(x) *(++s)=x%10,x/=10;
	while(s!=ib::b) pc((*(s--))+48);
}
inline void ri(int &x){
	x=0; static char c; bool t(0);
	while(c=getchar(),c<'0'||c>'9') if(c=='-') t=1; else t=0;
	do x=(x<<1)+(x<<3)+c-'0'; while(c=getchar(),c>='0'&&c<='9');
	if(t) x=-x;
}
bool G[55][55];
int f[103][51][51][51];
int jc[100024],njc[100024],P;
inline int ksm(int n,int c){
	int jc=1;
	while(c){
		if(c&1) jc=(long long)jc*n%P;
		n=(long long)n*n%P;
		c>>=1;
	}
	return jc;
}
void build(){
	int i;
	jc[0]=1,njc[0]=1;
	for(i=1;i<=100000;++i) jc[i]=(long long)jc[i-1]*i%P,njc[i]=(long long)njc[i-1]*ksm(i,P-2)%P;
}
inline int c(int m,int n){
	return (long long)jc[n]*njc[n-m]%P*njc[m]%P;
}
int main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout); 
	int i,j,k,l,gs,n,m,C,D,T,x,y;
	ri(T);
	while(T--){
		ri(n); ri(m); ri(C); ri(D); ri(P);
		if(n<=50&&m<=50){
			memset(G,0,sizeof(G));
			memset(f,0,sizeof(f));
			for(i=1;i<=C;++i){
				ri(x); ri(y);
				G[x][y]=1;
			}
			f[2][1][1][0]=1;
			for(i=2;i<=n+m;++i)
			for(j=1;j<=n&&j<i;++j)
			for(k=1;k<=n&&k<i;++k)
			for(l=0;l<=D;++l){
				f[i][j][k][l]%=P;
				x=i-j; y=i-k;
				if(j!=k||x!=y){
					gs=l+G[j][x+1]+G[k][y+1];
					if(gs<=D)
					f[i+1][j][k][gs]+=f[i][j][k][l];
					gs=l+G[j+1][x]+G[k+1][y];
					if(gs<=D)
					f[i+1][j+1][k+1][gs]+=f[i][j][k][l];
				}
				if(j!=k+1||x+1!=y){
					gs=l+G[j][x+1]+G[k+1][y];
					if(gs<=D)
					f[i+1][j][k+1][gs]+=f[i][j][k][l];
				}
				if(j+1!=k||x!=y+1){
					gs=l+G[j+1][x]+G[k][y+1];
					if(gs<=D)
					f[i+1][j+1][k][gs]+=f[i][j][k][l];
				}
			}
			int ans=0; 
			for(i=0;i<=D;++i) ans=(ans+f[n+m-1][n][n-1][i])%P;
			pi(ans); pc('\n');
		}
		else{
			if(n>m) swap(n,m);
			if(n<2) puts("0");
			else{
				build();
				pi((long long)c(n-2,n+m-4)*c(n-2,n+m-3)%P*ksm(n-1,P-2)%P);
				pc('\n'); 
			}
		}
	}
	return 0;
}

