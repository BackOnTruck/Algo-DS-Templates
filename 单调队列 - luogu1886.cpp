#include<cstdio>
#include<deque>
using namespace std;
struct num{int v,p;};
int n,k,a[1100001];
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)scanf("%d",a+i);
	deque<num> q;
	for(int i=0;i<n;i++)
	{
		while(!q.empty()&&q.back().v>=a[i])q.pop_back();
		q.push_back({a[i],i});
		if(q[0].p<=i-k)q.pop_front();
		if(i>=k-1)printf("%d ",q[0].v);
	}
	puts("");
	q.clear();
	for(int i=0;i<n;i++)
	{
		while(!q.empty()&&q.back().v<=a[i])q.pop_back();
		q.push_back({a[i],i});
		if(q[0].p<=i-k)q.pop_front();
		if(i>=k-1)printf("%d ",q[0].v);
	}
	puts("");
}
