#include<bits/stdc++.h>
using namespace std;
struct edge{int v,w;};
vector<edge> w[3001];
int t,n,m,d[3001];
bool check()
{
	for(int u=1;u<=n;u++)
		for(edge e:w[u])
			if(d[u]<0x3f3f3f3f&&d[e.v]>d[u]+e.w)return 1;
	return 0;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)w[i].clear();
		while(m--)
		{
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			w[x].push_back({y,z});
			if(z>=0)w[y].push_back({x,z});
		}
		memset(d,0x3f,sizeof d);
		d[1]=0;
		for(int i=1;i<n;i++)
			for(int u=1;u<=n;u++)
				if(d[u]<0x3f3f3f3f)for(edge e:w[u])d[e.v]=min(d[e.v],d[u]+e.w);
		puts(check()?"YE5":"N0");
	}
}
