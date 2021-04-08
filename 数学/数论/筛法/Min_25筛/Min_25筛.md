Min_25筛主要用于**积性函数前缀和**. 复杂度为$O(\frac{n^\frac 34}{\log n})$. 相比杜教筛, Min_25筛对求和的函数有不同的要求.

相比杜教筛, Min_25筛更为通用.

###相关定义和要求

* $P$: 质数集合. 其中第$i$小的元素为$P_i$.

* $p_i$: 从小到大第$i$个质数.

* $q(n)$: $n$的最小质因子.

给定积性函数$f(x)$, 我们想求出$F(n)=\sum_{i=1}^nf(i)$.

**要求:** 对于$x\in P$, $f(x)$可以用多项式表示, $f(x^k)$可以快速计算.

我们令$f(p),~p\in P$的表达式为$o(p)$, 例如$f(p)=p-1$的表达式为$o(x)=x-1$ (不要求$x$是质数).

如果$o(x)$是完全积性函数, 我们可以一遍筛出答案.

否则我们需要进行多次Min_25筛. 如$o(x)=x-1$, 我们需要拆成$g(x)=x$和$h(x)=1$计算. 具体实现上, 我们可以在一个$S(n,j)$函数内一并计算$g(x),h(x)$之和.



###方法

#### I. 预处理

我们用埃氏筛或线性筛筛出前$O(\sqrt n)$的质数, 并计算前缀和$\sum_{i=1}^jf(P_i)$.



####II. $g(n,j)$的计算 

令$g(n,j)=\sum_{i=1}^nf(i)[i\in P~或~q(i)>P_j]$. 显然$g(n,j)$表示埃氏筛法用前$j$个质数筛后留下的数的$f$值之和.

我们想要求出$g(n,\infin)=\sum_{i=1}^nf(i)[i\in P]$. 考虑如何求$g(n,j)$. 按照$P_j^2$和$n$的大小关系分情况考虑.
$$
g(n,j)=\cases{g(n,j-1),~~P_j^2>n\\g(n,j-1)-f(P_j)(g(\lfloor\frac n{P_j}\rfloor,j-1)-\sum_{i=1}^{j-1}f(P_i)),~~P_j^2\le n}
$$
其中$g(\lfloor\frac n{P_j}\rfloor,j-1)$表示所有$P_j$的倍数. $\sum_{i=1}^{j-1}f(P_i)$表示小于$P_j$的质数.

至于$g(n,0)$, 我们将所有$n$当做质数处理. 例如$f(p)=p^2$, 则$g(n,0)=\frac{n(n+1)(2n+1)}6-1$. (注意不含$f(1)$)

我们需要对所有$x=\lfloor \frac ni\rfloor$求出$g(x,\infin)$.



####III. $S(n,j)$的计算

记$S(n,j)=\sum_{i=2}^nf(i)[q(i)\ge P_j]$. 即$S(n,j)$表示所有满足最小质因数不小于$P_j$的$i$的$f(i)$之和.
$$
S(n,j)=g(n,\infin)-\sum_{i=1}^{j-1}f(P_i)+\sum_{j\le k,~P_k^2<n}\sum_{1\le e,~P_k^e<n}(f(P_k^e)S(\lfloor\frac{n}{P_k^e}\rfloor,k+1)+f(P_k^{e+1}))
$$
解释: 我们将$S(n,j)$分成两部分计算.

质数部分: $g(n,\infin)-\sum_{i=1}^{j-1}f(P_i)$表示所有合法质数$p$的$f(p)$之和.

合数部分: 对于合法的合数, 我们直接枚举最小质因子及其幂次即可.



####IV. 最终答案和细节

最终答案为$f(1)+S(n,1)$.

具体实现上, 我们预处理所需$g(n,j)$值, 递归计算$S(n,1)$即可. 计算$S$时**无需**记忆化.



### 示例

####示例1 (SPOJ DIVCNTk)

给定$n,k$, 求
$$
S_k(n)=\sum_{i=1}^n\sigma_0(i^k)
$$

##### 解答

设$$f(n)=\sigma_0(n^k)$$. 则$S_k(n)=\sum_{i=1}^nf(i)$. 且
$$
\cases{f(1)=1\\f(p^a)=ak+1}
$$
注意到$o(n)=k+1$不是完全积性函数, 故我们可以计算$r(n)=1$的$g(n,/)$值, 再在计算$S$时将$g(n,\infin)$乘以$k+1$.

初值$g(n,0)=n-1$. 一遍Min_25筛即可.



#### 示例2 (LOJ 6053 - 简单的函数)

给定$n$, 定义积性函数$f(n)$:
$$
\cases{f(1)=1\\f(p^a)=p\oplus a}
$$
求$S(n)=\sum_{i=1}^nf(i)$. $(n\le 10^{10})$

##### 解答

注意到$f(p)=p\oplus 1=\cases{p+1,~~p=2\\p-1,~~p\neq 2}$. 故我们将$p=2$特殊处理, 先当做奇质数, 之后将答案加上$2$即可.

即按照$f(p)=p-1$处理初值, 分别将$g(p)=p$和$h(p)=1$求和.

初值为$g(n,0)=\frac 12n(n+1)-1$和$h(n,0)=n-1$.

计算$S(n,j)$时将二者合并即可. 注意$j=1$时答案要加上$2$ ($p=2$的特判).



####示例3 (UOJ 188 - Sanrd)

定义函数$f(x)$表示$x$的非严格次大质因子. 例如$f(16)=2,f(15)=3$. 规定$f(1)=f(p)=0,p\in P$.

给定$l,r$, 求$\sum_{i=l}^rf(i)$. ($1\le l\le r\le 10^{11}$)

##### 解答

显然问题相当于分两次求$\sum_{i=1}^nf(i)$.

类似DIVCNTK, 我们筛出$g(x)=\sum_{i=1}^x[x\in P]$.

设$q(n)$表示$n$的最小质因子, $S(n,j)=\sum_{i=1}^n[q(i)\ge P_j]f(i)$.

考虑如何计算$S(n,j)$. 同正常的Min_25筛一样, 我们枚举满足$j<k,P_k^2<n,~1\le e,P_k^e<n$的$k,e$.

* $P_k$不是次大质因子. 这部分对答案贡献$S(\lfloor\frac{n}{P_k^e}\rfloor,k+1)$.
* $P_k$是次大质因子. 这部分贡献$P_k\sum_{i=P_k}^{\lfloor\frac n{P_k^e}\rfloor}[i\in P]$. 后面一部分相当于对最大质因子的枚举.

最终答案为$S(n,1)$.



### 参考资料

[Min_25筛](https://www.cnblogs.com/zhoushuyu/p/9187319.html)

[一种筛法](http://www.cnblogs.com/zzqsblog/p/8302815.html)

[筛法总结](https://blog.csdn.net/WAautomaton/article/details/82667522)

[Min_25](https://www.cnblogs.com/cjyyb/p/9185093.html)

[Min_25](https://www.cnblogs.com/zbh2047/p/8552551.html)

