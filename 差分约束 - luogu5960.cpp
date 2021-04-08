#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
struct edge{int v,w;};
vector<edge> w[11001];
int n,m,cnt[11001],d[11001];
int main()
{
	scanf("%d%d",&n,&m);
	while(m--)
	{
		int x,y,z;
		scanf("%d%d%d",&y,&x,&z);
		w[x].push_back({y,z});
	}
	for(int i=1;i<=n;i++)w[0].push_back({i,0});
	queue<int> q;
	memset(d,0x3f,sizeof d);
	d[0]=0;
	q.push(0);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(edge e:w[u])
			if(d[e.v]>d[u]+e.w)
			{
				d[e.v]=d[u]+e.w;
				q.push(e.v);
			}
		if(++cnt[u]>=n){puts("NO");return 0;}
	}
	for(int i=1;i<=n;i++)printf("%d ",d[i]);
	puts("");
}
