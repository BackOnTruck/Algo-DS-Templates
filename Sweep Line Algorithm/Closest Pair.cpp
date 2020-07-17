#include<bits/stdc++.h>
using namespace std;
struct point
{
	double x,y;
	point(){}
	point(double a,double b):x(a),y(b){}
	bool operator>(const point &p)const{return x<p.x;}
	bool operator<(const point &p)const{return y<p.y||(y==p.y&&x<p.x);}
}p[300001];
inline double dist(point a,point b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
int n;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%lf%lf",&p[i].x,&p[i].y);
	sort(p,p+n,greater<point>());
	double ans=1e36;
	set<point> s;
	s.insert(p[0]);
	for(int i=1,j=0;i<n;i++)
	{
		while(j<i&&p[i].x-p[j].x>ans)s.erase(p[j++]);
		auto l=s.lower_bound(point(0,p[i].y-ans)),r=s.upper_bound(point(1e10,p[i].y+ans));
		for(auto it=l;it!=r;it++)ans=min(ans,dist(*it,p[i]));
		s.insert(p[i]);
	}
	printf("%.4f\n",ans);
	return 0;
}
