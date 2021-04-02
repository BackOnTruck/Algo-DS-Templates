// 思路：先求出树的直径a-b，则任意一个结点u到另一个结点的最大距离为max(d(u,a),d(u,b))
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
struct edge{int v,w;};
int n,s[20001];
vector<edge> w[20001];
void dfs(int u,int p,int d)
{
	s[u]=max(s[u],d);
	for(int i=0;i<w[u].size();i++)
		if(p!=w[u][i].v)dfs(w[u][i].v,u,d+w[u][i].w);
}
int main()
{
	while(scanf("%d",&n)==1)
	{
		for(int i=1;i<=n;i++)w[i].clear(),s[i]=0;
		for(int i=2,x,y;i<=n;i++)
		{
			scanf("%d%d",&x,&y);
			w[i].push_back({x,y});
			w[x].push_back({i,y});
		}
		dfs(1,0,0);
		int Max=0,u=1,v=1;
		for(int i=2;i<=n;i++)
			if(Max<s[i])Max=s[i],u=i;
		dfs(u,0,0);
		Max=0;
		for(int i=2;i<=n;i++)
			if(Max<s[i])Max=s[i],v=i;
		dfs(v,0,0);
		for(int i=1;i<=n;i++)printf("%d\n",s[i]);
	}
}
