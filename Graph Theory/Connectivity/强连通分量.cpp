#include<bits/stdc++.h>
using namespace std;
vector<int> w[100001],nw[100001];
int sccid[100001],weight[100001],cnt[100001],tot,num,dfn[100001],low[100001],f[100001],in[100001];
stack<int> st;
void push(int u){st.push(u);in[u]=1;}
int pop(){int u=st.top();st.pop();in[u]=0;return u;}
void tarjan(int u)
{
	dfn[u]=low[u]=++num;
	push(u);
	for(int v:w[u])
		if(!dfn[v])tarjan(v),low[u]=min(low[u],low[v]);
		else if(in[v])low[u]=min(low[u],dfn[v]);
	if(dfn[u]==low[u])
	{
		tot++;
		for(;;)
		{
			int v=pop();
			sccid[v]=tot;
			weight[tot]+=cnt[v];
			if(u==v)break;
		}
	}
}
int dp(int u)
{
	if(f[u]!=-1)return f[u];
	f[u]=weight[u];
	for(int v:nw[u])f[u]=max(f[u],weight[u]+dp(v));
	return f[u];
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",cnt+i);
	while(m--)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		w[u].push_back(v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])tarjan(i);
	for(int i=1;i<=n;i++)
		for(int j:w[i])
			if(sccid[i]!=sccid[j])nw[sccid[i]].push_back(sccid[j]);
	for(int i=1;i<=tot;i++)sort(nw[i].begin(),nw[i].end()),nw[i].erase(unique(nw[i].begin(),nw[i].end()),nw[i].end());
	int ans=0;
	memset(f,-1,sizeof f);
	for(int i=1;i<=tot;i++)ans=max(ans,dp(i));
	printf("%d\n",ans);
}
