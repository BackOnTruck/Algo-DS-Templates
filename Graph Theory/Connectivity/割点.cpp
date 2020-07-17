#include<bits/stdc++.h>
using namespace std;
vector<int> w[110001];
int num,dfn[110001],low[110001];
vector<int> ans;
void tarjan(int u,int r)
{
	dfn[u]=low[u]=++num;
	int c=0,f=0;
	for(int v:w[u])
		if(!dfn[v])
		{
			tarjan(v,r),low[u]=min(low[u],low[v]),c++;
			if(low[v]>=dfn[u]&&u!=r)f=1;
		}
		else low[u]=min(low[u],dfn[v]);
	if(u==r&&c>1)f=1;
	if(f)ans.push_back(u);
}
int n,m;
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
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i,i);
	sort(ans.begin(),ans.end());
	printf("%llu\n",ans.size());
	for(int x:ans)printf("%d ",x);
	puts("");
}
