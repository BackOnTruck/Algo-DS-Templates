#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
struct edge{int v;long long w;};
int n,m,dfn[300001],tot,f[19][300001],dep[300001];
long long dist[19][300001];
vector<edge> g[300001],w[300001];
void dfs(int u,int p,int d,long long dis)
{
	dep[u]=d;
	dfn[u]=++tot;
	f[0][u]=p;
	dist[0][u]=dis;
	for(edge e:g[u])
		if(e.v!=p)dfs(e.v,u,d+1,e.w);
}
int lca(int x,int y)
{
	if(dep[x]>dep[y])swap(x,y);
	for(int k=18;k>=0;k--)
		if(dep[y]-(1<<k)>=dep[x])y=f[k][y];
	for(int k=18;k>=0;k--)
		if(f[k][x]!=f[k][y])x=f[k][x],y=f[k][y];
	if(x!=y)x=f[0][x],y=f[0][y];
	return x;
}
void addedge(int x,int y)
{
	long long z=1<<30;
	int X=x,Y=y;
	if(dep[x]>dep[y])swap(x,y);
	for(int k=18;k>=0;k--)
		if(dep[y]-(1<<k)>=dep[x])z=min(z,dist[k][y]),y=f[k][y];
	if(dep[X]>dep[Y])swap(X,Y);
	w[X].push_back({Y,z});
}
long long dp(int u,long long prev)
{
	if(w[u].empty())return prev;
	long long sum=0;
	for(edge e:w[u])sum+=dp(e.v,e.w);
	w[u].clear();
	return min(sum,prev);
}
int k,q[300001],s[300001],top;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		g[x].push_back({y,z});
		g[y].push_back({x,z});
	}
	memset(dist,0x3f,sizeof dist);
	dfs(1,0,0,1ll<<60);
	for(int i=1;i<19;i++)
		for(int j=1;j<=n;j++)f[i][j]=f[i-1][f[i-1][j]],dist[i][j]=min(dist[i-1][j],dist[i-1][f[i-1][j]]);
	scanf("%d",&m);
	while(m--)
	{
		scanf("%d",&k);
		for(int i=1;i<=k;i++)scanf("%d",q+i);
		sort(q+1,q+1+k,[](const int &x,const int &y){return dfn[x]<dfn[y];});
		s[top=1]=1;
		for(int i=1;i<=k;i++)
		{
			if(top==1){s[++top]=q[i];continue;}
			int LCA=lca(q[i],s[top]);
			if(LCA==s[top])continue;
			while(top>1&&dfn[s[top-1]]>=dfn[LCA])addedge(s[top-1],s[top]),top--;
			if(LCA!=s[top])addedge(LCA,s[top]),s[top]=LCA;
			s[++top]=q[i];
		}
		while(top>1)addedge(s[top-1],s[top]),top--;
		printf("%lld\n",dp(1,1ll<<60));
	}
}
