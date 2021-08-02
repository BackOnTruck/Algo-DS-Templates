#include<iostream>
#include<cmath>
using namespace std;
const double eps=1e-10,pi=acos(-1);
int dcmp(double x) //signum(x)
{
	if(-eps<x&&x<eps)return 0;
	return x>0?1:-1;
}
struct point
{
	double x,y;
	point(double a=0,double b=0):x(a),y(b){}
	//operators
	point operator+(point b)const{return point(x+b.x,y+b.y);}
	point operator-(point b)const{return point(x-b.x,y-b.y);}
	point operator*(double p)const{return point(x*p,y*p);}
	point operator/(double p)const{return point(x/p,y/p);}
	point operator-()const{return point(-x,-y);}
	//comparison
	bool operator<(const point &b)const{return x<b.x||(x==b.x&&y<b.y);}
	bool operator==(const point &b)const{return !dcmp(x-b.x)&&!dcmp(y-b.y);}
	void input(){scanf("%lf%lf",&x,&y);}
};
typedef point vec; //vector
point operator*(double p,point a){return point(a.x*p,a.y*p);}

//Dot product (a·b) & Cross product (a×b)
//complex<double> a,b: dot(a,b) => real(conj(a)*b), cross(a,b) => imag(conj(a)*b)
double dot(vec a,vec b){return a.x*b.x+a.y*b.y;}
double cross(vec a,vec b){return a.x*b.y-a.y*b.x;}

//length of vector a	&	rotate a by x rad	&	unit normal vector of a
//complex<double> a: rotate(a,x) => a*exp(xi)
double length(vec a){return sqrt(dot(a,a));}
vec rotate(vec a,double rad){return vec(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));}
vec normal(vec a)
{
	double len=length(a);
	return vec(-a.y/len,a.x/len);
}

//<a,b> & area of Triangle ABC
double angle(vec a,vec b){return acos(dot(a,b)/length(a)/length(b));}
double area(point a,point b,point c){return cross(b-a,c-a)/2;}

//Intersection of line p+tv and line q+tw
point LineIntersection(point p,vec v,point q,vec w){return p+v*cross(w,p-q)/cross(v,w);}
//Distance from point p to line ab
double Dist(point p,point a,point b)
{
	vec x=b-a,y=p-a;
	return fabs(cross(x,y))/length(x);
}
//Distance from point p to SEGMENT ab
double DistToSeg(point p,point a,point b)
{
	if(a==b)return length(p-a);
	vec v1=b-a,v2=p-a,v3=p-b;
	if(dcmp(dot(v1,v2))<0)return length(v2);
	if(dcmp(dot(v1,v3))<0)return length(v3);
	return fabs(cross(v1,v2))/length(v1);
}
//Line Projection
point LineProj(point p,point a,point b)
{
	vec v=b-a;
	return a+v*dot(v,p-a)/dot(v,v);
}

//Do Segments ab and cd intersect properly?		&	is point p on segment ab?
bool SegInter(point a,point b,point c,point d){return dcmp(cross(b-a,c-a))*dcmp(cross(b-a,d-a))<0&&dcmp(cross(d-c,a-c))*dcmp(cross(d-c,b-c))<0;}
bool on(point p,point a,point b){return !dcmp(cross(a-p,b-p))&&dcmp(dot(a-p,b-p))<0;}

//Area of polygon p
double area(point *p,int n)
{
	double s=0;
	for(int i=2;i<n;i++)s+=cross(p[i-1]-p[0],p[i]-p[0]);
	return s/2;
}
