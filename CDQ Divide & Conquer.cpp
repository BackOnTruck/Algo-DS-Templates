#include<bits/stdc++.h>
using namespace std;
struct Tuple
{
	int a,b,c,w,id;
	bool operator<(const Tuple &x)const{return a<x.a||(a==x.a&&b<x.b)||(a==x.a&&b==x.b&&c<x.c);}
}a[300001],b[300001];
int n,v,k,cnt[300001];
long long c[300001],ans[300001];
long long sum(int x)
{
	long long res=0;
	while(x)res+=c[x],x-=x&-x;
	return res;
}
void add(int x,int d){while(x<=k)c[x]+=d,x+=x&-x;}
void solve(int l,int r)
{
	if(l==r)return;
	int m=(l+r)/2;
	solve(l,m);
	solve(m+1,r);
	int p=l,q=m+1,cur=l;
	while(p<=m||q<=r)
		if(p<=m&&(q>r||a[p].b<=a[q].b))add(a[p].c,a[p].w),b[cur++]=a[p++];
		else ans[a[q].id]+=sum(a[q].c),b[cur++]=a[q++];
	for(int i=l;i<=m;i++)add(a[i].c,-a[i].w);
	for(int i=l;i<=r;i++)a[i]=b[i];
}
int main()
{
	scanf("%d%d",&v,&k);
	map<Tuple,int> m;
	for(int i=1;i<=v;i++)scanf("%d%d%d",&a[i].a,&a[i].b,&a[i].c),m[a[i]]++;
	for(auto x:m)n++,a[n]=x.first,a[n].w=x.second,a[n].id=n;
	solve(1,n);
	for(int i=1;i<=n;i++)cnt[ans[a[i].id]+a[i].w-1]+=a[i].w;
	for(int i=0;i<v;i++)printf("%d\n",cnt[i]);
	return 0;
}
