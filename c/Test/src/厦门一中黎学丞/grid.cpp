#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<map>
#include<ctime>
#define eps 1e-9
#define ll long long
#define N 2000000
#define inf 1000000000
#define mkp make_pair
using namespace std;
int i,j,k,m,n,s,t,mn;
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') {if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int f[105][52][52][55],mp[55][55],b1[10][10],k1,l1,l,mod,c,d,b[220],mx,x1,y1,x2,y2,p[100100],s1,s2,ans;
struct data{
	int x,y;
}a[110][110];
void add(int &x,int y)
{
	x+=y;
	if (x>=mod) x-=mod;
}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	b1[1][0]=1;
	b1[2][1]=1;
	int T=read();
	while (T--)
	{
		n=read();
		m=read();
		c=read();
		d=read();
		mod=read();
		if (n<=50&&m<=50)
		{
			memset(b,0,sizeof(b));
			memset(mp,0,sizeof(mp));
			memset(f,0,sizeof(f));
			memset(p,0,sizeof(p));
			for (i=1;i<=c;i++)
			{
				s=read();
				t=read();
				mp[s][t]=1;
			}
			for (i=1;i<=n;i++)
			  for (j=1;j<=m;j++)
			  {
			  	b[i+j-1]++;
			  	a[i+j-1][b[i+j-1]].x=i;
			  	a[i+j-1][b[i+j-1]].y=j;
			  	p[(i-1)*m+j]=b[i+j-1];
			  }
			f[1][1][1][0]=1;
			for (i=1;i<n+m-1;i++)
			{
				mx=b[i];
				for (j=1;j<=mx;j++)
				  for (k=j;k<=mx;k++)
				    for (l=0;l<=d;l++)
				    {
				  	 if (k==j&&i!=1) continue;
				  	 s=f[i][j][k][l];
					 if (!s) continue;
					 for (k1=1;k1<=2;k1++)
					   for (l1=1;l1<=2;l1++)
					   {
					   	 x1=a[i][j].x+b1[k1][0];
					   	 y1=a[i][j].y+b1[k1][1];
					   	 x2=a[i][k].x+b1[l1][0];
					   	 y2=a[i][k].y+b1[l1][1];
					   	 if (x1>n||y1>m||x2>n||y2>m) continue;
					   	 s1=p[(x1-1)*m+y1];
					   	 s2=p[(x2-1)*m+y2];
					   	 if (!s1||!s2) continue;
					   	 if (s1>s2) continue;
					   	 if (i!=n+m-2&&s1==s2) continue;
					   	 add(f[i+1][s1][s2][l+mp[x1][y1]+mp[x2][y2]],s);
					   }
				    }
			}
			ans=0;
			for (i=0;i<=d;i++)
			  add(ans,f[n+m-1][1][1][i]);
			printf("%d\n",ans);
			continue;
		}
	}
}
