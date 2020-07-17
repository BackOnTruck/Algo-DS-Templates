#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int oo=1<<29;
namespace flow
{
	struct edge
	{
		int v,cap,rev;
		edge(int a,int b,int c):v(a),cap(b),rev(c){}
	};
	vector<edge> w[52000];
	void add_edge(int u,int v,int cap)
	{
		w[u].push_back(edge(v,cap,w[v].size()));
		w[v].push_back(edge(u,0,w[u].size()-1));
	}
	int level[52000],iter[52000];
	int dfs(int s,int t,int f)
	{
		if(s==t)return f;
		for(int &i=iter[s];i<w[s].size();i++)
		{
			edge &e=w[s][i];
			if(e.cap&&level[e.v]>level[s])
				if(int d=dfs(e.v,t,min(f,e.cap)))
				{
					e.cap-=d;
					w[e.v][e.rev].cap+=d;
					return d;
				}
		}
		return 0;
	}
	int max_flow(int s,int t)
	{
		int ans=0;
		for(;;)
		{
			memset(level,-1,sizeof level);
			memset(iter,0,sizeof iter);
			level[s]=0;
			queue<int> q;
			q.push(s);
			while(!q.empty())
			{
				int u=q.front();q.pop();
				for(int e=0;e<w[u].size();e++)
				{
					edge &i=w[u][e];
					if(level[i.v]==-1&&i.cap)
					{
						level[i.v]=level[u]+1;
						q.push(i.v);
					}
				}
			}
			if(level[t]==-1)return ans;
			while(int f=dfs(s,t,oo))ans+=f;
		}
	}
}
int n,m,s,t;
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&t);
	while(m--)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		flow::add_edge(a,b,c);
	}
	printf("%d\n",flow::max_flow(s,t));
	return 0;
}
