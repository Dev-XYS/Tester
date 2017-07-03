#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int T, n, m, C, D, MOD, dp[2][55][55][55];
bool blk[55][55];
inline int rd(){
	int a=0; char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) (a*=10)+=c-'0', c=getchar();
	return a;
}
void add(int &a, int b){a+=b; a=a>=MOD?a-MOD:a;}
int main(){
	freopen("grid.in", "r", stdin);
	freopen("grid.out", "w", stdout);
	T=rd();
	while(T--){
		n=rd(), m=rd(), C=rd(), D=rd(), MOD=rd();
		int x, y; memset(blk, 0, sizeof blk);
		for(int i=0;i<C;i++){
			x=rd(), y=rd(); blk[x][y]=1;
		}
		memset(dp, 0, sizeof dp); dp[0][1][1][0]=1;
		for(int i=3, t=1;i<n+m;i++, t^=1, memset(dp[t], 0, sizeof dp[t]))
			for(int j=1;j<i&&j<n;j++)
				for(int k=j+1;k<i&&k<=n;k++){
					int b=0; b+=blk[j][i-j]; b+=blk[k][i-k];
					for(int l=0;l+b<=D;l++){
						add(dp[t][j][k][l+b], dp[t^1][j][k][l]);
						if(j>1) add(dp[t][j][k][l+b], dp[t^1][j-1][k][l]);
						if(k>1) add(dp[t][j][k][l+b], dp[t^1][j][k-1][l]);
						if(j>1&&k>1) add(dp[t][j][k][l+b], dp[t^1][j-1][k-1][l]);
					}
				}
		int ans=0;
		for(int i=0;i<=D;i++)
			add(ans, dp[(n+m-1)&1][n-1][n][i]);
		printf("%d\n", ans);
	}
	return 0;
}