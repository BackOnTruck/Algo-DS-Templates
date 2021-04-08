#include<bits/stdc++.h>
using namespace std;
struct edge{int u,v,w;}e[20001];
int n,m,r,in[201],p[201],id[201],vis[201];
int main()
{
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1;i<=m;i++)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	int ans=0;
	for(;;)
	{
		memset(in,0x3f,sizeof in);
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v,w=e[i].w;
			if(w<in[v]&&u!=v)p[v]=u,in[v]=w;
		}
		for(int i=1;i<=n;i++)
			if(i!=r&&in[i]>1e6){puts("-1");return 0;}
		int cnt=0;
		memset(id,-1,sizeof id);
		memset(vis,-1,sizeof vis);
		in[r]=0;
		for(int i=1;i<=n;i++)
		{
			ans+=in[i];
			int v=i;
			while(vis[v]!=i&&id[v]==-1&&v!=r)vis[v]=i,v=p[v];
			if(v!=r&&id[v]==-1)
			{
				id[v]=++cnt;
				for(int u=p[v];u!=v;u=p[u])id[u]=cnt;
			}
		}
		if(!cnt){printf("%d\n",ans);return 0;}
		for(int i=1;i<=n;i++)
			if(id[i]==-1)id[i]=++cnt;
		for(int i=1;i<=m;i++)
		{
			int u=e[i].u,v=e[i].v;
			e[i].u=id[u],e[i].v=id[v];
			if(id[u]!=id[v])e[i].w-=in[v];
		}
		n=cnt;r=id[r];
	}
}
