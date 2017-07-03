#include<cmath>
#include<cctype>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define lol long long
#define ns namespace
using ns std;
const int M = 111,N=2333;
int n,m;
lol p;
lol a[M][M],b[M][M],c[M][M];
int x[N],y[N];
int main()
{
#ifdef shorn

#else
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
#endif
	cin >> n >> m >> p;
	for(int i=1;i<=m;i++)
	{
		
		lol aa,bb;
		cin >> x[i] >> y[i] >> aa >> bb;
		a[x[i]][y[i]] = aa;
		b[x[i]][y[i]] = bb;
		a[y[i]][x[i]] = -aa;
		b[y[i]][x[i]] = bb;
	}
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<p;j++)
		{
			for(int k=0;k<p;k++)
			{
				c[1][2] = i;c[2][1] = -i;
				c[2][3] = j;c[3][2] = -j;
				c[1][3] = k;c[3][1] = -k;
				lol s1=0LL,s2=0LL;
				s1 =( ((b[1][2] * c[1][2])%p + (b[2][3] * c[2][3]) % p + (b[3][1] * c[3][1]) % p) % p + 3 * p) % p;
				s2 = ((a[1][2] + a[2][3] + a[3][1]) % p + 3 * p) % p;
				if(s1==s2)
				{
					for(int i=1;i<=m;i++)
					{
						cout << (c[x[i]][y[i]] % p + 3 * p) % p << endl;
					}
					return 0;
				}
			}
		}
	}
	return 0;
}
