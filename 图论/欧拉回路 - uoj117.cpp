#include<bits/stdc++.h>
using namespace std;
struct edge{int v,id;};
int t,n,m,in[110001],out[110001],vis[220001],last[220001];
vector<edge> w[110001];
vector<int> ans;
void dfs(int u)
{
	for(int &i=last[u];i<(int)w[u].size();i++)
	{
		edge &e=w[u][i];
		if(!vis[abs(e.id)])
		{
			vis[abs(e.id)]=1;
			dfs(e.v);
			ans.push_back(e.id);
		}
	}
}
int main()
{
	scanf("%d%d%d",&t,&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		w[u].push_back({v,i});
		if(t==1)w[v].push_back({u,-i}),in[u]++,in[v]++;
		else in[v]++,out[u]++;
	}
	for(int i=1;i<=n;i++)
		if((t==1&&in[i]%2)||(t==2&&in[i]!=out[i]))return puts("NO"),0;
	for(int i=1;i<=n;i++)
		if(w[i].size()){dfs(i);break;}
	if(ans.size()!=m)return puts("NO"),0;
	puts("YES");
	reverse(ans.begin(),ans.end());
	for(int i:ans)printf("%d ",i);
	puts("");
}
