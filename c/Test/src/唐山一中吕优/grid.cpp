#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int T,ans,mo,n,m,C,D;
bool flag[7][7],num[6][6];

int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	scanf("%d",&T);
	while (T--) 
	{
		scanf("%d%d%d%d%d",&n,&m,&C,&D,&mo);
		memset(flag,0,sizeof flag);ans=0;
		for (int i=1;i<=C;i++) 
		{
			int x,y;
			scanf("%d%d",&x,&y);
			flag[x][y]=1;
		}
		int r=1<<(n+m-2);
		for (int i1=0;i1<r;i1++) 
		{
			int cnt=0,x=1,y=1;
			bool pd=1;
			memset(num,0,sizeof num);
			for (int j=0;j<(n+m-2);j++)
			{
				if (i1&(1<<j)) x++;else y++;
				if (x>n||y>m) {pd=0;break;}
				if (flag[x][y]) cnt++;
				num[x][y]=1;
			}
			if (!pd) continue;
			num[n][m]=0;
			int tmp=cnt;
			for (int i2=0;i2<r;i2++) 
			{
				pd=1;x=1;y=1;cnt=tmp;
				for (int j=0;j<(n+m-2);j++)
				{
					if (i2&(1<<j)) x++;else y++;
					if (x>n||y>m||num[x][y]) {pd=0;break;}
					if (flag[x][y]) cnt++;
				}
				if (!pd) continue;
				if (cnt<=D) ans++;
			}
		}
		ans>>=1;ans%=mo;
		printf("%d\n",ans);
	}
	return 0;
}