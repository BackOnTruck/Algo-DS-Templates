### 子集枚举相关

如果我们需要求子集前缀和, 即对于任意集合$S$, 存在一个数$a_S$, 我们希望求出$s_S=\sum_{S\sub T}a_T$,

我们可以使用以下代码 (集合$S$用bitmask表示, $lim=2^{|S|}$, 数组$a$的范围为$[0,lim)​$ ):

```cpp
for(int i=1;i<lim;i<<=1)
		for(int j=0;j<lim;j+=i<<1)
			for(int k=0;k<i;k++)a[j+k]+=a[j+k+i];
```

执行完毕后数组$a$转化为前缀和$s$.