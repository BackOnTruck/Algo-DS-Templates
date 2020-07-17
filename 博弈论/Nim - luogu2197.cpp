#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,x;
	cin>>t;
	while(t--)
	{
		cin>>n;
		int q=0;
		while(n--)cin>>x,q^=x;
		cout<<(q?"Yes\n":"No\n");
	}
}
