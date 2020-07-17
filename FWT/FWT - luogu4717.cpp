#include<bits/stdc++.h>
using namespace std;
const int mod=998244353,inv2=(mod+1)/2;
int add(int a,int b){int c=a+b;return c>=mod?c-mod:c;}
int sub(int a,int b){int c=a-b+mod;return c>=mod?c-mod:c;}
void fwt_and(int *c,int n,int f)
{
	for(int h=2;h<=n;h<<=1)
		for(int j=0;j<n;j+=h)
			for(int k=j;k<j+h/2;k++)c[k]=(f==1?add:sub)(c[k],c[k+h/2]);
}
void fwt_or(int *c,int n,int f)
{
	for(int h=2;h<=n;h<<=1)
		for(int j=0;j<n;j+=h)
			for(int k=j;k<j+h/2;k++)c[k+h/2]=(f==1?add:sub)(c[k+h/2],c[k]);
}
void fwt_xor(int *c,int n,int f)
{
	for(int h=2;h<=n;h<<=1)
	{
		for(int j=0;j<n;j+=h)
			for(int k=j;k<j+h/2;k++)
			{
				int x=c[k],y=c[k+h/2];
				c[k]=add(x,y);
				c[k+h/2]=sub(x,y);
			}
		if(f==-1)
			for(int i=0;i<n;i++)c[i]=1ll*c[i]*inv2%mod;
	}
}
int n,a[1<<19],b[1<<19],c[1<<19],d[1<<19],e[1<<19];
template<class T>void solve(T fwt)
{
	memcpy(d,a,sizeof a);
	memcpy(e,b,sizeof b);
	fwt(d,n,1);
	fwt(e,n,1);
	for(int i=0;i<n;i++)c[i]=1ll*d[i]*e[i]%mod;
	fwt(c,n,-1);
	for(int i=0;i<n;i++)printf("%d ",c[i]);
	puts("");
}
int main()
{
	scanf("%d",&n);n=1<<n;
	for(int i=0;i<n;i++)scanf("%d",a+i);
	for(int i=0;i<n;i++)scanf("%d",b+i);
	solve(fwt_or);
	solve(fwt_and);
	solve(fwt_xor);
}
