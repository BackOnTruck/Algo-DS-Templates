#include<bits/stdc++.h>
using namespace std;
inline void update(int x,int &best,int &sec)
{
	if(x>best)sec=best,best=x;
	else if(x!=best&&x>sec)sec=x;
}
struct edge
{
	int u,v,w;
	bool operator<(const edge &e)const{return w<e.w;}
}e[410001];
int n,m,p[19][110001],f[110001],vis[410001],best[19][110001],sec[19][110001],dep[110001];
vector<edge> w[110001];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
void dfs(int u,int par,int prev)
{
	p[0][u]=par;
	best[0][u]=prev;
	dep[u]=dep[par]+1;
	for(edge x:w[u])
		if(x.v!=par)dfs(x.v,u,x.w);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+1+m);
	long long tot=0,ans=1ll<<60;
	for(int i=1;i<=m;i++)
	{
		int x=find(e[i].u),y=find(e[i].v);
		if(x!=y)
		{
			int u=e[i].u,v=e[i].v;
			tot+=e[i].w;vis[i]=1;f[x]=y;
			w[u].push_back(e[i]);
			swap(e[i].u,e[i].v);
			w[v].push_back(e[i]);
		}
	}
	memset(best,-1,sizeof best);
	memset(sec,-1,sizeof sec);
	dfs(1,0,0);
	for(int j=1;j<19;j++)
		for(int i=1;i<=n;i++)
		{
			p[j][i]=p[j-1][p[j-1][i]];
			best[j][i]=max(best[j-1][i],best[j-1][p[j-1][i]]);
			sec[j][i]=max(max(sec[j-1][i],sec[j-1][p[j-1][i]]),best[j-1][i]==best[j-1][p[j-1][i]]?0:max(best[j-1][i],best[j-1][p[j-1][i]]));
		}
	for(int i=1;i<=m;i++)
		if(!vis[i])
		{
			int u=e[i].u,v=e[i].v,top=-1,top2=-1;
			if(dep[u]>dep[v])swap(u,v);
			for(int k=18;k>=0;k--)
				if(dep[v]-(1<<k)>=dep[u])update(sec[k][v],top,top2),update(best[k][v],top,top2),v=p[k][v];
			for(int k=18;k>=0;k--)
				if(p[k][u]!=p[k][v])
				{
					update(sec[k][u],top,top2),update(best[k][u],top,top2);
					update(sec[k][v],top,top2),update(best[k][v],top,top2);
					u=p[k][u],v=p[k][v];
				}
			if(u!=v)update(best[0][u],top,top2),update(best[0][v],top,top2);
			if(top!=e[i].w)ans=min(ans,tot-top+e[i].w);
			if(top2!=-1)ans=min(ans,tot-top2+e[i].w);
		}
	printf("%lld\n",ans);
}
