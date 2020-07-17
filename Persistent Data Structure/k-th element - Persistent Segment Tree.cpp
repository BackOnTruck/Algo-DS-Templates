#include<bits/stdc++.h>
using namespace std;
int tot=0,sum[7000001],lc[7000001],rc[7000001],root[300001];
void build(int &o,int l,int r)
{
	o=++tot;
	if(l==r)return;
	int m=(l+r)/2;
	build(lc[o],l,m);
	build(rc[o],m+1,r);
}
int modify(int o,int l,int r,int p)
{
	int newv=++tot;
	lc[newv]=lc[o];
	rc[newv]=rc[o];
	sum[newv]=sum[o]+1;
	if(l==r)return newv;
	int m=(l+r)/2;
	if(p<=m)lc[newv]=modify(lc[newv],l,m,p);
	else rc[newv]=modify(rc[newv],m+1,r,p);
	return newv;
}
int query(int u,int v,int l,int r,int k)
{
	if(l==r)return l;
	int m=(l+r)/2,x=sum[lc[v]]-sum[lc[u]];
	return x>=k?query(lc[u],lc[v],l,m,k):query(rc[u],rc[v],m+1,r,k-x);
}
int n,m,a[300001],b[300001];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",a+i),b[i]=a[i];
	sort(b+1,b+1+n);
	int sz=unique(b+1,b+1+n)-b-1;
	build(root[0],1,sz);
	for(int i=1;i<=n;i++)root[i]=modify(root[i-1],1,sz,lower_bound(b+1,b+1+sz,a[i])-b);
	while(m--)
	{
		int l,r,k;
		scanf("%d%d%d",&l,&r,&k);
		printf("%d\n",b[query(root[l-1],root[r],1,sz,k)]);
	}
	return 0;
}
