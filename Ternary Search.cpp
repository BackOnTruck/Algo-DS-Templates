#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6;
int n;
double l,r,c[20];
double f(double x)
{
	double s=0;
	for(int i=n;i>=0;i--)s=s*x+c[i];
	return s;
}
int main()
{
	cin>>n>>l>>r;
	for(int i=n;i>=0;i--)cin>>c[i];
	while(abs(r-l)>eps)
	{
		double lm=(l+r)/2,rm=(lm+r)/2;
		if(f(lm)>f(rm))r=rm;
		else l=lm;
	}
	printf("%.5f\n",l);
	return 0;
}
