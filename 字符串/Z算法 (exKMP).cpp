#include<bits/stdc++.h>
using namespace std;
string s,t;
int z[2100001];
int main()
{
	cin>>s>>t;
	s=' '+t+s;
	int n=(int)s.size()-1;
	z[1]=n;
	int l=1,r=1;
	for(int i=2;i<=n;i++)
		if(z[i-l+1]<r-i+1)z[i]=z[i-l+1];
		else
		{
			if(i<=r)z[i]=r-i+1;
			while(z[i]+i<=n&&s[z[i]+i]==s[z[i]+1])z[i]++;
			l=i,r=i+z[i]-1;
		}
	for(int i=(int)t.size()+1;i<=n;i++)
		if(z[i]>=t.size())cout<<i-t.size()<<' ';
	cout<<'\n';
}
