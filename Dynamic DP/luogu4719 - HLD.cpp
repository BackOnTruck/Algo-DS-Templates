#include<bits/stdc++.h>
using namespace std;
struct matrix
{
	int a[2][2];
	matrix():a{{0,0},{0,0}}{}
	matrix(int w,int x,int y,int z):a{{w,x},{y,z}}{}
	matrix operator*(const matrix &b)const{return {max(a[0][0]+b.a[0][0],a[0][1]+b.a[1][0]),max(a[0][0]+b.a[0][1],a[0][1]+b.a[1][1]),max(a[1][0]+b.a[0][0],a[1][1]+b.a[1][0]),max(a[1][0]+b.a[0][1],a[1][1]+b.a[1][1])};}
	void operator*=(const matrix &b){*this=*this*b;}
};
struct colvector
{
	int a[2];
	colvector(int x,int y):a{x,y}{}
	colvector operator*(const matrix &b)const{return {max(b.a[0][0]+a[0],b.a[0][1]+a[1]),max(b.a[1][0]+a[0],b.a[1][1]+a[1])};}
}zero{0,0};
struct tree
{
	matrix sumv[700001];
	void build(int g[110001][2],int o,int l,int r)
	{
		if(l==r){sumv[o]={g[l][0],g[l][0],g[l][1],0};return;}
		int m=(l+r)/2;
		build(g,o*2,l,m);
		build(g,o*2+1,m+1,r);
		sumv[o]=sumv[o*2]*sumv[o*2+1];
	}
	void modify(int x,int *g,int o,int l,int r)
	{
		if(l==r){sumv[o]={g[0],g[0],g[1],0};return;}
		int m=(l+r)/2;
		if(x<=m)modify(x,g,o*2,l,m);
		else modify(x,g,o*2+1,m+1,r);
		sumv[o]=sumv[o*2]*sumv[o*2+1];
	}
	matrix query(int x,int y,int o,int l,int r)
	{
		if(x<=l&&r<=y)return sumv[o];
		int m=(l+r)>>1;
		if(x<=m&&y<=m)return query(x,y,o*2,l,m);
		if(x<=m&&y>m)return query(x,y,o*2,l,m)*query(x,y,o*2+1,m+1,r);
		return query(x,y,o*2+1,m+1,r);
	}
}T;
vector<int> w[110001];
int n,q,p[110001],sz[110001],id[110001],top[110001],bottom[110001],val[110001],g[110001][2],rg[110001][2],f[110001][2],num[110001],chaincnt=1,number;
void dfs(int u)
{
	sz[u]=1;
	for(int v:w[u])
		if(v!=p[u])p[v]=u,dfs(v),sz[u]+=sz[v];
}
void init(int u,int chcnt,bool is_top)
{
	num[u]=++number;
	id[u]=chcnt;
	if(is_top)top[chcnt]=u;
	int Max=0,pos=-1;
	for(int i=0;i<(int)w[u].size();i++)
		if(sz[w[u][i]]>Max)Max=sz[w[u][i]],pos=i;
	if(pos!=-1)
	{
		if(pos)swap(w[u][pos],w[u][0]);
		init(w[u][0],chcnt,0);
		for(int i=1;i<(int)w[u].size();i++)init(w[u][i],++chaincnt,1);
	}
	else bottom[chcnt]=u;
}
void dp(int u)
{
	g[u][1]=val[u];
	for(int i=1;i<(int)w[u].size();i++)
	{
		int v=w[u][i];
		dp(v);
		g[u][0]+=max(f[v][0],f[v][1]);
		g[u][1]+=f[v][0];
	}
	f[u][0]=g[u][0];
	f[u][1]=g[u][1];
	if(!w[u].empty())
	{
		int v=w[u][0];
		dp(v);
		f[u][0]+=max(f[v][0],f[v][1]);
		f[u][1]+=f[v][0];
	}
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",val+i);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		w[u].push_back(v);
		w[v].push_back(u);
	}
	dfs(1);
	for(int i=2;i<=n;i++)
		for(int j=0;j<(int)w[i].size();j++)
			if(w[i][j]==p[i]){w[i].erase(w[i].begin()+j);break;}
	init(1,1,1);
	dp(1);
	for(int i=1;i<=n;i++)rg[num[i]][0]=g[i][0],rg[num[i]][1]=g[i][1];
	T.build(rg,1,1,n);
	while(q--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		g[x][1]+=y-val[x];
		val[x]=y;
		T.modify(num[x],g[x],1,1,n);
		int chain=id[x];
		for(;;)
		{
			const int head=top[chain],tail=bottom[chain],par=p[head];
			colvector newf=zero*T.query(num[head],num[tail],1,1,n),oldf{f[head][0],f[head][1]};
			f[head][0]=newf.a[0];f[head][1]=newf.a[1];
			if(!par)break;
			matrix old=T.query(num[par],num[par],1,1,n);
			int newg[2]={old.a[0][0],old.a[1][0]};
			g[par][0]=newg[0]+=max(newf.a[0],newf.a[1])-max(oldf.a[0],oldf.a[1]);
			g[par][1]=newg[1]+=newf.a[0]-oldf.a[0];
			T.modify(num[par],newg,1,1,n);
			chain=id[par];
		}
		printf("%d\n",max(f[1][0],f[1][1]));
	}
}
