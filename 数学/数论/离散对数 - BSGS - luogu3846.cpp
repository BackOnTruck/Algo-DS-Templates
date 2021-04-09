#include<cstdio>
#include<cmath>
#include<unordered_map>
using namespace std;
long long sqr(int a,int p){return 1ll*a*a%p;}
int pow(int a,int n,int p)
{
	if(!n)return 1;
	return sqr(pow(a,n/2,p),p)*(n&1?a:1)%p;
}
int a,b,p;
int main()
{
	scanf("%d%d%d",&p,&a,&b);
	a%=p;b%=p;
	int n=floor(sqrt(p)+.5)+1,inv=pow(pow(a,p-2,p),n,p);
	unordered_map<int,int> m;
	for(int i=0,res=1;i<n;i++,res=1ll*res*a%p)
		if(!m.count(res))m[res]=i;
		else break;
	for(int i=0,res=b;1ll*i*n<p;i++,res=1ll*res*inv%p)
		if(m.count(res)){printf("%d\n",i*n+m[res]);return 0;}
	puts("no solution");
}
