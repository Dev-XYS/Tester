#include<cstdio>
#include<cctype>
#include<cstring>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<cmath>
#include<cstdlib>
#include<string>
#include<ctime>
#include<set>
#include<map>
#define bzs(x) for (int __bzsjbyt__=int((x)-1);__bzsjbyt__>=0;__bzsjbyt__--)
#define bzsi(x) for (unsigned i=0;i<unsigned(x);i++)
#define bzsj(x) for (unsigned j=0;j<unsigned(x);j++)
#define bzsk(x) for (unsigned k=0;k<unsigned(x);k++)
#define abzs(x,y) for (unsigned x=0;x<unsigned(y);x++)
#define dbzsi(x) for (int i=int(x)-1;i>=0;i--)
#define dbzsj(x) for (int j=int(x)-1;j>=0;j--)
#define dbzsk(x) for (int k=int(x)-1;k>=0;k--)
#define dabzs(x,y) for (int x=int(y)-1;x>=0;x--)
#define jqe(x) for (int __jqeisGqe__=int(x);__jqeisGqe__>=1;__jqeisGqe__--)
#define jqei(x) for (unsigned i=1;i<=unsigned(x);i++)
#define jqej(x) for (unsigned j=1;j<=unsigned(x);j++)
#define jqek(x) for (unsigned k=1;k<=unsigned(x);k++)
#define ajqe(x,y) for (unsigned x=1;x<=unsigned(y);x++)
#define djqei(x) for (unsigned i=unsigned(x);i>0;i--)
#define djqej(x) for (unsigned j=unsigned(x);j>0;j--)
#define djqek(x) for (unsigned k=unsigned(x);k>=0;k--)
#define dajqe(x,y) for (unsigned x=unsigned(y);x>0;x--)
#define bzsset(x) memset((x),0,sizeof (x))
#define bzsfla(x) memset((x),-1,sizeof (x))
#define bzsgra(x) for (edge *nd=head[x];nd;nd=nd->suc)
#define fi first
#define se second
#define mk std::make_pair
#define ded if(DEBUG)
#define enter ded printf("\n")
#define oo ((1<<31)-1)
#define lowoo ((1<<30)-1)
#define leroo ((1<<15))
#define lloo ((1<<63)-1)
#define FIO(x) freopen("x.in","r",stdin),freopen("x.out","w",stdout);
//define
int DEBUG;
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<deque>
#include<stack>
#include<set>
#include<map>
#include<cmath>
#include<ctime>
namespace bzs
{
    using namespace std;
    int read(char &x)
    {
	return scanf("%c",&x);
    }
    int read(char *x)
    {
	return scanf("%c",x);
    }
    int read(int &x)
    {
	return scanf("%d",&x);
    }
    int read(int *x)
    {
	return scanf("%d",x);
    }
    int getint()
    {
	int t;
	if (read(t)<0)
	{
	    puts("input failed");
	    return -2147483648;
	}
	return t;
    }
    int read(long long &x)
    {
	return scanf("%lld",&x);
    }
    int read(long long *x)
    {
	return scanf("%lld",x);
    }
    template<class T1,class T2>
    int read(T1 &x,T2 &y)
    {
	int t=read(x)+read(y);
	return t>=0?t:-1;
    }
    template<class T1,class T2,class T3>
    int read(T1 &u1,T2 &u2,T3 &u3)
    {
	int t=read(u1,u2)+read(u3);
	return t>=0?t:-1;
    }
    template<class T1,class T2,class T3,class T4>
    int read(T1 &u1,T2 &u2,T3 &u3,T4 &u4)
    {
	int t=read(u1,u2)+read(u3,u4);
	return t>=0?t:-1;
    }
    void readbzs(char *x,char *y)
    {
	fgets(x,int(y-x+1),stdin);
	return;
    }
    void readbzs(int *x,int *y)
    {
	if (x>y)
	{
	    return;
	}
	while(x!=y)
	{
	    read(x++);
	}
	return;
    }
    template<class t1,class t2>
    bool min_update(t1 &x,const t2 y)
    {
	if (x>y)
	{
	    x=y;
	    return 1;
	}
	return 0;
    }
    template<class t1,class t2>
    bool max_update(t1 &x,const t2 y)
    {
	if (x<y)
	{
	    x=y;
	    return 1;
	}
	return 0;
    }
    template<class t1,class t2>
    bool upper_update(t1 &x,const t2 y)
    {
	if (x<=y)
	{
	    x=y;
	    return 1;
	}
	return 0;
    }
    template<class t1,class t2>
    bool lower_update(t1 &x,const t2 y)
    {
	if (x>=y)
	{
	    x=y;
	    return 1;
	}
	return 0;
    }
    template<class T>
    void sort(vector<T> &x)
    {
	sort(x.begin(),x.end());
	return;
    }
    template<class T>
    T bzspop(queue<T> &x)
    {
	T t=x.front();
	x.pop();
	return t;
    }
    template<class T>
    T bzspop(stack<T> &x)
    {
	T t=x.top();
	x.pop();
	return t;
    }
    template<class T>
    T bzspop(vector<T> &x)
    {
	T t=x[x.size()-1];
	x.resize(x.size()-1);
	return t;
    }
    template<class T>
    T bzspop(priority_queue<T> &x)
    {
	T t=x.top();
	x.pop();
	return t;
    }
    void write(char x)
    {
	printf("%c",x);
	return;
    }
    void write(char *x)
    {
	printf("%s",x);
	return;
    }
    void write(int x)
    {
	printf("%d",x);
	return;
    }
    void write(int *x)
    {
	printf("%d",*x);
	return;
    }
    void write(unsigned x)
    {
	printf("%u",x);
	return;
    }
    void write(unsigned *x)
    {
	printf("%u",*x);
	return;
    }
    void write(unsigned long x)
    {
	printf("%lu",x);
	return;
    }
    void writeln(unsigned long *x)
    {
	printf("%lu",*x);
	return;
    }
    void write(double x)
    {
	printf("%lf",x);
	return;
    }
    void write(double *x)
    {
	printf("%lf",*x);
	return;
    }
    void write(long long &x)
    {
	printf("%lld",x);
	return;
    }
    void write(long long *x)
    {
	printf("%lld",*x);
	return;
    }
    void writebzs()
    {
	write(' ');
	return;
    }
    template<class t>
    void writebzs(t x)
    {
	write(x);
	write(' ');
	return;
    }
    template<class T1,class T2>
    void write(T1 x,T2 y)
    {
	writebzs(x);
	write(y);
	return;
    }
    template<class T1,class T2,class T3>
    void write(T1 x,T2 y,T3 z)
    {
	write(x,y);
	writebzs();
	write(z);
	return;
    }
    template<class T1,class T2,class T3,class T4>
    void write(T1 u1,T2 u2,T3 u3,T4 u4)
    {
	write(u1,u2);
	writebzs();
	write(u3,u4);
	return;
    }
    void writeln()
    {
	write('\n');
	return;
    }
    template<class t>
    void writeln(t x)
    {
	write(x);
	writeln();
	return;
    }
    template<class t1,class t2>
    void writeln(t1 u1,t2 u2)
    {
	write(u1,u2);
	writeln();
	return;
    }
    template<class t1,class t2,class t3>
    void writeln(t1 u1,t2 u2,t3 u3)
    {
	write(u1,u2,u3);
	writeln();
    }
    template<class t1,class t2,class t3,class t4>
    void writeln(t1 u1,t2 u2,t3 u3,t4 u4)
    {
	write(u1,u2,u3,u4);
	writeln();
    }
    template<class t>
    void writebzs(t *x,t *y)
    {
	if (x>y)
	{
	    return;
	}
	while(x<y-1)
	{
	    writeb(x++);
	}
	write(x);
	return;
    }
    template<class t>
    void writebzs(vector<t> x)
    {
	for (int i=0;i<x.size()-1;i++)
	{
	    writeb(x[i]);
	}
	write(x[x.size()-1]);
	return;
    }
    template<class t>void writebzs(stack<t> x)
    {
	if (x.empty())
	{
	    return;
	}
	while(x.size()>1)
	{
	    writeb(bzspop(x));
	}
	write(bzspop(x));
	return;
    }
    template<class t>
    void writebzsln(t *x,t *y)
    {
	if (x>y)
	{
	    return;
	}
	while(x<y-1)
	{
	    writeln(x++);
	}
	writeln(x);
	return;
    }
    template<class t>
    void writebzsln(vector<t> x)
    {
	for (int i=0;i<x.size();i++)
	{
	    writeln(x[i]);
	}
	return;
    }
    template<class t>
    void writebzsln(stack<t> x)
    {
	while(!x.empty())
	{
	    writeln(bzspop(x));
	}
	return;
    }
    template<class t>
    void writebzs(t **x,int r,int c)
    {
	for (int i=0;i<r;i++)
	{
	    writebzs(x[r],x[r]+c);
	    writeln();
	}
	return;
    }
    template<class t>
    t abs(t x)
    {
	return x<0?-x:x;
    }
    template<class t>
    void reverse(t *x,t *y)
    {
	if (x>=y) return;
	int k=(y-x)/sizeof *x;
	t temp[k];
	k=0;
	while(x!=y)
	{
	    temp[k++]=*(x++);
	}
	return;
    }
    template<class t>
    void reverse(vector<t> &x)
    {
	vector<t> temp;
	while(!x.empty())
	{
	    temp.push_back(bzspop(x));
	}
	x=temp;
	return;
    }
    template<class t>
    void reverse(stack<t> &x)
    {
	stack<t> temp;
	while(!x.empty())
	{
	    temp.push(bzspop(x));
	}
	x=temp;
	return;
    }
    char getbzs()
    {
	int t;
	do
	{
	    t=getchar();
	}
	while(t<33&&t>=0);
	if (t<0)
	{
	    puts("input failed");
	}
	return char(t);
    }
    vector<int> strvector(char* s)
    {
	unsigned l=unsigned(strlen(s));
	vector<int> t;
	t.clear();
	for (unsigned i=0;i<l;i++)
	{
	    t.push_back(s[i]);
	}
	return t;
    }
    template<class t>
    void random_shuffle(vector<t> &x)
    {
	random_shuffle(x.begin(),x.end());
    }
    template<class t>
    bool max_swap(t &u,t &v)
    {
	if (u<v)
	{
	    swap(u,v);
	    return 1;
	}
	return 0;
    }
    template<class t>
    bool min_swap(t &u,t &v)
    {
	if (u>v)
	{
	    swap(u,v);
	    return 1;
	}
	return 0;
    }
    template<class t>
    bool upper_swap(t &u,t &v)
    {
	if (u<=v)
	{
	    swap(u,v);
	    return 1;
	}
	return 0;
    }
    template<class t>
    bool lower_swap(t &u,t &v)
    {
	if (u>=v)
	{
	    swap(u,v);
	    return 1;
	}
	return 0;
    }
    template<class t>
    void bzs_shuffle(vector<t> &x)
    {
	srand(time(0));
	int n=x.size();
	vector<pair<int,int> > order;
	order.resize(n);
	for (int i=0;i<order.size();i++)
	    order[i]=make_pair(rand(),i);
	sort(order);
	vector<t> res;
	res.clear();
	for (int i=0;i<order.size();i++)
	    res.push_back(x[order[i].second]);
	x=res;
    }
    template<class t>
    bool swap(t &u,t &v,bool d)
    {
	if (d) std::swap(u,v);
	return d;
    }	
}
using namespace bzs;
//const
// const int MO=1000000007;
// const int N=00;
// const int M=00;
typedef long long lol;
typedef int type;
typedef const type &btype;
typedef const int &bint;
typedef const char &bchar;
typedef const float &bfloat;
typedef const double &bdouble;
typedef const lol &blol;
//struct
//variable
int n,m,T;
int p;
//function
int ksm(int u,int v)
{
    if (!v) return 1;
    if (v&1) return ksm(u*u%p,v>>1)*v%p;
    return ksm(u*u%p,v>>1);
}
//main
namespace brute
{
    const int N=5;
    int a[N][N];
    int b[N][N];
    int c[N][N];
    vector<pair<int,int> > query;
    void main()
    {
	bzsi(m)
	{
	    int u,v,_a,_b;
	    read(u,v,_a,_b);
	    a[u][v]=_a;
	    a[v][u]=-_a;
	    b[u][v]=_b;
	    b[v][u]=_b;
	    query.push_back(mk(u,v));
	}
	c[1][2]=(a[1][2]+a[2][3]+a[3][1])*ksm(b[1][2]+b[2][3]+b[3][1],p-2)%p;
	c[2][3]=c[1][2];
	c[3][1]=c[1][2];
	c[2][1]=-c[1][2];
	c[3][2]=c[2][1];
	c[1][3]=c[2][1];
	bzsi(query.size())
	    writeln(c[query[i].fi][query[i].se]);
    }
}
int main()
{
#ifdef BZSJBYT
    DEBUG=1;
    //prefer AD? jqe? cat? or female creeper?
#else
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
#endif
    read(n,m,p);
    if (n==3&&m==3) brute::main();
    return 0;
}
