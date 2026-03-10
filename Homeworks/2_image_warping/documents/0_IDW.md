# Inverse distance-weighted interpolation methods[^IDW]

## 问题描述

**Input:** 给定 $n$ 对控制点 $(\boldsymbol{p}_i, \boldsymbol{q}_i)$ ，其中 $\boldsymbol{p}_i,\boldsymbol{q}_i\in\mathbb{R}^2$ ， $i=1, 2, \cdots,n$ ，

**Output:** 插值映射 $f : \mathbb{R}^2\to\mathbb{R}^2$ ，满足

$$f(\boldsymbol{p}_i) = \boldsymbol{q}_i, \quad \text{for } i = 1, 2, \cdots, n.$$

## 算法原理

假设插值映射 $f$ 具有如下加权平均的形式

$$f(\boldsymbol{p})=\sum_{i=1}^n w_i(\boldsymbol{p})f_i(\boldsymbol{p}),$$

其中 $f_i$ 是在插值节点 $\boldsymbol{p}_i$ 处的局部近似（local approximation），满足在 $(\boldsymbol{p}_i, \boldsymbol{q}_i)$ 的插值性质 $f_i(\boldsymbol{p}_i) = \boldsymbol{q}_i$。权重函数 $w_i$ 满足非负性和归一性

$$\sum_{i=1}^n w_i = 1, \text{and } \ w_i \geq 0, \text{ for } i = 1, 2, \cdots, n,$$

且在 $\boldsymbol{p}_i$ 处 $w_i(\boldsymbol{p}_i) = 1$.

对于任意的 $i$，我们取如下形式的 $w_i$ 和 $f_i$：

- 权重 $w_i: \mathbb{R}^2\to\mathbb{R}$ 形如
  
  $$w_i(\boldsymbol{p}) = \dfrac{\sigma_i(\boldsymbol{p})}{\displaystyle\sum_{j=1}^n\sigma_j(\boldsymbol{p})},$$
  
  其中 
  
  $$\sigma_i(\boldsymbol{p}) = \dfrac{1}{\Vert\boldsymbol{p} - \boldsymbol{p}_i\Vert^\mu},$$ 
  
  $\mu > 1$（比如可以取 $\mu = 2$），在 $\boldsymbol{p}=\boldsymbol{p_i}$ 时 $w_i$ 为1。

- 映射 $f_i: \mathbb{R}^2\to\mathbb{R}^2$ 形如 
  
  $$f_i(\boldsymbol{p})=\boldsymbol{q}_i+\boldsymbol{T}_i(\boldsymbol{p}-\boldsymbol{p}_i),$$
  
  其中 $\boldsymbol{T} _ i$ 是一个 $2\times 2$ 矩阵，通过最小化下面的能量决定（最小二乘问题）：
  
  $$E_i(\boldsymbol{T} _ i) = \sum _ {j=1, j\neq i}^n \sigma_i(\boldsymbol{p}_j)\left\Vert\boldsymbol{q}_i+\boldsymbol{T}_i(\boldsymbol{p}_j-\boldsymbol{p}_i) - \boldsymbol{q}_j\right\Vert^2.$$
  
  > 求解这个最小二乘问题，可以对矩阵 $\boldsymbol{T}_i$ 的各个分量求偏导数，令偏导数等于 0，得到一个关于 $\boldsymbol{T}_i$ 的方程组，可以写作：
  > 
  > $$\frac{\partial E_i}{\partial \boldsymbol{T}_i} =  \sum _ {j=1, j\neq i}^n 2\cdot \sigma_i(\boldsymbol{p}_j)\left(\boldsymbol{q}_i+\boldsymbol{T}_i(\boldsymbol{p}_j-\boldsymbol{p}_i) - \boldsymbol{q}_j\right)\cdot (\boldsymbol{p}_j-\boldsymbol{p}_i)^\top = \boldsymbol{0}$$
  > 
  > 即求解如下的线性方程组
  > 
  > $$\boldsymbol{T}_i \boldsymbol{A} = \boldsymbol{B},$$
  > 
  > 其中
  > 
  > $$\boldsymbol{A} = \sum _ {j=1, j\neq i}^n \sigma_i(\boldsymbol{p}_j)(\boldsymbol{p}_j-\boldsymbol{p}_i) \cdot (\boldsymbol{p}_j-\boldsymbol{p}_i)^\top,$$
  > 
  > $$\boldsymbol{B} = \sum _ {j=1, j\neq i}^n \sigma_i(\boldsymbol{p}_j)(\boldsymbol{q}_j-\boldsymbol{q}_i)\cdot (\boldsymbol{p}_j-\boldsymbol{p}_i)^\top.$$

确定 $f_i$ 和 $w_i$ 之后，就得到了插值映射 $f$.

## 注

可以尝试其他形式的 $\sigma$，例如

$$\sigma_i = \left[\dfrac{(R_i - \Vert\boldsymbol{p} - \boldsymbol{p} _ i\Vert)_{+}}{R_i\Vert\boldsymbol{p} - \boldsymbol{p}_i\Vert}\right]^\mu$$

其中 $R_i$ 是某一个适当大小的正常数，该式将插值点 $\boldsymbol{p}_i$ 的影响控制在了一个范围内。

## 参考文献

[^IDW]: Ruprecht D, Muller H. [**Image warping with scattered data interpolation**](https://ieeexplore.ieee.org/document/365004)[J]. IEEE Computer Graphics and Applications, 1995, 15(2): 37-43.
