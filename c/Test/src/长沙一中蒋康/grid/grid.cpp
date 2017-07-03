#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 55
using namespace std;
long long dp[2][N][N][N],T,n,m,C,D,MOD,o,bz[N][N],u,v;
long long read(){
	long long x=0,t=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')  t=-1;c=getchar();}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*t;
}
int main(){
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	T=read();
	while(T--){
		n=read();m=read();C=read();D=read();MOD=read();
		o=0;
		memset(dp,0,sizeof(dp));
		memset(bz,0,sizeof(bz));
		dp[0][1][1][0]=1;
		for(long long i=1;i<=C;++i){
			u=read();v=read();
			bz[u][v]=1;	
		}
		for(long long i=2;i<=n+m-2;++i){
			o^=1;
			memset(dp[o],0,sizeof(dp[o]));
			for(long long j=1;j<m;++j)
				for(long long k=j+1;k<=m;++k)
				if(i-j+1<=n&&i-k+1<=n&&i-j+1>=1&&i-k+1>=1){
					long long num=bz[i-j+1][j]+bz[i-k+1][k];
						for(long long l=0;l<=D;++l)
							dp[o][j][k][l+num]=(dp[o^1][j][k][l]+dp[o^1][j-1][k][l]+dp[o^1][j][k-1][l]+dp[o^1][j-1][k-1][l])%MOD;
				}
		}
		long long ans=0;
		for(long long i=0;i<=D;++i)  ans=(ans+dp[o][m-1][m][i])%MOD;
		printf("%lld\n",ans);
	}
	return 0;
}
