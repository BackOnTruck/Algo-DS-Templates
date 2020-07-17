Suppose $P(x)=p_0+p_1x+p_2x^2+p_3x^3+...p_nx^n$ and $Q(x)=q_0+q_1x+q_2x^2+q_3x^3+...q_mx^m$.

Then $deg(P)=n$ and $deg(Q)=m$.

## Convolution

- **Definition.** $S(x)$ is the convolution of $P(x)$ and $Q(x)$.
  $$
  P(x)Q(x)=S(x)=s_0+s_1x+s_2x^2+s_3x^3+...+s_{n+m}x^{n+m}\space,s_i=\sum_{k=0}^{i}p_kq_{i-k}
  $$

- **Computation.** FTT / NTT, $O(n\log n)$

#### Special: computing NTT with any mods

Suppose any coefficients are $\le10^9$, and $deg(P),deg(Q)\le10^5$.

##### Method #1

* Choose 3 NTT-friendly primes ($2^pq+1$) ,their product $$\gt10^{23}=(10^9)^2\times10^5$$ , do NTT 3 times , then merge them using China Remainder Theorem (**fast multiply** or **__int128** required).

##### Method #2 (MTT)

* Split each coefficients in the form of $32768a+b$ (the 2 polynomials will be divided into 4) , do FFT, then merge the result. (This method can be used to avoid precision loss.)

## Inverse

* **Problem.** Given $P(x)\pmod{x^n}$ , we want to compute $P(x)^{-1}\pmod{x^n}$. In other words, we are to find
  $$
  Q(x)\space s.t.\space P(x)Q(x)\equiv1\pmod{x^n}
  $$

* **Solution.**

  * For $n=1$, $Q(x)\equiv p_0^{-1}\pmod x$.

  * Suppose we found that $P(x)Q'(x)\equiv1\pmod{x^{\lceil\frac{n}{2}\rceil}}$ , then we have
    $$
    Q(x)-Q'(x)\equiv0\pmod{x^{\lceil\frac{n}{2}\rceil}}
    $$

    $$
    Q(x)^2-2Q(x)Q'(x)+Q'(x)^2\equiv0\pmod{x^n}
    $$

    $$
    Q(x)\equiv2Q'(x)-P(x)Q'(x)^2\pmod{x^n}
    $$

    We can compute convolution using NTT$\pmod{998244353}$ or MTT (other mods).

    Thus, the time complexity is $O(n\log n)$.

## Division

* **Problem.** Given $A(x)$, $D(x)$. Suppose $A(x)=D(x)Q(x)+R(x)$, $deg(A)=n$, $deg(D)=m$. Compute $Q(x)$ and $R(x)$.

* **Definition.** Suppose $n=deg(A)$. $A^R(x)=x^nA(\frac{1}{x})$. 

* **Lemma.** If $A(x)=a_0+a_1x+a_2x^2+...+a_nx^n$ then $A^R(x)=a_n+a_{n-1}x+a_{n-2}x^2+...+a_0x^n$.

* **Solution.** From $A(x)=D(x)Q(x)+R(x)$, we have $deg(Q)=n-m$ , $deg(R)=m-1$ , and
  $$
  A(\frac{1}{x})=D(\frac{1}{x})Q(\frac{1}{x})+R(\frac{1}{x})
  $$

  $$
  x^nA(\frac{1}{x})=x^mD(\frac{1}{x})x^{n-m}Q(\frac{1}{x})+x^{n-m+1}x^{m-1}R(\frac{1}{x})
  $$

  $$
  A^R(x)=D^R(x)Q^R(x)+x^{n-m+1}R^R(x)
  $$

  $$
  A^R(x)\equiv D^R(x)Q^R(x)\pmod{x^{n-m+1}}
  $$

  So we have $Q^R(x)\equiv A^R(x)D^R(x)^{-1}\pmod{x^{n-m+1}}$. We can compute $R(x)$ afterwards.

## Newton's Method

* **Problem.** Given $G(x)$, compute $F(x)\pmod{x^n}$ such that $G(F(x))\equiv0\pmod{x^n}$.

* **Solution.**

  * First when $n=1$, we need to find $F(x)$ such that $G(F(x))\equiv0\pmod x$.

  * Suppose we know that $G(F_0(x))\equiv0\pmod{x^{\lceil\frac{n}{2}\rceil}}$. From Taylor Series,
    $$
    G(F(x)) \equiv  G(F_0(x)) + \frac{G'(F_0(x))}{1!}(F(x) - F_0(x)) + \frac{G''(F_0(x))}{2!}(F(x) - F_0(x))^2 + \cdots \\ \equiv  G(F_0(x)) + {G'(F_0(x))}(F(x) - F_0(x))\pmod{x^n}
    $$
    Because $G(F(x))\equiv0\pmod{x^n}$, we get
    $$
    F(x)\equiv F_0(x)-\frac{G(F_0(x))}{G'(F_0(x))}\pmod{x^n}
    $$



## Square Root

* **Problem.** Given $A(x)$, find $F(x)^2\equiv A(x)\pmod{x^n}$.

* **Solution.** Let $G(F(x))=F(x)^2-A(x)$, so $G'(F(x))=2F(x)$. Suppose $G(F_0(x))\equiv0\pmod{x^{\lceil\frac{n}{2}\rceil}}$.

  Using Newton's Method, we get
  $$
  F(x)\equiv F_0(x)-\frac{F_0(x)^2-A(x)}{2F_0(x)}\equiv\frac{F_0(x)^2+A(x)}{2F_0(x)}\equiv\frac{F_0(x)}{2}+\frac{A(x)}{2F_0(x)}\pmod{x^n}
  $$
  For $n=1$, it's $f_0^2\equiv a_0\pmod x$. This may be computed by Cipolla's Algorithm in $O(\log n)$ time.

## Logarithm

* **Problem.** Compute $\ln A(x)$.

* **Solution.** 
  $$
  \frac{\text{d}\ln A(x)}{\text{d}x}=\frac{\text{d}\ln A(x)}{\text{d}A(x)}\frac{\text{d}A(x)}{\text{d}x}=\frac{A'(x)}{A(x)}
  $$

  $$
  \ln A(x)=\int\frac{A'(x)}{A(x)}\text dx
  $$



##Exponentiation

* **Problem 1.** Compute $e^{A(x)}$. **(It is guaranteed that $a_0=0$)**

* **Solution.** Let $G(F(x))=\ln F(x)-A(x)$. So $G'(F(x))=\frac{1}{F(x)}$. Suppose $G(F_0(x))\equiv0\pmod{x^{\lceil\frac{n}{2}\rceil}}$.
  $$
  F(x)\equiv F_0(x)-\frac{\ln F_0(x)-A(x)}{\frac{1}{F_0(x)}}\equiv F_0(x)(1-\ln F_0(x)+A(x))\pmod{x^n}
  $$
  For $n=1$, $F(x)\equiv 1\pmod x$.

* **Problem 2.** Compute $P(x)^a$.

* **Solution.** 
  $$
  P(x)^a=e^{a\ln P(x)}
  $$



## Triangular Functions

We are going to compute triangular functions of polynomials modulo $p$. We have:
$$
e^{\text ix}=\cos x+\text i\sin x
$$
Suppose $\text{i}^2\equiv-1\pmod p$.
$$
\sin P(x)=\frac{e^{\text{i}P(x)}-e^{-\text{i}P(x)}}{2\text{i}}
$$

$$
\cos P(x)=\frac{e^{\text iP(x)}+e^{-\text iP(x)}}2
$$

Since
$$
\frac{\text d\arcsin x}{\text dx}=\frac 1{\sqrt{1-x^2}}
$$

$$
\frac{\text d\arctan x}{\text dx}=\frac 1{1+x^2}
$$

We have
$$
\arcsin P(x)=\int\frac{P^\prime(x)}{\sqrt{1-P^2(x)}}\text dx
$$

$$
\arctan P(x)=\int\frac{P^\prime(x)}{1+P^2(x)}\text dx
$$

