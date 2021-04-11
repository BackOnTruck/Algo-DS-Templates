// gcd: find (x,y) that ax+by = gcd(a,b)
// inv: find x that ax ≡ gcd(a,m) (mod m) and 0≤x<m
void gcd(int a,int b,int &d,int &x,int &y)
{
	if(!b){d=a;x=1;y=0;return;}
	gcd(b,a%b,d,y,x);
	y-=a/b*x;
}
int inv(int a,int m)
{
	int d,x,y;
	gcd(a,m,d,x,y);
	return (x%m+m)%m;
}
