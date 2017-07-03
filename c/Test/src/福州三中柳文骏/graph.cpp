#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<map>
#include<set>
#include<ctime>
#include<queue>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>

#define open(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout)
#define LL long long
#define _max(a,b) ((a)>(b)?(a):(b))
#define _min(a,b) ((a)<(b)?(a):(b))
#define M 4

using namespace std;
template<class T>
inline void read(T& x)
{
    bool f=false;char ch=getchar();x=0;
    while(ch<48)f=(ch=='-'),ch=getchar();
    while(47<ch)x=(x<<3)+(x<<1)+ch-48,ch=getchar();
    if(f)x=-x;
}
int n,m,p;
int a[M],b[M],c[M];
int ix[M],iy[M];
bool z(int x)
{
	return !(x%p);
}
int main()
{
	open(graph);
	read(n),read(m),read(p);
	for(int i=1,x,y,aa,bb;i<=m;++i)
	{
		read(x),read(y),read(aa),read(bb);
		ix[i]=x;iy[i]=y;
		if(x>y)swap(x,y),aa*=-1;
		if(x+1 == y)a[x]=aa,b[x]=bb;
		else a[y]=-aa,b[y]=bb;
	}
	for(int i=0;i<=4;++i)
		for(int j=0;j<=4;++j)
			for(int k=0;k<=4;++k)
			{
				if(z(i-k) && z(j-i) && z(k-j) && (b[1]*i+b[2]*j+b[3]*k)%p == (a[1]+a[2]+a[3])%p)
				{
					c[1]=i;c[2]=j;c[3]=k;goto a;
				}
			}
	a:
	for(int i=1;i<=m;++i)
	{
		int out=1;
		if(ix[i] > iy[i])out*=-1,swap(ix[i],iy[i]);
		if(ix[i]+1 == iy[i])out*=c[ix[i]];
		else out*=-c[iy[i]];
		printf("%d\n",out);
	}
	return 0;
}
/*
3 3 5
1 2 1 1   
2 3 1 1   
3 1 2 4    
*/ 
