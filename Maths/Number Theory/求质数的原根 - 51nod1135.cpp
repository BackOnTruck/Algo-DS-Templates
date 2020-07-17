#include<bits/stdc++.h>
using namespace std;
int p;
long long sqr(long long x){return x*x%p;}
int pow(int a,int n){return !n?1:sqr(pow(a,n/2))*(n&1?a:1)%p;}
vector<int> f;
int main()
{
	cin>>p;
	int k=p-1;
	for(int i=2;i*i<=k;i++)
		if(k%i==0)
		{
			while(k%i==0)k/=i;
			f.push_back(i);
		}
	if(k>1)f.push_back(k);
	for(int i=2;;i++)
	{
		bool g=1;
		for(int j:f)
			if(pow(i,(p-1)/j)==1){g=0;break;}
		if(g)return cout<<i<<'\n',0;
	}
}
