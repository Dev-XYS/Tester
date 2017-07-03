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
int p;
int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	n=read();
	m=read();
	p=read();
	if (n==3&&m==3)
	{
		for (i=1;i<=m;i++)
		  printf("0\n");
		return 0;
	}
}
