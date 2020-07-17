#include<bits/stdc++.h>
using namespace std;
vector<int> w[51];
int q,n;
long long H[51][51];
long long h(int u,int p)
{
	vector<long long> f;
	for(int v:w[u])
		if(v!=p)f.push_back(h(v,u));
	sort(f.begin(),f.end());
	long long ans=0;
	for(long long x:f)ans=ans*4029+x;
	return ans*4029+1009;
}
int main()
{
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>n;
		for(int j=0;j<=n;j++)w[j].clear();
		for(int j=1,x;j<=n;j++)
		{
			cin>>x;
			if(x)w[x].push_back(j),w[j].push_back(x);
		}
		for(int j=1;j<=n;j++)H[i][j]=h(j,0);
		sort(H[i]+1,H[i]+1+n);
		for(int j=1,k;j<=n;j++)
		{
			for(k=1;k<=n;k++)
				if(H[i][k]!=H[j][k])break;
			if(k>n){cout<<j<<'\n';break;}
		}
	}
}
