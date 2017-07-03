#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int map[4][4][4];

int main()
{
	freopen("graph.in", "r", stdin);
	freopen("graph.out", "w",stdout);
	int n, m, p;
	scanf("%d%d%d", &n, &m, &p);
	int u, v, a, b;
	int t[4][3],tot=0;
	for(int i=1; i<=3; i++)
	{
		scanf("%d%d%d%d", &u, &v, &a, &b);
		t[i-1][0]=u;
		t[i-1][1] =v;
		map[u][v][1] = a;
		map[v][u][1] = -a;
		map[u][v][2] = map[v][u][2] = b; 
	}
//	int tota=(map[1][2][1] + map[3][1][1] + map[2][3][1])%5;
//	int totb=(map[1][2][2] + map[3][1][2] + map[2][3][2])%5;
//	int totc = tota/totb%5;
	int t1, t2, t3;
	int flat = 0;
	//for(int i=0; i<=2; i++) cout<<t[i][0]<<' '<<t[i][1]<<endl;
	//cout<<totc<<endl;
	for(int c1=-5; c1<=5; c1++)
	{
		for(int c2 = -5; c2<=5; c2++)
		{
			if((c2 - c1)%5!=0) 
				continue;
			t1 = (c2-c1)/5;
			for(int c3 = -5; c3<=5;c3++)
			{
				if((c1+c3)%5!=0) continue;
				else t2 = (c1+c3)/5;
				if((-c3-c2)%5!=0) continue;
				else t3 = (-c3-c2)/5;
				if((t1+t2+t3)!=0)
					continue;
				int tmp1=map[3][1][1],tmp2=map[3][1][2]*c3+map[1][2][2]*c1 + map[2][3][2]*c2;
				for(int i=1;i<=n-1;i++)
					tmp1+=map[i][i+1][1];
				//
				if(tmp1==tmp2)
				{	
					//cout<<'1'<<endl;
					for(int i=0;i<=2;i++)
					{
						if(t[i][0]==1 && t[i][1]==2 || t[i][1]==1 && t[i][0] == 2)
							cout<<max(c1,-c1)<<endl;
						if(t[i][0]==3 && t[i][1]==2 || t[i][1]==3 && t[i][0] == 2)
							cout<<max(c2,-c2)<<endl;
						if(t[i][0]==3 && t[i][1]==1 || t[i][1]==3 && t[i][0] == 1)
							cout<<max(c3,-c3)<<endl;
					}
					return 0;
				}
			}
		}
	}
	return 0;
}
