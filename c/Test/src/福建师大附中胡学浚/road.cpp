#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
#define MN 500000
#define MD 18
#define ll long long
#define pa pair<ll,int>
#define mp(x,y) make_pair(x,y)
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll d[MN+5];bool vis[MN+5],b[MN+5];
int Best[MN+5],back[MN+5],dis[MN+5],front[MN+5],top[MN+5],Fa[MN+5],last=0;
int n,m,ty,Q,cnt=0,C,S,head[MN+5],semi[MN+5],idom[MN+5],dn=0,id[MN+5],s[MN+5];
int t[MN+5],p[MN+5],dfn[MN+5],T[MN+5],dep[MN+5],fa[MD+1][MN+5],c[MD+1][MN+5];
priority_queue<pa,vector<pa>,greater<pa> >q;
struct edge{int from,to,next,w;}e[MN*5+5];
inline void ins(int*H,int f,int t,int w){e[++cnt]=(edge){f,t,H[f],w};H[f]=cnt;}

void Dij()
{
    memset(d,42,sizeof(d));
    d[S]=0;q.push(mp(0,S));
    while(!q.empty())
    {
        while(!q.empty()&&q.top().first!=d[q.top().second]) q.pop();
        if(q.empty()) break;
        int x=q.top().second;q.pop();
        for(int i=head[x];i;i=e[i].next)
            if(d[x]+e[i].w<d[e[i].to])
            {
                d[e[i].to]=d[x]+e[i].w;
                q.push(mp(d[e[i].to],e[i].to));
            }
    }
}

void Pre(int x)
{
    id[dfn[x]=++dn]=x;
    for(int i=front[x];i;i=e[i].next)
        if(!dfn[e[i].to]) Fa[e[i].to]=x,Pre(e[i].to);
}

void Build()
{
    vis[S]=1;C=S;
    for(int i=2;i<=n;++i)
    {
        int Ch=0;
        for(int j=head[C];j;j=e[j].next)
            if(!vis[e[j].to]&&d[C]+e[j].w==d[e[j].to])
                if(!Ch||p[e[j].to]<p[Ch]) Ch=e[j].to;
        if(Ch) t[Ch]=C,C=Ch,vis[C]=1;
        else --i,C=t[C];
    }
    for(int i=1;i<=n;++i)
        for(int j=head[i];j;j=e[j].next)
            if(d[i]+e[j].w==d[e[j].to])
                ins(front,i,j+n,0),ins(front,j+n,e[j].to,0),
                ins(back ,j+n,i,0),ins(back ,e[j].to,j+n,0);
    Pre(S);
}
inline bool P(int x,int y){return dfn[x]<dfn[y];}
inline int Up(int x)
{
    if(s[x]==x) return x;
    int y=Up(s[x]);
    if(P(semi[Best[s[x]]],semi[Best[x]])) Best[x]=Best[s[x]];
    return s[x]=y;
}

void Build_Tree()
{
    for(int tt=dn;tt>1;--tt)
    {
        int u=id[tt];
        for(int i=back[u];i;i=e[i].next)
            if(dfn[e[i].to]) Up(e[i].to),
                P(semi[Best[e[i].to]],semi[u])?semi[u]=semi[Best[e[i].to]]:0;
        ins(top,semi[u],u,0);s[u]=Fa[u];u=Fa[u];
        for(int i=top[u];i;i=e[i].next)
        {
            Up(e[i].to);
            if(semi[Best[e[i].to]]==semi[u]) idom[e[i].to]=u;
            else idom[e[i].to]=Best[e[i].to];
        }
        top[u]=0;
    }
    for(int i=2;i<=dn;++i)
        if(semi[id[i]]!=idom[id[i]])
            idom[id[i]]=idom[idom[id[i]]];
}

void GetDep(int x)
{
    for(int i=T[x];i;i=e[i].next)
        dep[e[i].to]=dep[x]+1,GetDep(e[i].to);
}

inline int Get(int x){return dep[e[x].from]<dep[e[x].to]?e[x].from:e[x].to;}
int main()
{
    freopen("road.in","r",stdin);
    freopen("road.out","w",stdout);
    n=read();m=read();S=read();ty=read();
    for(int i=1;i<=n;++i) p[i]=read();
    for(int i=1;i<=m;++i)
    {
        int x=read(),y=read(),l=read();
        ins(head,x,y,l);
        ins(head,y,x,l);
    }
    Dij();Build();
    for(int i=1;i<=n+2*m;++i)
        s[i]=Best[i]=semi[i]=i;
    Build_Tree();
    for(int i=2;i<=n;++i) ins(T,t[i],i,0);
    GetDep(S);Q=read();
    for(int i=1;i<=n;++i)
        if(idom[i]>n) fa[0][i]=Get(idom[i]-n),c[0][i]=0;
        else fa[0][i]=idom[i],c[0][i]=dep[i]-dep[idom[i]];
    for(int i=1;i<=MD;++i)
        for(int j=1;j<=n;++j)
            fa[i][j]=fa[i-1][fa[i-1][j]],
            c[i][j]=c[i-1][j]+c[i-1][fa[i-1][j]];
    for(int i=1;i<=Q;++i)
    {
        int x=read(),y=read();
        if(ty) x^=last,y^=last;last=0;
        for(int j=MD;~j;--j)
            if(dep[fa[j][y]]>=dep[x])
                last+=c[j][y],y=fa[j][y];
        printf("%d\n",(last+=dep[y]-dep[x]));
    }
    return 0;
}
