#include<bits/stdc++.h>
using namespace std;
int n,m,tot=0,prime[3000001],x;
bool f[10000011];
int main()
{
	scanf("%d%d",&n,&m);
	f[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!f[i])prime[tot++]=i;
		for(int j=0;j<tot;j++)
		{
			if(1ll*prime[j]*i>n)break;
			f[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
	while(m--)scanf("%d",&x),puts(f[x]?"No":"Yes");
	return 0;
}
