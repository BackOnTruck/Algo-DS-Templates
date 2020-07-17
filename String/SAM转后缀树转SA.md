### SAM转后缀树转SA

以下定义$S$为原串, $S^R$为反串.

#### SAM转后缀树

* **$S^R$的SAM的parent树是$S$的后缀树.**

例如, 如果$S^R$的SAM有fail指针`AX`$\leftarrow$`AAAX`, 则$S$的后缀树有连边`XA`$\rightarrow$`XAAA`.

##### 做法

建出$S^R$的SAM, 用parent树求出$S$的后缀树.

对于所有SAM的结点, 我们原样保留. 转移边就是原来的fail指针.

最后将$S^R$的所有前缀结点设置为终结结点即可.



#### 后缀树转SA

直接在后缀树上按字典序遍历每个后缀即可得出SA.



以上两个算法的复杂度均为$O(n)$. 但SAM常数较大, 不一定优于用$O(n\log n)$的倍增法构造SA.