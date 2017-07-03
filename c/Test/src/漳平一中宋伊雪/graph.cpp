#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<stack>
#include<bitset>
using namespace std;

const int N = 105;
const int M = 2002;
typedef long long LL;

#define swap(x,y) ((x) ^= (y),(y) ^= (x),(x) ^= (y))

struct E{
	LL a,b,c; int to,Num; E(){}
	E(LL a,LL b,LL c,int to,int Num):
		a(a),b(b),c(c),to(to),Num(Num){}
}edgs[M*2];

int n,m,cnt,tot,fa[N],L[N];
LL p,A[M+N][M],B[M+N];

bool vis[N];

vector <int> v[N];

inline LL getLL()
{
	char ch = getchar(); LL ret = 0;
	while (ch < '0' || '9' < ch) ch = getchar();
	while ('0' <= ch && ch <= '9')
		ret = ret * 10LL + 1LL * (ch - '0'),ch = getchar();
	return ret;
}

char s[20];
inline void Print(LL x)
{
	if (!x) {puts("0"); return;} int len = 0;
	while (x) s[++len] = x % 10LL,x /= 10LL;
	for (int i = len; i; i--) putchar(s[i] + '0'); puts("");
}

inline void Add(int x,int y,LL a,LL b,int I)
{
	v[x].push_back(tot); edgs[tot++] = E(a,b,1,y,I);
	v[y].push_back(tot); edgs[tot++] = E(p - a,b,p - 1LL,x,I);	
}

inline void Inc(LL &x,const LL &y)
{
	x += y; x = x < p ? x : x - p;
}

inline void Dec(LL &x,const LL &y)
{
	x -= y; x = x < 0 ? x + p : x;
}

inline LL Mul(LL x,LL y)
{
	if (x < y) swap(x,y); LL ret = 0;
	for (; y; y >>= 1LL)
	{
		if (y & 1LL) Inc(ret,x);
		Inc(x,x);
	}
	return ret;
}

inline void Dfs(int x,int from)
{
	vis[x] = 1;
	for (int i = 0; i < v[x].size(); i++)
	{
		E e = edgs[v[x][i]]; if (e.to == from) continue;
		if (!vis[e.to]) fa[e.to] = v[x][i],L[e.to] = L[x] + 1,Dfs(e.to,x);
		else if (L[e.to] < L[x])
		{
			++cnt; Inc(B[cnt],e.a);
			Inc(A[cnt][e.Num],Mul(e.b,e.c));
			for (int z = x; z != e.to; z = edgs[fa[z]^1].to)
			{
				E _e = edgs[fa[z]]; Inc(B[cnt],_e.a);
				Inc(A[cnt][_e.Num],Mul(_e.b,_e.c));
			}
		}
	}
}

inline LL ksm(LL x,LL y)
{
	LL ret = 1;
	for (; y; y >>= 1LL)
	{
		if (y & 1LL) ret = Mul(ret,x);
		x = Mul(x,x);
	}
	return ret;
}

inline void Swap(int x,int y)
{
	for (int i = x; i <= m; i++) swap(A[x][i],A[y][i]); swap(B[x],B[y]);
}

inline void Gauss(int k)
{
	if (k > m) return;
	if (!A[k][k])
	{
		for (int i = k + 1; i <= cnt; i++)
			if (A[i][k]) {Swap(k,i); break;}
	}
	LL Inv = ksm(A[k][k],p - 2LL); B[k] = Mul(B[k],Inv);
	for (int i = k; i <= m; i++) A[k][i] = Mul(A[k][i],Inv);
	for (int i = k + 1; i <= cnt; i++)
	{
		if (!A[i][k]) continue;
		LL tmp = A[i][k]; Dec(B[i],Mul(tmp,B[k]));
		for (int j = k; j <= m; j++) Dec(A[i][j],Mul(A[k][j],tmp));
	}
	Gauss(k + 1);
	for (int i = k + 1; i <= m; i++) Dec(B[k],Mul(B[i],A[k][i]));
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
		freopen("test.txt","w",stdout);
	#else
		freopen("graph.in","r",stdin);
		freopen("graph.out","w",stdout);
	#endif
	
	cin >> n >> m >> p; cnt = n;
	for (int i = 1; i <= m; i++)
	{
		int x = getLL(),y = getLL();
		LL a = getLL(),b = getLL(); Add(x,y,a,b,i);
	}
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < v[i].size(); j++)
		{
			E e = edgs[v[i][j]];
			A[i][e.Num] = e.c;
		}
	L[1] = 1; Dfs(1,0); Gauss(1);
	for (int i = 1; i <= m; i++) Print(B[i]);
	return 0;
}
