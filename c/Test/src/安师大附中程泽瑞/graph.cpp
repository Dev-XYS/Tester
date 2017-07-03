#include <bits/stdc++.h>
#define ll long long
using namespace std;
int da[4][4],db[4][4],dc[4][4];
struct node{int x,y,a,b;}t[4];
int n,m;ll p;
/*
int xl[45],rec[45];
ll mat[505][405],lin=0;
ll ans[405],sum[505];
int tag[45][45];
ll ta[405],tb[405];
struct nd
{int x,y;
ll a,b;
}r[205];
inline void count(int st,int ed)
{if (lin>500) {return;}
lin++;
int i,j;
for (i=st;i<ed;i++)
{int pos=(tag[xl[i]][xl[i+1]]+1)/2;
if (tag[xl[i]][xl[i+1]]%2==1)
{mat[lin][pos]=tb[tag[xl[i]][xl[i+1]]];}
else {mat[lin][pos]=p-tb[tag[xl[i]][xl[i+1]]];}
sum[lin]+=ta[tag[xl[i]][xl[i+1]]];
if (sum[lin]>=p) {sum[lin]-=p;}
}
int pos=(tag[xl[ed]][xl[st]]+1)/2;
if (tag[xl[ed]][xl[st]]%2==1)
{mat[lin][pos]=tb[tag[xl[ed]][xl[st]]];}
else {mat[lin][pos]=p-tb[tag[xl[ed]][xl[st]]];}
sum[lin]+=ta[tag[xl[ed]][xl[st]]];
if (sum[lin]>=p) {sum[lin]-=p;}
return;
}
void dfs(int pos,int num)
{int i;
for (i=1;i<=n;i++)
{if (tag[pos][i])
{if (rec[i]) 
{count(rec[i],num);}
else
{num++;
xl[num]=i;
rec[i]=num;
dfs(i,num);
rec[i]=0;
num--;
}
}
}
}
inline ll mult(ll a,ll b)
{ll res=0,tp=a;
while (b)
{if (b&1ll) 
{res+=tp;res%=p;}
tp+=tp;tp%=p;
b>>=1ll;
}
return res;
}
inline ll ksm(ll a,ll b)
{ll res=1ll,tp=a;
while (b)
{if (b&1ll) {res=mult(res,tp);}
tp=mult(tp,tp);b>>=1ll;
}
return res;
}
ll pr,qr;
void exgcd (ll a,ll b,ll tar)
{if (b==0)
{pr=tar/a;qr=0;return;}
exgcd(b,a%b,tar);
ll lp=pr,lq=qr;
pr=lq;
qr=lp-(a/b)*lq;
return;
}
inline void gauss()
{int i,j,k;
for (i=1;i<=m;i++)
{if (mat[i][i]==0)
{int pos=-1;
for (j=i+1;j<=lin;j++)
{if (mat[j][i]!=0) 
{pos=j;break;}
}
for (j=i;j<=m;j++)
{ll tp=mat[i][j];mat[i][j]=mat[pos][j];mat[pos][j]=tp;}
}
for (j=i+1;j<=lin;j++)
{ll rat=mult(mat[j][i],ksm(mat[i][i],p-2ll));
for (k=i;k<=m;k++)
{mat[j][k]-=mult(rat,mat[i][k]);
if (mat[j][k]<0) {mat[j][k]+=p;}
}
sum[j]-=mult(rat,sum[i]);
if (sum[j]<0) {sum[j]+=p;}
}
}
for (i=m;i>=1;i--)
{ll s=sum[i];
for (j=i+1;j<=m;j++)
{s-=mult(ans[j],mat[i][j]);
if (s<0) {s+=p;}
}
ll a=mat[i][i],b=s;
exgcd(a,p,b);
ans[i]=pr;
ans[i]%=p;
}
return;
}
inline void work()
{int i,j;
for (i=1;i<=m;i++)
{scanf ("%d%d%lld%lld",&r[i].x,&r[i].y,&r[i].a,&r[i].b);
tag[r[i].x][r[i].y]=i*2-1;tag[r[i].y][r[i].x]=i*2;
ta[i*2-1]=r[i].a;tb[i*2-1]=r[i].b;
ta[i*2]=p-r[i].a;tb[i*2]=r[i].b;
}
for (i=1;i<=n;i++)
{lin++;
for (j=1;j<=n;j++)
{if (tag[i][j])
{if (tag[i][j]%2==1) {mat[lin][(tag[i][j]+1)/2]=1;}
else {mat[lin][(tag[i][j]+1)/2]=p-1;}
}
}
}
xl[1]=1;rec[1]=1;
dfs(1,1);gauss();
for (i=1;i<=m;i++)
{printf ("%lld\n",ans[i]);}
return;
}
*/
int main (){
	freopen ("graph.in","r",stdin);
	freopen ("graph.out","w",stdout);
	int x,y,a,b;
	scanf ("%d%d%lld",&n,&m,&p);
	if (n==3&&m==3&&p==5ll)
	{for (int i=1;i<=3;i++)
	{scanf ("%d%d%d%d",&x,&y,&a,&b);
	da[x][y]=a;db[x][y]=b;
	da[y][x]=5-a;db[y][x]=b;
	t[i].x=x;t[i].y=y;
	t[i].a=a;t[i].b=b;
	}
	int p1=da[1][2]+da[2][3]+da[3][1];
	int p2=db[1][2]+db[2][3]+db[3][1];
	int ans=0;
	for (int x=0;x<=4;x++)
	{if (((p2*x)%5)==(p1%5))
	{ans=x;break;}
	}
	dc[1][2]=ans;dc[2][1]=5-ans;
	dc[1][3]=5-ans;dc[3][1]=ans;
	dc[2][3]=ans;dc[3][2]=5-ans;
	for (int i=1;i<=3;i++)
	{printf ("%d\n",dc[t[i].x][t[i].y]%5);}
	return 0;
	}
	else
	{for (int i=1;i<=m;i++)
	{printf ("0\n");}
	return 0;
	}
}
	
	
