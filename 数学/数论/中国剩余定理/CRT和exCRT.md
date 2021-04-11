### 中国剩余定理（CRT）

给定n个同余方程$x\equiv a_i\pmod{m_i}$, 其中$m_i$两两互质. 求解$x$.

则$x$的唯一解为
$$
x\equiv\sum_{i=1}^na_iM_it_i\pmod M
$$
其中$M=\prod_{i=1}^nm_i$, $M_i=\frac M{m_i}$, $t_i\equiv M_i^{-1}\pmod {m_i}$.

### 扩展中国剩余定理（exCRT）

给定n个同余方程$x\equiv{a_i}\pmod{m_i}$, 求解$x$.

假设已经求出来前$k-1$个方程组的解$x\pmod M$, 其中$M=\text{LCM}^{k-1}_{i=1}m_i$.

现在要求$t$使得$x+tM\equiv a_k\pmod{m_k}$. 转化为$tM\equiv a_k-x\pmod{m_k}$后用exgcd求解即可.

新解为$x'\equiv x+tM\pmod{M'}$, 其中$M'=lcm(M,a_k)$.

