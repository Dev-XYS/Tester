#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rep(i,st,n) for(int i=st,i_end=n;i<=i_end;++i)
using namespace std;

const int maxn=50+2;

int n,m,C=0,D=0,MOD=100000007;
int dp[2][maxn][maxn][maxn],val[maxn][maxn];

const int dx[]={0,-1};

inline void solve()
{
	cin>>n>>m>>C>>D>>MOD;
	memset(val,0,sizeof val);
	for(int i=1,x,y;i<=C;++i)
	{
		scanf("%d%d",&x,&y);
		val[x][y]=1;
	}

	memset(dp,0,sizeof dp);
	dp[0][1][1][0]=1;int cur=1;
	
	for(int i=3;i<=n+m;++i,cur^=1) 
	{
		rep(j,max(1,i-m),min(n,i-1))  rep(k,max(1,i-m),min(j,min(n,i-1)))
		{
			rep(c,0,D) dp[cur][j][k][c]=0;
			if(j==k && i!=n+m) continue;

			int t=val[j][i-j]+val[k][i-k];
			rep(c,t,D)
			{
				int &ans=dp[cur][j][k][c];
				ans=0;
				rep(k1,0,1) rep(k2,0,1){
					ans+=dp[cur^1][j+dx[k1]][k+dx[k2]][c-t];
					ans+= ans>=MOD ? -MOD:0;
				}
//				printf("dp[%d][%d][%d][%d]=%d\n",i,j,k,c,ans);
			}	
		}
	}
	int ans=0;
	rep(c,0,D) {
		ans+=dp[cur^1][n][n][c];
		ans+= ans>=MOD ? -MOD:0;
	}
	printf("%d\n",ans);
}

int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int T;cin>>T;
	while(T--) solve();
	return 0;
}

