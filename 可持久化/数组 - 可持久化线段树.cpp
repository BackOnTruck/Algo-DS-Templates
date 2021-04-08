#include<bits/stdc++.h>
using namespace std;
int tot=0,val[25000001],lc[25000001],rc[25000001],root[1000001],a[1000001];
void build(int &o,int l,int r)
{
	o=++tot;
	if(l==r){val[o]=a[l];return;}
	int m=(l+r)/2;
	build(lc[o],l,m);
	build(rc[o],m+1,r);
}
int modify(int o,int l,int r,int p,int v)
{
	int newv=++tot;
	lc[newv]=lc[o];
	rc[newv]=rc[o];
	if(l==r){val[newv]=v;return newv;}
	int m=(l+r)/2;
	if(p<=m)lc[newv]=modify(lc[newv],l,m,p,v);
	else rc[newv]=modify(rc[newv],m+1,r,p,v);
	return newv;
}
int query(int o,int l,int r,int p)
{
	if(l==r)return val[o];
	int m=(l+r)/2;
	return p<=m?query(lc[o],l,m,p):query(rc[o],m+1,r,p);
}
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	build(root[0],1,n);
	for(int i=1;i<=m;i++)
	{
		int ver,op,pos,value;
		scanf("%d%d%d",&ver,&op,&pos);
		if(op==1)scanf("%d",&value),root[i]=modify(root[ver],1,n,pos,value);
		else printf("%d\n",query(root[i]=root[ver],1,n,pos));
	}
	return 0;
}
