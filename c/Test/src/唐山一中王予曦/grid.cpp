#include<cstdio>
#include<cstring>
#include<algorithm>
#define For(i,a,b) for(register int i=a;i<=b;++i)
#define Fdn(i,b,a) for(register int i=b;i>=a;--i)
using namespace std;
typedef long long LL;

int TT,x,y,n,m,c,d,mo,mp[55][55],f[55][55][55][55];

int main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	
	scanf("%d",&TT);
	while(TT--){
		scanf("%d%d%d%d%d",&n,&m,&c,&d,&mo);
		memset(mp,0,sizeof(mp));
		For(i,1,c){
			scanf("%d%d",&x,&y);
			mp[x][y]++;
		}
		memset(f,0,sizeof(f));
		For(p,0,d) f[1][1][1][p]=1;
		For(i,1,n){
			For(j,1,m){
				int rr=min(i+j-1,n);
				For(k,i+1,rr){ 
					int l=i+j-k;
					int tmp=mp[i][j]+mp[k][l];
					For(p,tmp,d){
						f[i][j][k][p]=(
							(f[i-1][j][k-1][p-tmp]+f[i-1][j][k][p-tmp])%mo+
							(f[i][j-1][k-1][p-tmp]+f[i][j-1][k][p-tmp])%mo
						)%mo;
					}
				}
			}
		}
		printf("%d\n",f[n-1][m][n][d]);
	}
	
	return 0;
}
	
	
	
