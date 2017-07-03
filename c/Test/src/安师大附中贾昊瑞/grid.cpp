#include"bits/stdc++.h"
#define F(i,j,n) for(register int i=j;i<=n;i++)
#define D(i,j,n) for(register int i=j;i>=n;i--)
#define ll long long
#define N 55
#define M 200010
#define S (t&1)
#define T (!(t&1))
using namespace std;
void in(int&a);void in(ll&a);
int f[2][N][N][N],a[N][N],t,n,m,c,d,p,s[M],o[M],tot;
void add(int &x,int y){x=(x+y)%p;}
int C(int n,int m){
	if(n<0||m<0)return 0;
//	printf("%d %d ",n,m);
	F(i,1,n+m)s[i]=0;
	int x;
	F(i,1,n){
		x=n+m+1-i;while(x!=1){s[o[x]]++;x/=o[x];}
		x=i;while(x!=1){s[o[x]]--;x/=o[x];}
	}
	x=1;
	F(i,1,n+m)while(s[i])s[i]--,x=(ll)x*i%p;
//	printf("%d\n",x);
	return x;
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("grid.in","r",stdin);
	freopen("grid.out","w",stdout);
	#endif
	F(i,2,M-10){
		if(!o[i]){o[i]=i;s[++tot]=i;}
		F(j,1,tot){
			if(i*s[j]>M-10)break;
			o[i*s[j]]=s[j];
			if(i%s[j]==0)break;
		}
	}
	in(t);
	while(t--){
		in(n);in(m);in(c);in(d);in(p);
		//*
		if(n<=50&&m<=50){
			int j,l,x;
			memset(f[1],0,sizeof(f[1]));
			memset(a,0,sizeof(a));
			F(i,1,c)in(j),in(l),a[j][l]=1;
			f[1][1][2][a[1][2]+a[2][1]]=1;
			F(t,3,n+m-1){
				memset(f[T],0,sizeof(f[T]));
				F(i,max(1,t-m),min(t-1,n))
					F(k,i+1,min(t-1,n)){
						j=t-i;l=t-k;
						F(x,a[i][j]+a[k][l],d)if(f[S][i][k][x]){
//							printf("(%d %d) (%d %d) %d %d\n",i,j,k,l,x,f[S][i][k][x]);
							if(i+1!=k)add(f[T][i+1][k][x+a[i+1][j]+a[k][l+1]],f[S][i][k][x]);
							if(k!=n)add(f[T][i+1][k+1][x+a[i+1][j]+a[k+1][l]],f[S][i][k][x]);
							if(j!=m)add(f[T][i][k][x+a[i][j+1]+a[k][l+1]],f[S][i][k][x]);
							if(k!=n&&j!=m)add(f[T][i][k+1][x+a[i][j+1]+a[k+1][l]],f[S][i][k][x]);
						}
					}
			}
			x=0;
			F(i,0,d)add(x,f[!(n+m&1)][n-1][n][i]);
			printf("%d\n",x);
			continue;
		}//*/
		if(!c){int x=C(n-2,m-2);x=(ll)x*x%p;printf("%lld\n",(x-(ll)C(n-1,m-3)*C(n-3,m-1)%p+p)%p);continue;}
	}
	
	return 0;
}
void in(ll&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=0;c=getchar();}if(y)a=-a;}
void in(int&a){register char c;register bool y=false;c=getchar();a=0;
while(c<'0'||c>'9'){if(c=='-'){c=getchar();y=true;break;}c=getchar();}
while(c>='0'&&c<='9'){a=(a<<3)+(a<<1)+c-'0';c=0;c=getchar();}if(y)a=-a;}

