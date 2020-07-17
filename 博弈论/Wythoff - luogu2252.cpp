#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b;
	cin>>a>>b;
	if(a>b)swap(a,b);
	cout<<(int((1+sqrt(5))/2*(b-a))!=a)<<'\n';
}
