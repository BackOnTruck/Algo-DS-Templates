#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
inline int add(int x,int y,int mod){int z=x+y;return z>=mod?z-mod:z;}
struct tree
{
	int mod,sumv[500001],addv[500001];
	void init(int md){mod=md;}
	void build(int *a,int o,int l,int r)
	{
		if(l==r){sumv[o]=a[l];return;}
		int m=(l+r)/2;
		build(a,o*2,l,m);
		build(a,o*2+1,m+1,r);
		sumv[o]=(sumv[o*2]+sumv[o*2+1])%mod;
	}
	void pushdown(int o,int l,int r)
	{
		if(l==r)return;
		addv[o*2]=add(addv[o*2],addv[o],mod);
		addv[o*2+1]=add(addv[o*2+1],addv[o],mod);
		int m=(l+r)/2;
		sumv[o*2]=add(sumv[o*2],1ll*addv[o]*(m-l+1)%mod,mod);
		sumv[o*2+1]=add(sumv[o*2+1],1ll*addv[o]*(r-m)%mod,mod);
		addv[o]=0;
	}
	void modify(int x,int y,int d,int o,int l,int r)
	{
		if(x<=l&&r<=y)
		{
			addv[o]=add(addv[o],d,mod);
			sumv[o]=add(sumv[o],1ll*d*(r-l+1)%mod,mod);
			return;
		}
		pushdown(o,l,r);
		int m=(l+r)/2;
		if(x<=m)modify(x,y,d,o*2,l,m);
		if(y>m)modify(x,y,d,o*2+1,m+1,r);
		sumv[o]=add(sumv[o*2],sumv[o*2+1],mod);
	}
	int query(int x,int y,int o,int l,int r)
	{
		if(x<=l&&r<=y)return sumv[o];
		pushdown(o,l,r);
		int m=(l+r)>>1,ans=0;
		if(x<=m)ans=add(ans,query(x,y,o*2,l,m),mod);
		if(y>m)ans=add(ans,query(x,y,o*2+1,m+1,r),mod);
		return ans;
	}
}T;
vector<int> w[110001];
int n,m,r,mod,dep[110001],p[110001][21],sz[110001],id[110001],top[110001],num[110001],last[110001],val[110001],rval[110001],tot,number,chaincnt=1;
void dfs(int u,int f,int depth)
{
	dep[u]=depth;
	sz[u]=1;
	p[u][0]=f;
	for(int v:w[u])
		if(v!=f)dfs(v,u,depth+1),sz[u]+=sz[v];
}
int lca(int u,int v)
{
	if(dep[u]>dep[v])swap(u,v);
	int k=16;
	while(dep[v]!=dep[u])
	{
		while(dep[v]-dep[u]<(1<<k))k--;
		v=p[v][k];
	}
	k=18;
	while(v!=u)
	{
		while(k&&p[v][k]==p[u][k])k--;
		u=p[u][k];
		v=p[v][k];
	}
	return u;
}
void init(int u,int f,int chcnt,bool is_top)
{
	num[u]=++number;
	id[u]=chcnt;
	if(is_top)top[chcnt]=u;
	int Max=0,pos=-1;
	for(int i=0;i<w[u].size();i++)
		if(w[u][i]!=f&&sz[w[u][i]]>Max)Max=sz[w[u][i]],pos=i;
	if(pos!=-1)
	{
		if(pos)swap(w[u][pos],w[u][0]);
		init(w[u][0],u,chcnt,0);
		for(int i=1;i<w[u].size();i++)
			if(w[u][i]!=f)init(w[u][i],u,++chaincnt,1);
	}
	last[u]=number;
}
void modify(int x,int y,int d)
{
	if(id[x]==id[y])return T.modify(num[x],num[y],d,1,1,n);
	modify(x,p[top[id[y]]][0],d);
	T.modify(num[top[id[y]]],num[y],d,1,1,n);
}
int query(int x,int y)
{
	if(id[x]==id[y])return T.query(num[x],num[y],1,1,n);
	return add(query(x,p[top[id[y]]][0]),T.query(num[top[id[y]]],num[y],1,1,n),mod);
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&r,&mod);
	for(int i=1;i<=n;i++)scanf("%d",val+i);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		w[a].push_back(b);
		w[b].push_back(a);
	}
	dfs(r,0,1);
	for(int i=1;i<19;i++)
		for(int j=1;j<=n;j++)p[j][i]=p[p[j][i-1]][i-1];
	init(r,0,1,1);
	for(int i=1;i<=n;i++)rval[num[i]]=val[i];
	T.init(mod);
	T.build(rval,1,1,n);
	while(m--)
	{
		int op,x,y,z;
		scanf("%d%d",&op,&x);
		if(op==1)
		{
			scanf("%d%d",&y,&z);
			int LCA=lca(x,y);
			modify(LCA,x,z);
			modify(LCA,y,z);
			T.modify(num[LCA],num[LCA],mod-z,1,1,n);
		}
		else if(op==2)
		{
			scanf("%d",&y);
			int LCA=lca(x,y);
			printf("%d\n",((query(LCA,x)+query(LCA,y))%mod+mod-T.query(num[LCA],num[LCA],1,1,n))%mod);
		}
		else if(op==3)scanf("%d",&z),T.modify(num[x],last[x],z,1,1,n);
		else printf("%d\n",T.query(num[x],last[x],1,1,n));
	}
	return 0;
}
