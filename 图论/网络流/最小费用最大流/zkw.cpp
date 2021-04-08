#include<bits/stdc++.h>
using namespace std;
struct edge
{
	int v,cap,cost,rev;
	edge(int a,int b,int c,int d):v(a),cap(b),cost(c),rev(d){}
};
const int oo=1<<28;
vector<edge> w[23333];
void add_edge(int u,int v,int cap,int cost)
{
	w[u].emplace_back(v,cap,cost,w[v].size());
	w[v].emplace_back(u,0,-cost,w[u].size()-1);
}
int t,vis[23333],cost=0,dist=0,n;
int dfs(int u,int f)
{
	if(u==t){cost+=dist*f;return f;}
	vis[u]=1;
	int left=f;
	for(edge &e:w[u])
		if(e.cap&&!e.cost&&!vis[e.v])
		{
			int flow=dfs(e.v,min(left,e.cap));
			e.cap-=flow;
			w[e.v][e.rev].cap+=flow;
			left-=flow;
			if(!left)return f;
		}
	return f-left;
}
bool relabel()
{
	int d=oo;
	for(int i=1;i<=n;i++)
		if(vis[i])for(edge &j:w[i])
			if(j.cap&&!vis[j.v])d=min(d,j.cost);
	if(d==oo)return 0;
	for(int i=1;i<=n;i++)
		if(vis[i])for(edge &j:w[i])j.cost-=d,w[j.v][j.rev].cost+=d;
	dist+=d;
	return 1;
}
int main()
{
	int m,s;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	while(m--)
	{
		int a,b,cap,d;
		scanf("%d%d%d%d",&a,&b,&cap,&d);
		add_edge(a,b,cap,d);
	}
	int f=0;
	do for(;;)
		{
			memset(vis,0,sizeof vis);
			if(int flow=dfs(s,oo))f+=flow;
			else break;
		}
	while(relabel());
	printf("%d %d\n",f,cost);
	return 0;
}
