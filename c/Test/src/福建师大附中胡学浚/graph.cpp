#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,P,x[10],y[10],a[10],b[10],d[10];
int head[10],cnt=0,C[10][10];
struct edge{int to,next,a,b;}e[150123];
bool inq[10],flag;
inline void ins(int f,int t,int a,int b)
{
    e[++cnt]=(edge){t,head[f],a,b};head[f]=cnt;
}
void dfs(int now,int s,int y)
{
    inq[now]=1;
    for(int i=head[now];i;i=e[i].next)
        if(!inq[e[i].to])
            dfs(e[i].to,s+e[i].b*C[now][e[i].to],y+e[i].a);
        else
        {
            int ss=s+e[i].b*C[now][e[i].to],yy=y+e[i].a;
            if(ss%P!=yy%P) flag=false;
        }
    inq[now]=0;
}

bool Check(int a1,int a2,int a3)
{
    d[1]=d[2]=d[3]=0;
    d[x[1]]+=a1;d[y[1]]+=5-a1;
    d[x[2]]+=a2;d[y[2]]+=5-a2;
    d[x[3]]+=a3;d[y[3]]+=5-a3;
    if(d[1]%5!=0||d[2]%5!=0||d[3]%5!=0) return false;
    C[x[1]][y[1]]=a1;C[y[1]][x[1]]=5-a1;
    C[x[2]][y[2]]=a2;C[y[2]][x[2]]=5-a2;
    C[x[3]][y[3]]=a3;C[y[3]][x[3]]=5-a3;
    flag=1;dfs(1,0,0);dfs(2,0,0);dfs(3,0,0);
    return flag;
}

int main()
{
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    n=read();m=read();P=read();
    if(n>3||m>3||P>5) return 0*puts("ditolyAK");
    for(int i=1;i<=m;++i)
    {
        x[i]=read();y[i]=read();
        a[i]=read()%P;b[i]=read()%P;
        ins(x[i],y[i],a[i],b[i]);
        ins(y[i],x[i],5-a[i],b[i]);
    }
    for(int i=0;i<5;++i)
        for(int j=0;j<5;++j)
            for(int k=0;k<5;++k)
                if(Check(i,j,k))
                    return 0*printf("%d %d %d\n",i,j,k);
    return 0;
}
