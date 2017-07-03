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

const int N = 55;
const int dx[2] = {0,1};
const int dy[2] = {1,0};

struct Point{
	int x,y; Point(){}
	Point(int x,int y): x(x),y(y){}
};

struct data{
	Point a,b; int Num; data(){}
	data(Point a,Point b,int Num): a(a),b(b),Num(Num){}
};

int n,m,p,c,d,f[N][N][N],g[N][N][N];
bool vis[N][N],inq[N][N][N];

queue <data> Q;

inline void Add(int &x,const int &y)
{
	x += y; x = x < p ? x : x - p;
}

void Solve()
{
	cin >> n >> m >> c >> d >> p;
	for (int i = 1; i <= c; i++)
	{
		int x,y; scanf("%d%d",&x,&y);
		vis[x][y] = 1;
	}
	int M = n + m - 2,cur = 0,Ans = 0;
	f[1][1][0] = 1; Q.push(data(Point(1,1),Point(1,1),0));
	while (!Q.empty())
	{
		data k = Q.front(); Q.pop();
		if (k.a.x + k.a.y - 2 > cur)
			++cur,memcpy(f,g,sizeof(g)),memset(g,0,sizeof(g)),memset(inq,0,sizeof(inq));
		if (cur == M - 1) {Add(Ans,f[k.a.x][k.b.x][k.Num]); continue;}
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
			{
				int xa = k.a.x + dx[i],ya = k.a.y + dy[i];
				int xb = k.b.x + dx[j],yb = k.b.y + dy[j];
				if (xa == xb && ya == yb) continue;
				if (xa < xb || xa > n || ya > m || xb > n || yb > m) continue;
				int Nex = k.Num + vis[xa][ya] + vis[xb][yb];
				if (Nex > d) continue; Add(g[xa][xb][Nex],f[k.a.x][k.b.x][k.Num]);
				if (!inq[xa][xb][Nex]) inq[xa][xb][Nex] = 1,Q.push(data(Point(xa,ya),Point(xb,yb),Nex));
			}
	}
	cout << Ans << endl;
	memset(f,0,sizeof(f)); memset(g,0,sizeof(g));
	memset(vis,0,sizeof(vis)); memset(inq,0,sizeof(inq));
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
	#else
		freopen("grid.in","r",stdin);
		freopen("grid.out","w",stdout);
	#endif
	
	int T; cin >> T;
	while (T--) Solve();
	return 0;
}
