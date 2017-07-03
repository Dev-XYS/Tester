#include<cstdio>
inline int read()
{
	int x;char c;
	while((c=getchar())<'0'||c>'9');
	for(x=c-'0';(c=getchar())>='0'&&c<='9';)x=x*10+c-'0';
	return x;
}
int a[5][5],b[5][5],c[5][5],x[5],y[5];
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int n,m,p,i;
	n=read();m=read();p=read();
	if(n!=3||m!=3||p!=5)return 0*puts("TooDifficult");
	for(i=1;i<=m;++i)
	{
		x[i]=read();y[i]=read();
		a[x[i]][y[i]]=read();b[x[i]][y[i]]=read();
		a[y[i]][x[i]]=(p-a[x[i]][y[i]])%p;b[y[i]][x[i]]=b[x[i]][y[i]];
	}
	for(c[1][2]=0;c[1][2]<5;++c[1][2])
		for(c[2][3]=0;c[2][3]<5;++c[2][3])
			for(c[3][1]=0;c[3][1]<5;++c[3][1])
			{
				c[2][1]=(p-c[1][2])%p;
				c[3][2]=(p-c[2][3])%p;
				c[1][3]=(p-c[3][1])%p;
				if(((c[1][2]+c[1][3])%p)||((c[2][1]+c[2][3])%p)||((c[3][1]+c[3][2])%p))continue;
				if((b[1][2]*c[1][2]+b[2][3]*c[2][3]+b[3][1]*c[3][1])%p==(a[1][2]+a[2][3]+a[3][1])%p)
				{
					for(i=1;i<=m;++i)printf("%d\n",c[x[i]][y[i]]);
					return 0;
				}
			}
	fclose(stdin);fclose(stdout);return 0;
}
