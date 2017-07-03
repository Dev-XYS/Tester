#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
int T,n,m,C,D,mod,ans,edge;
int siz[105];
int mp[55][55],sec[105][55];
int dp[105][55][55][55];
void sread()
{
	memset(dp,0,sizeof(dp));
	memset(mp,0,sizeof(mp));
	memset(sec,0,sizeof(sec));
	memset(siz,0,sizeof(siz));
	edge = ans = 0;
	scanf("%d%d%d%d%d",&n,&m,&C,&D,&mod);
	for (int i = 1;i <= C;i++)
	{
		int t_x,t_y;
		scanf("%d%d",&t_x,&t_y);
		mp[t_x][t_y] = 1;
	}
}
void sinit()
{
	int t_sec[105][55];
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m;j++)
		{
			int tp = i + j - 1;
			edge = max(tp,edge);
			t_sec[tp][++siz[tp]] = mp[i][j];
		}
	for (int i = 1;i <= n + m - 1;i++)
		for (int j = 1;j <= siz[i];j++)
			sec[i][j] = t_sec[i][siz[i] - j + 1];
}
void swork()
{
	if (n <= 1 || m <= 1)
	{
		printf("0\n");
		return;
	}
	dp[2][1][2][sec[2][1] + sec[2][2]] = 1;
	for (int i = 3;i <= n;i++)
	{
		for (int j = 1;j <= siz[i] - 1;j++)
		{
			for (int o = j + 1;o <= siz[i];o++)
			{
				for (int tc = 0;tc <= min(C,D);tc++)
				{
					if (tc - sec[i][j] - sec[i][o] < 0) continue;
					ll tot = 0;
					int t = tc - sec[i][j] - sec[i][o]; 
					if (j >= 2) tot += dp[i - 1][j - 1][o - 1][t];//左左 
					tot %= mod;
					if (j >= 2 && (o <= siz[i] - 1 || n > m)) tot += dp[i - 1][j - 1][o][t];//左上 
					tot %= mod;
					if (o <= siz[i] - 1 || n > m) tot += dp[i - 1][j][o][t];//上上 
					tot %= mod;
					if (o - j >= 2) tot += dp[i - 1][j][o - 1][t];//上左 
					tot %= mod;
					dp[i][j][o][tc] = (int)tot;
				}
			}
		}
	}
	for (int i = n + 1;i <= n + m - 2;i++)
	{
		for (int j = 1;j <= siz[i] - 1;j++)
		{
			for (int o = j + 1;o <= siz[i];o++)
			{
				for (int tc = 0;tc <= min(C,D);tc++)
				{
					if (tc - sec[i][j] - sec[i][o] < 0) continue;
					int t = tc - sec[i][j] - sec[i][o];
					ll tot = 0;
					tot += dp[i - 1][j][o][t];//左左 
					tot %= mod;
					tot += dp[i - 1][j + 1][o + 1][t];//上上 
					tot %= mod;
					tot += dp[i - 1][j][o + 1][t];//左上 
					tot %= mod;
					if (o - j >= 2) tot += dp[i - 1][j + 1][o][t];//上左 
					tot %= mod;
					dp[i][j][o][tc] = (int)tot; 
				}
			}
		}
	}
	for (int i = 0;i <= D;i++)
	{ 
		ans += dp[edge - 1][1][2][i];
		ans %= mod;
	} 
	printf("%d\n",ans);
}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	scanf("%d",&T);
	for (int mi = 1;mi <= T;mi++)
	{
		sread();
		sinit();
		swork();
	}
	return 0;
}
