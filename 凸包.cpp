#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
bool equal(double x,double y){return abs(x-y)<eps;}
struct point
{
	double x,y,th;
	point(){}
	point(double a,double b):x(a),y(b),th(0){}
	bool operator<(const point &b)const{return th<b.th||(equal(th,b.th)&&x<b.x);}
	point operator-(const point &b)const{return point(x-b.x,y-b.y);}
}p[110001];
double dist(point a,point b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
double cross(point a,point b){return a.x*b.y-a.y*b.x;}
int n;
int main()
{
	scanf("%d",&n);
	p[0]=point(1e300,1e300);
	for(int i=1;i<=n;i++)scanf("%lf%lf",&p[i].x,&p[i].y);
	int pos=0;
	for(int i=1;i<=n;i++)
		if(p[0].y>p[i].y||(equal(p[0].y,p[i].y)&&p[0].x>p[i].x))p[0]=p[i],pos=i;
	swap(p[pos],p[1]);
	for(int i=2;i<=n;i++)p[i].th=atan2(p[i].y-p[1].y,p[i].x-p[1].x);
	sort(p+2,p+n+1);
	vector<point> v;
	v.push_back(p[1]);
	v.push_back(p[2]);
	for(int i=3;i<=n;i++)
	{
		while(v.size()>1&&cross(p[i]-v[v.size()-2],v.back()-v[v.size()-2])>-eps)v.pop_back();
		v.push_back(p[i]);
	}
	double ans=0;
	for(int i=1;i<(int)v.size();i++)ans+=dist(v[i-1],v[i]);
	ans+=dist(v[0],v.back());
	printf("%.2f\n",ans);
}
