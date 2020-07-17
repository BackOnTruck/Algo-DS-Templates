#### Cipolla算法 - 在$O(\log n)$时间内求解$x^2\equiv a\pmod p$

###### 问题

给定**质数**$p$和整数$a$, 求满足$x^2\equiv a\pmod p$的$x$.

注意到$p=2$时有解$x\equiv \pm a\pmod p$. 因此只考虑$p$为奇质数的情况.



######前置技能

* $(a+b)^p\equiv a^p+b^p\pmod p$ (由二项式定理可证)

* 二次剩余: 若上述同余方程有解, 则称$a$为模$p$意义下的二次剩余.

* 勒让德符号 ($p$为奇质数):

$$
\left(\frac ap\right)=\begin{cases}1,~~~~~a为p的二次剩余\\-1,~~a不为p的二次剩余\\0,~~~~~p|a\end{cases}
$$

* 欧拉判别法: 

$$
\left(\frac ap\right)\equiv a^\frac{p-1}2\pmod p
$$

**证明.**  当$x^2\equiv a\pmod p$有解时, $a^\frac{p-1}2\equiv x^{p-1}\equiv 1\pmod p$.

无解时, 对于$1\le i\lt p$, 均有唯一的$1\le j\lt p,~i\ne j$使得$ij\equiv a\pmod p$. 根据威尔逊定理, $(p-1)!\equiv -1\pmod p$, 从而$a^\frac{p-1}2\equiv -1\pmod p$.

$p|a$时显然.



* 使方程$x^2\equiv a\pmod p$有解的$a$在模$p$意义下共有$\frac{p+1}2$个.

**证明.** 对于$u^2\equiv v^2\pmod p$, 有$p|(u+v)(u-v)$. 在$u\not\equiv v\pmod p$时, 有$p|u+v$.

而模$p$意义下共有$p$个数, 除去$0$, 剩下的数可以两两分组. 每一组数$(x,y)$满足$p|x+y$, 即$x^2\equiv y^2\pmod p$.

从而结论成立.



###### 算法步骤

* 我们要求方程$x^2\equiv n\pmod p$的解. 假设此方程有解.

* 随机一个数$a$使$a^2-n$不是二次剩余.

  * 即, $(a^2-n)^\frac{p-1}2\equiv -1\pmod p$.
  * 随机的次数为$O(1)$, 检验时使用快速幂. 这一步的总复杂度为$O(\log n)$.

* 类比复数, 定义$\omega=\sqrt{a^2-n}$为模$p$意义下的虚数单位元. 

* 引入域$\bold F_{p^2}$, 这个域中的所有数都可以表示为$a+b\omega$. ($a,b$为整数) 类比复数引入加法和乘法.

* 可以验证:
  $$
  \begin{aligned}(a+\omega)^{p+1}&=(a+\omega)^p(a+\omega)\\&\equiv (a^p+\omega^p)(a+\omega)\\&\equiv (a-\omega)(a+\omega)\\&\equiv a^2-\omega^2\\&\equiv n\pmod p\end{aligned}
  $$

* 取$x=\pm(a+\omega)^\frac{p+1}2$即可. 由拉格朗日定理可得, $x$的虚部为$0​$.

