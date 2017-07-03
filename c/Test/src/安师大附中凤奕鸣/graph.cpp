#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct edge{
	   int u,v,p,a,b,c;
}e[100];
bool cherk(int n,int m,int p){
	 int s,i,j;
	 for (i=1;i<=n;i++){
	 	 s=0;
		 for (j=1;j<=m;j++){
			 if (e[j].u==i){
				s=(s+e[j].c)%p;
			 }
		 }
		 if (s!=0){
			return false;
		 }
	 }
	 s=0;
	 for (i=1;i<=n;i++){
		 for (j=1;j<=m;j++){
		 	 if (e[j].u%n+1==e[j].v){
			 	s=(s+e[j].b*e[j].c-e[j].a)%p;
             }
		 }
	 }
	 if (s!=0){
		return false;
	 }
	 s=0;
	 for (i=1;i<=n;i++){
		 for (j=1;j<=m;j++){
		 	 if (e[j].u%n+1!=e[j].v){
			 	s=(s+e[j].b*e[j].c-e[j].a)%p;
		 	 }
		 }
	 }
	 if (s!=0){
		return false;
	 }
	 return true;
}
int main(){
	int i,n,m,p,u,v,x,y;
	freopen ("graph.in","r",stdin);
	freopen ("graph.out","w",stdout);
	scanf ("%d%d%d",&n,&m,&p);
	for (i=1;i<=m;i++){
		scanf ("%d%d%d%d",&e[i].u,&e[i].v,&e[i].a,&e[i].b);
		e[i+m].u=e[i].v;
		e[i+m].v=e[i].u;
		e[i+m].a=-e[i].a;
		e[i+m].b=e[i].b;
	}
	for (e[1].c=0;e[1].c<p;e[1].c++){
		e[m+1].c=-e[1].c;
		for (e[2].c=0;e[2].c<p;e[2].c++){
			e[m+2].c=-e[2].c;
			for (e[3].c=0;e[3].c<p;e[3].c++){
				e[m+3].c=-e[3].c;
				if (cherk(n,m,p)){
				   printf ("%d\n%d\n%d\n",e[1].c,e[2].c,e[3].c);
				}
			}
		}
	}
	return 0;
}

