# Radial basis functions interpolation method [^RBF] 

## 问题描述

**Input:** 给定 $n$ 对控制点 $(\boldsymbol{p}_i, \boldsymbol{q}_i)$ ，其中 $\boldsymbol{p}_i,\boldsymbol{q}_i\in\mathbb{R}^2$ ， $i=1, 2, \cdots,n$ ，

**Output:** 插值映射 $f : \mathbb{R}^2\to\mathbb{R}^2$ ，满足

$$f(\boldsymbol{p}_i) = \boldsymbol{q}_i, \quad \text{for } i = 1, 2, \cdots, n.$$

## 算法原理

假设所求的插值函数 $f$ 是如下径向部分加上仿射部分的形式

$$f(\boldsymbol{p}) = A(\boldsymbol{p}) + R(\boldsymbol{p}),$$

其中仿射变换部分满足

$$A(\boldsymbol{p}) = \boldsymbol{A}\boldsymbol{p} + \boldsymbol{b}$$

径向部分由若干个**径向**基函数组合而成

$$R(\boldsymbol{p})=\sum _ {i=1}^n \boldsymbol{\alpha} _ i g_i(\Vert\boldsymbol{p} - \boldsymbol{p}_i\Vert),\quad \boldsymbol{\alpha}_i\in \mathbb R^2$$

这里的径向基函数也有较大的选取自由，可以取

$$g_i(d) = (d^2 + r_i^2)^{\pm 1/2}, \quad r_i = \min_{j\neq i} \Vert\boldsymbol{p_i} - \boldsymbol{p_j}\Vert.$$

上述映射 $f$ 有 $2(n+3)$ 个自由度（矩阵 $\boldsymbol{A}$，向量 $\boldsymbol{b}$，以及 $n$ 个二维向量 $\boldsymbol{\alpha} _ i$），插值条件

$$f(\boldsymbol{p} _ j)=\sum _ {i=1}^n\boldsymbol{\alpha} _ i g_i(\Vert\boldsymbol{p} _ j-\boldsymbol{p} _ i\Vert)+A\boldsymbol{p} _ j+\boldsymbol{b}=\boldsymbol{q} _ j,\quad j=1,\dots,n.$$

提供了 $2n$ 个约束。有以下的求解方法：

- 直接取 $\boldsymbol{A} = \boldsymbol{I}, \boldsymbol{b} = \boldsymbol{0}$ 是恒同映射，剩下的 $2n$ 个变量通过求解方程组确定；
- 如果提供了一个点，可以选取 $\boldsymbol{A}(\boldsymbol{p})$ 为平移变换，$A=I$ ， $\boldsymbol{b}=\boldsymbol{q}_1-\boldsymbol{p}_1$；
- 如果提供了两个点，可以选取 $\boldsymbol{A}(\boldsymbol{p})$ 为平移+缩放；
- 一般地，如果提供了至少三个点，可以通过求解最小二乘问题确定仿射变换
  
  $$\min \sum_{i=1}^n\Vert\boldsymbol{A}\boldsymbol{p}_i + \boldsymbol{b} - \boldsymbol{q}_i\Vert^2.$$

- 也可以补充约束求解所有 $2(n+3)$ 个变量
  
$$\begin{pmatrix}
\boldsymbol{p} _ 1 & \cdots &\boldsymbol{p} _ n \newline
1 & \cdots &1
\end{pmatrix} _ {3\times n}
\begin{pmatrix}
\boldsymbol{\alpha} _ 1^\top\newline
\vdots\newline
\boldsymbol{\alpha} _ n^\top
\end{pmatrix} _ {n\times 2} = \boldsymbol{0} _ {3\times 2}.$$

## 参考文献

[^RBF]: Arad N, Reisfeld D. [**Image warping using few anchor points and radial functions**](https://onlinelibrary.wiley.com/doi/10.1111/1467-8659.1410035 )[C]//Computer graphics forum. Edinburgh, UK: Blackwell Science Ltd, 1995, 14(1): 35-46.

