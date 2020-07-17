### min-max容斥

给定集合$S$, 则有:
$$
\max(S)=\sum_{T\subseteq S}(-1)^{|T|-1}\min(T)
$$

$$
\min(S)=\sum_{T\subseteq S}(-1)^{|T|-1}\max(T)
$$

min-max容斥对期望同样成立. 即:
$$
E(\max(S))=\sum_{T\subseteq S}(-1)^{|T|-1}E(\min(T))
$$

$$
E(\min(S))=\sum_{T\subseteq S}(-1)^{|T|-1}E(\max(T))
$$

### 例题

#### HDU 4336

有$n$个数, 每次你有$p_i$的概率获得第$i$个数 ($\sum p_i=1$). 求期望多少次后所有数至少获得一次.

##### 题解

记$\max(S)$为$S$中最后获得的那种卡片第一次获得的期望时间, $\min(S)$为$S$中的第一个获得的那种卡片第一次获得的期望时间. 用第一个公式计算即可. 其中
$$
\min(T)=\frac1{\sum_{i\in T}p_i}
$$
​																																																																																																																																																																											

