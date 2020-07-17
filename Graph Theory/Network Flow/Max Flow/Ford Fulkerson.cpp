#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
struct edge
{
	int v,cap,rev;
	edge(int a,int b,int w):v(a),cap(b),rev(w){}
};
vector<edge> w[20001];
const int oo=1<<29;
int vis[20001];
int dfs(int s,int t,int f)
{
	if(s==t)return f;
	vis[s]=1;
	for(edge &e:w[s])
		if(!vis[e.v]&&e.cap)
			if(int d=dfs(e.v,t,min(f,e.cap)))
			{
				e.cap-=d;
				w[e.v][e.rev].cap+=d;
				return d;
			}
	return 0;
}
int max_flow(int s,int t)
{
	int ans=0;
	for(;;)
	{
		memset(vis,0,sizeof vis);
		if(int f=dfs(s,t,oo))ans+=f;
		else return ans;
	}
}
int main()
{
	int n,m,s,t;
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>s>>t;
	while(m--)
	{
		int x,y,z;
		cin>>x>>y>>z;
		w[x].emplace_back(y,z,w[y].size());
		w[y].emplace_back(x,0,w[x].size()-1);
	}
	cout<<max_flow(s,t)<<endl;
	return 0;
}
