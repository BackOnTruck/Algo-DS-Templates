void gcd(int a,int b,int &d,int &x,int &y)
{
	if(!b){d=a;x=1;y=0;return;}
	gcd(b,a%b,d,y,x);
	y-=a/b*x;
}
// find (x,y) that ax+by = gcd(a,b)
