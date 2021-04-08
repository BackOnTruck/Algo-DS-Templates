#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
struct edge
{
	int v,cap,cost,rev;
	edge(int a,int b,int c,int w):v(a),cap(b),cost(c),rev(w){}
};
vector<edge> w[233333];
const int oo=1<<29;
int d[233333],pv[233333],pe[233333],n;
pair<int,int> min_cost_flow(int s,int t)
{
	int ans=0,F=0;
	while(1)
	{
		for(int i=0;i<=n;i++)d[i]=oo;
		d[s]=0;
		for(;;)
		{
			bool g=0;
			for(int v=0;v<=n;v++)
				if(d[v]!=oo)for(int i=0;i<w[v].size();i++)
				{
					edge &e=w[v][i];
					if(d[e.v]>d[v]+e.cost&&e.cap)
					{
						d[e.v]=d[v]+e.cost;
						pv[e.v]=v;
						pe[e.v]=i;
						g=1;
					}
				}
			if(!g)break;
		}
		if(d[t]==oo)return make_pair(F,ans);
		int x=oo;
		for(int v=t;v!=s;v=pv[v])x=min(x,w[pv[v]][pe[v]].cap);
		ans+=x*d[t];
		F+=x;
		for(int v=t;v!=s;v=pv[v])
		{
			edge &e=w[pv[v]][pe[v]];
			e.cap-=x;
			w[e.v][e.rev].cap+=x;
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int m,s,t;
	cin>>n>>m>>s>>t;
	while(m--)
	{
		int x,y,z,u;
		cin>>x>>y>>z>>u;
		w[x].emplace_back(y,z,u,w[y].size());
		w[y].emplace_back(x,0,-u,w[x].size()-1);
	}
	pair<int,int> ans=min_cost_flow(s,t);
	cout<<ans.first<<' '<<ans.second<<endl;
	return 0;
}
