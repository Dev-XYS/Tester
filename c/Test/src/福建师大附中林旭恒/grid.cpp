#include<cstdio>
#include<cstring>
inline int read()
{
	int x;char c;
	while((c=getchar())<'0'||c>'9');
	for(x=c-'0';(c=getchar())>='0'&&c<='9';)x=x*10+c-'0';
	return x;
}
#define MN 50
const int o[2][2]={{0,1},{1,0}};
int g[MN+5][MN+5],f[MN*2][MN+1][MN+1][MN+1],mod;
inline void rw(int&a,int b){a+=b;if(a>=mod)a-=mod;}
int main()
{
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	int T=read(),n,m,c,d,i,j,k,l,ans;
	while(T--)
	{
		n=read();m=read();c=read();d=read();mod=read();
		memset(g,0,sizeof(g));
		while(c--)i=read(),g[i][read()]=1;
		if(n>50||m>50||c>50){puts("TooDifficult");continue;}
		memset(f,0,sizeof(f));
		f[3][1][2][g[1][2]+g[2][1]]=1;
		for(i=3;i<n+m-1;++i)for(j=1;j<=n;++j)for(k=j;++k<=n;)for(l=0;l<=d;++l)if(f[i][j][k][l])
		{
			int x1=j,y1=i-j,x2=k,y2=i-k;
			for(int p1=0;p1<2;++p1)for(int p2=0;p2<2;++p2)
			{
				int xx1=x1+o[p1][0],yy1=y1+o[p1][1],
					xx2=x2+o[p2][0],yy2=y2+o[p2][1];
				if(xx1!=xx2)rw(f[i+1][xx1][xx2][l+g[xx1][yy1]+g[xx2][yy2]],f[i][j][k][l]);
			}
		}
		for(ans=i=0;i<=d;++i)rw(ans,f[n+m-1][n-1][n][i]);
		printf("%d\n",ans);
	}
	fclose(stdin);fclose(stdout);
}
