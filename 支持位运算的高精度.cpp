#include<bits/stdc++.h>
using namespace std;
const int len=29;
struct bignum
{
	vector<int> t;
	bignum(){t.push_back(0);}
	bignum(int q,int k)
	{
		t.push_back(1);
		while(k--)
		{
			int c=0;
			for(int i=0;i<(int)t.size();i++)
			{
				long long x=1ll*t[i]*q+c;
				t[i]=x&((1<<len)-1);
				c=x>>len;
			}
			if(c)t.push_back(c);
		}
	}
	bool operator[](int k)
	{
		size_t i=k/len;
		if(i>=t.size())return 0;
		return t[i]&(1<<(k%len));
	}
	void operator+=(bignum& a)
	{
		if(a.t.size()>t.size())t.resize(a.t.size(),0);
		int c=0;
		for(size_t i=0;i<t.size();i++)
		{
			t[i]+=(a.t.size()>i?a.t[i]:0)+c;
			if(t[i]>=(1<<len)){t[i]-=1<<len;c=1;}
			else c=0;
		}
		if(c)t.push_back(c);
	}
};
