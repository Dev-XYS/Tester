#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n,m,p;
void solve1();
int power(int x,int y,int z){
	int ans = 1;
	while (y){
		if (y&1) ans = (ll)ans*x%z;
		x = (ll)x*x%z;
		y >>= 1;
	}
	return ans;
}
int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d%d%d",&n,&m,&p);
	if (n == 3) solve1();
	return 0;
}
void solve1(){
	int x,y,a,b,sa = 0,sb = 0;
	int tip[4];
	for (int i = 1;i <= 3;i++) {
		scanf("%d%d%d%d",&x,&y,&a,&b);
		sb += b;
		if (x+y == 4){
			if (x < y) {sa -= a;tip[i] = -1;}
			else {tip[i] = 1;sa += a;}
		}
		else{
			if (x < y) {tip[i] = 1;sa += a;}
			else {tip[i] = -1;sa -= a;}
		}
	}
	int ans = (ll)sa*power(sb,p-2,p)%p;
	for (int i = 1;i <= 3;i++) 
		if (tip[i] == 1) printf("%d\n",ans);
		else printf("%d\n",(p-ans)%p);
}
