#include<bits/stdc++.h>
using namespace std;
#define pc(x) putchar(x)
namespace ib {char b[100];}
inline void pi(int x){
	if(x==0) {pc(48); return;}
	if(x<0) {pc('-'); x=-x;}
	char *s=ib::b;
	while(x) *(++s)=x%10,x/=10;
	while(s!=ib::b) pc((*(s--))+48);
}
inline void ri(int &x){
	x=0; static char c; bool t(0);
	while(c=getchar(),c<'0'||c>'9') if(c=='-') t=1; else t=0;
	do x=(x<<1)+(x<<3)+c-'0'; while(c=getchar(),c>='0'&&c<='9');
	if(t) x=-x;
}
const int N=5;
int A[N][N],B[N][N],xh[N][N],ans[5],P;
inline bool pd(int a,int b,int c){
	int s1=(A[1][2]+A[2][3]+A[3][1])%P; //cout<<s1<<endl;
	int s2=(B[1][2]*a+B[2][3]*b+B[3][1]*c)%P;
	if(s1<0) s1+=P; if(s2<0) s2+=P; 
	if(s1==s2) return 1; else return 0;
}
int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout); 
	int i,j,k,n,m,x,y,a,b;
	ri(n); ri(m); ri(P);
	for(i=0;i<m;++i){
		ri(x); ri(y); ri(a); ri(b);
		xh[x][y]=i+1; 
		A[x][y]=a; A[y][x]=-a;
		B[x][y]=b; B[y][x]=-b;
	}
	//cout<<A[1][2]<<' '<<A[2][3]<<' '<<A[3][1]<<endl; 
	for(i=0;i<P;++i)
	if(pd(i,i,i)){
		if(xh[1][2]) ans[xh[1][2]]=i;
		else ans[xh[2][1]]=-i;
		if(xh[1][3]) ans[xh[1][3]]=i;
		else ans[xh[3][1]]=-i;
		if(xh[2][3]) ans[xh[2][3]]=i;
		else ans[xh[3][2]]=-i;
		break;
	}
	//cout<<i<<' '<<j<<' '<<k<<endl; 
	for(i=1;i<=3;++i) cout<<(ans[i]+P)%P<<endl;
	return 0;
}

