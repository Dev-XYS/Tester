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
int f[105][55][55][55],n,m,C,D,mod;
bool b[55][55];
inline void R(int&x,int y){x+=y;x>=mod?x-=mod:0;}
void BlSolve()
{
    memset(f,0,sizeof(f));
    memset(b,0,sizeof(b));
    for(int i=1,j;i<=C;++i) j=read(),b[j][read()]=1;
    f[3][2][1][b[1][2]+b[2][1]]=1%mod;
    for(int i=3;i<n+m;++i)
        for(int j=1;j<i&&j<=n;++j)if(i-j<=m)
            for(int k=1;k<j;++k)if(i-k<=m)
                for(int l=0;l<=D;++l)
                {
                    int V=f[i][j][k][l];
                    if(j<n&&i-k<m)  R(f[i+1][j+1][k][l+b[j+1][i-j]+b[k][i-k+1]],V);
                    if(j<n&&k<n)    R(f[i+1][j+1][k+1][l+b[j+1][i-j]+b[k+1][i-k]],V);
                    if(i-j<m&&k<j-1)R(f[i+1][j][k+1][l+b[j][i-j+1]+b[k+1][i-k]],V);
                    if(i-j<m&&i-k<m)R(f[i+1][j][k][l+b[j][i-j+1]+b[k][i-k+1]],V);
                 //   cout<<i<<" "<<j<<" "<<k<<" "<<l<<" "<<f[i][j][k][l]<<endl;
                }
    int ans=0;
    for(int i=0;i<=D;++i)R(ans,f[n+m-1][n][n-1][i]);
    printf("%d\n",ans);
}

int main()
{
    freopen("grid.in","r",stdin);
    freopen("grid.out","w",stdout);
    for(int T=read();T;--T)
    {
        n=read();m=read();C=read();D=read();mod=read();
        if(n<=50&&m<=50&&C<=50)
            BlSolve();
        else for(int i=1;i<=C;++i) read(),read();
    }
    return 0;
}
