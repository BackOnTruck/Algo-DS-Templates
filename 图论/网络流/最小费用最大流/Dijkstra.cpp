#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
struct edge
{
	int v,cap,cost,rev;
	edge(int a,int b,int c,int w):v(a),cap(b),cost(c),rev(w){}
};
vector<edge> w[233333];
const int oo=1<<29;
int d[233333],pv[233333],pe[233333],n,h[233333];
typedef pair<int,int> P;
P min_cost_flow(int s,int t)
{
	int ans=0,F=0;
	memset(h,0,sizeof h);
	while(1)
	{
		priority_queue<P,vector<P>,greater<P>> q;
		for(int i=0;i<=n;i++)d[i]=oo;
		d[s]=0;
		q.push({0,s});
		while(!q.empty())
		{
			P p=q.top();q.pop();
			int v=p.second;
			if(d[v]<p.first)continue;
			for(int i=0;i<w[v].size();i++)
			{
				edge &e=w[v][i];
				if(e.cap&&d[e.v]+h[e.v]>d[v]+h[v]+e.cost)
				{
					d[e.v]=d[v]+h[v]+e.cost-h[e.v];
					pv[e.v]=v;
					pe[e.v]=i;
					q.push({d[e.v],e.v});
				}
			}
		}
		if(d[t]==oo)return {F,ans};
		for(int v=0;v<=n;v++)h[v]+=d[v];
		int D=oo;
		for(int v=t;v!=s;v=pv[v])D=min(D,w[pv[v]][pe[v]].cap);
		F+=D;
		ans+=D*h[t];
		for(int v=t;v!=s;v=pv[v])
		{
			edge &e=w[pv[v]][pe[v]];
			e.cap-=D;
			w[v][e.rev].cap+=D;
		}
	}
}
int main()
{
	int m,s,t;
	cin>>n>>m>>s>>t;
	while(m--)
	{
		int x,y,z,u;
		cin>>x>>y>>z>>u;
		w[x].emplace_back(y,z,u,w[y].size());
		w[y].emplace_back(x,0,-u,w[x].size()-1);
	}
	P ans=min_cost_flow(s,t);
	cout<<ans.first<<' '<<ans.second<<endl;
	return 0;
}
