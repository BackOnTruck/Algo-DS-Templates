#include<bits/stdc++.h>
using namespace std;
const double eps=1e-12;
double a;
inline double f(double x){return pow(x,a/x-x);}
inline double simpson(double l,double r){return (r-l)/6*(f(l)+4*f((l+r)/2)+f(r));}
double calc(double l,double r,double ans)
{
	double m=(l+r)/2,x=simpson(l,m),y=simpson(m,r);
	if(abs(x+y-ans)<eps)return x+y;
	return calc(l,m,x)+calc(m,r,y);
}
int main()
{
	cin>>a;
	if(a<0)cout<<"orz\n";
	else cout<<fixed<<setprecision(5)<<calc(eps,15,simpson(eps,15))<<endl;
}
