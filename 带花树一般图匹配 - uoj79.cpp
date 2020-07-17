#include<bits/stdc++.h>
using namespace std;
int n,m,cp[1001],f[1001],p[1001],type[1001],flag=0,tag[1001];
vector<int> w[1001];
int find(int x){return f[x]==x?x:f[x]=find(f[x]);}
int lca(int u,int v)
{
	for(flag++;;swap(u,v))
		if(u)
		{
			u=find(u);
			if(tag[u]==flag)return u;
			tag[u]=flag;
			u=p[cp[u]];
		}
}
queue<int> q;
void blossom(int u,int v,int root)
{
	while(find(u)!=root)
	{
		p[u]=v;v=cp[u];
		if(type[v]==2)type[v]=1,q.push(v);
		if(find(u)==u)f[u]=root;
		if(find(v)==v)f[v]=root;
		u=p[v];
	}
}
bool match(int s)
{
	for(int i=1;i<=n;i++)f[i]=i;
	memset(p,0,sizeof p);
	memset(type,0,sizeof type);
	q=queue<int>();
	type[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int v:w[u])
		{
			if(find(u)==find(v)||type[v]==2)continue;
			if(!type[v])
			{
				type[v]=2;p[v]=u;
				if(!cp[v])
				{
					for(int now=v;now;)
					{
						int x=p[now],y=now;
						now=cp[x];
						cp[y]=x;cp[x]=y;
					}
					return 1;
				}
				type[cp[v]]=1;
				q.push(cp[v]);
			}
			else if(type[v]==1)
			{
				int LCA=lca(u,v);
				blossom(u,v,LCA);
				blossom(v,u,LCA);
			}
		}
	}
	return 0;
}
int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		w[u].push_back(v);
		w[v].push_back(u);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(!cp[i])ans+=match(i);
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)printf("%d ",cp[i]);
	puts("");
}
