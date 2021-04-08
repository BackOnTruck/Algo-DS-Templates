### 辛普森公式

$$
\int_a^bf(x)\text{d}x\approx\frac{b-a}{6}(f(a)+4f(\frac{a+b}{2})+f(b))
$$

### 自适应辛普森法

为了提高精度, 计算$\int_a^bf(x)\text{d}x$时可以比较直接计算和取中点分别计算的差值, 若精度足够则直接计算, 否则取中点递归计算, 即递归分别求出$\int_a^mf(x)\text dx$和$\int_m^bf(x)\text dx$ ($m=\frac{a+b}{2}$).