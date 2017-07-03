#include<bits/stdc++.h>
using namespace std;
const int MAXN=2050;
int n,m,p,vis[MAXN];
vector< pair<int,int> > e[MAXN];
vector< pair<int,int> > a;
double mat[2050][2050];
int row,col;
void solve(){
	double x[2050];
	for(int i=0;i<col-2;i++){
		int k=i;
		double max=mat[k][i];
		for(int j=i+1;j<col-1;j++)if(abs(mat[j][i])>abs(mat[k][i])) max=mat[j][i],k=j;
		if(k!=i){
			for(int j=i;j<col;j++){
				double tmp=mat[k][j];
				mat[k][j]=mat[i][j];
				mat[i][j]=tmp;
			}
			for(int j=i+1;j<col-1;j++){
				double tmp=mat[j][i]/mat[i][i];
				for(int t=i+1;t<col;t++) mat[j][t]-=tmp*mat[i][t];
			}
		}
	}
	x[col-2]=mat[col-2][col-1]/mat[col-2][col-2];
	for(int i=col-3;i>=0;i--){
		for(int j=col-2;j>=i+1;j--) mat[i][col-1]-=x[j]*mat[i][j];
		x[i]=mat[i][col-1]/mat[i][i];
	}
}
int visnode[2050];
bool as;
void dfs(int u,int fa){
	for(vector< pair<int,int> >::iterator it=e[u].begin();it!=e[u].end();it++)
	if((*it).first!=fa){
		if(visnode[(*it).first]==1){
			as=1;return;
		}
		visnode[(*it).first]=1;
    	a.push_back(make_pair((*it).second,u));
		dfs((*it).first,u);
		if(as) return;
    	a.pop_back();
	}
}
int aa[2050],bb[2050],x[2050],y[2050];
int main(){
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&x[i],&y[i],&aa[i],&bb[i]);
		e[x[i]].push_back(make_pair(y[i],i));e[y[i]].push_back(make_pair(x[i],i));
	}
	for(int i=1;i<=m;i++)
	if(vis[i]==0){
		a.push_back(make_pair(i,x[i]));
		fill(visnode,visnode+m+3,0);
		visnode[x[i]]=1;visnode[y[i]]=1;as=0;
		dfs(x[i],y[i]);
		if(as)++row;
		int ans=0;
		for(vector< pair<int,int> >::iterator iter=a.begin();iter!=a.end()&&as;iter++){
			vis[(*iter).first]=1;
			mat[row-1][(*iter).first-1]=bb[(*iter).first];
			ans+=(*iter).second==x[i]?aa[(*iter).first]:-aa[(*iter).first];
		}
		if(as) mat[row][m]=ans;
	}
	for(int i=1;i<=n;i++){
		++row;
	}
	return 0;
}

