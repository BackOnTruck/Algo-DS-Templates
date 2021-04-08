#include<bits/stdc++.h>
using namespace std;
int p;
inline long long sqr(int a){return 1ll*a*a%p;}
int pow(int a,int n)
{
	if(!n)return 1;
	if(n&1)return sqr(pow(a,n/2))*a%p;
	return sqr(pow(a,n/2));
}
inline int Legend(int a){return pow(a,p/2);}
struct Mod
{
	int r,i,w;
	Mod(int a,int b,int c):r(a),i(b),w(c){}
	Mod operator*(Mod b){return Mod((1ll*r*b.r+1ll*i*b.i%p*w)%p,(1ll*i*b.r+1ll*r*b.i)%p,w);}
};
inline Mod sqr(Mod a){return a*a;}
Mod pow(Mod a,int n)
{
	if(!n)return Mod(1,0,a.w);
	if(n&1)return sqr(pow(a,n/2))*a;
	return sqr(pow(a,n/2));
}
int main()
{
	int t,n;
	srand(time(0));
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&p);n%=p;
		if(p==2){puts("1");continue;}
		if(Legend(n)==p-1){puts("No root");continue;}
		int a,w;
		do{a=rand()%p;w=((1ll*a*a-n)%p+p)%p;}while(Legend(w)==1);
		int ans=pow(Mod(a,1,w),(p+1)/2).r;
		if(ans*2>p)ans=p-ans;
		printf("%d %d\n",ans,p-ans);
	}
}
