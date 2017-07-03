#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define L long long
using namespace std;
int n,m,x[2010],y[2010];
L a[2010],b[2010],f[110][110],q;
inline L cheng(L a,L b)
{
    if(a<0)
      a+=q;
    if(b<0)
      b+=q;
    return (a*b-(L)(double(a)*b/q)*q)%q;
}
inline L power(L a,L b)
{
    if(!b)
      return 1;
    L c=power(a,b>>1);
    c=cheng(c,c);
    if(b&1)
      c=cheng(c,a);
    return c;
}
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	int i,j,k;
	L w;
	scanf("%d%d%lld",&n,&m,&q);
	for(i=1;i<=m;i++)
	  {
	   scanf("%d%d%lld%lld",&x[i],&y[i],&a[i],&b[i]);
	   w=power(b[i],q-2);
	   f[x[i]][y[i]]=(f[x[i]][y[i]]+w)%q;
	   f[x[i]][x[i]]=(f[x[i]][x[i]]-w)%q;
	   f[x[i]][n+1]=(f[x[i]][n+1]-cheng(a[i],w))%q;
	   f[y[i]][y[i]]=(f[y[i]][y[i]]-w)%q;
	   f[y[i]][x[i]]=(f[y[i]][x[i]]+w)%q;
	   f[y[i]][n+1]=(f[y[i]][n+1]+cheng(a[i],w))%q;
      }
    f[1][1]=1;
    for(i=2;i<=n+1;i++)
      f[1][i]=0;
    for(i=1;i<=n;i++)
      {
       for(j=i;j<=n;j++)
         if(f[j][i])
           break;
       if(j>i)
         for(k=i;k<=n+1;k++)
           swap(f[i][k],f[j][k]);
       w=power(f[i][i],q-2);
       for(j=i;j<=n+1;j++)
         f[i][j]=cheng(f[i][j],w);
       for(j=1;j<=n;j++)
         if(i!=j && f[j][i])
           for(k=n+1;k>=i;k--)
             f[j][k]=(f[j][k]-cheng(f[j][i],f[i][k]))%q;
      }
    for(i=1;i<=m;i++)
      {
       w=cheng((f[y[i]][n+1]-f[x[i]][n+1]+a[i])%q,power(b[i],q-2));
       w=(w+q)%q;
       printf("%lld\n",w);
      }
	return 0;
}

