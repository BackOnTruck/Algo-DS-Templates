#include<bits/stdc++.h>
using namespace std;
const double eps=1e-12;
double a,b,c,d;
inline double f(double x){return (c*x+d)/(a*x+b);}
inline double simpson(double l,double r){return (r-l)/6*(f(l)+4*f((l+r)/2)+f(r));}
double calc(double l,double r,double ans)
{
	double m=(l+r)/2,x=simpson(l,m),y=simpson(m,r);
	if(abs(x+y-ans)<eps)return x+y;
	return calc(l,m,x)+calc(m,r,y);
}
int main()
{
	double l,r;
	cin>>a>>b>>c>>d>>l>>r;
	cout<<fixed<<setprecision(6)<<calc(l,r,simpson(l,r))<<endl;
}
