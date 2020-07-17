#include<bits/stdc++.h>
using namespace std;
int n;
double p[25];
int main()
{
	while(cin>>n)
	{
		for(int i=0;i<n;i++)cin>>p[i];
		double ans=0;
		for(int s=1;s<(1<<n);s++)
		{
			double sum=0;
			for(int i=0;i<n;i++)
				if(s&(1<<i))sum+=p[i];
			ans+=(__builtin_popcount(s)&1?1:-1)/sum;
		}
		printf("%.20g\n",ans);
	}
}
