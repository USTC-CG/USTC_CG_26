# ImageWarping 说明文档

## 学习过程

- 根据 [配置说明](../../../Framework2D/README.md) 配置作业项目代码，把 `2_ImageWarping` 项目跑通；
- 参考[WarpingWidget.cpp](../../../Framework2D/src/assignments/2_ImageWarping/warping_widget.cpp) 中的图像处理函数 `invert()`， `mirror()`，`gray_scale()` 等，学习基本的图像处理，然后仿照 `warping()` 函数示例实现作业中的 `IDW` 和 `RBF` 图像变形方法。我们在待实现位置 `warping()` 处标明了 `HW2_TODO`。根据本文档接下来的教程补充相应的功能，就可以实现这两种算法。

## 提示

- 善用 VS Code 的全局搜索功能，快捷键 `Ctrl+Shift+F`，例如你可以使用这个功能全局搜索 `HW2_TODO` 的提示，帮助快速定位到关键部分。

- 文档已经简单列出了 IDW 算法和 RBF 算法的基本思想和数学公式，实现基本算法即可，不必拘泥于太多细节，对背景知识感兴趣可以去查阅相关的论文文献。

- 目录不要用中文名，否则编译会出错。要习惯用英文来思考，包括代码注释等。养成使用英文的习惯！

- 务必自己独立完成该作业，做得不好没有关系，我们会指出你的问题，一步一步帮你理解该作业需要你所理解的东西，这点极其重要！只有不断从失败中改正才能有长进！我们会帮你逐步纠正错误。

- **符合项目要求的结构设计、实现方法有很多，你不一定要严格按照下面的提示来实现，如果你有更好的想法，请务必实现它，并且在报告文件中详细描述。**

## 目标和要求

- 实现两种 Warping 算法（IDW & RBF）
- 把 Warping 算法的实现从图像处理任务中**解耦**出来，只关心其**数学抽象**
  - 封装 Warping 功能到 [`Warper`](../../../Framework2D/src/assignments/2_ImageWarping/warper/warper.h) 类中，供图像处理组件 [`WarpingWidget`](../../../Framework2D/src/assignments/2_ImageWarping/warping_widget.cpp) 调用；
  - IDW 和 RBF 算法的类实现参考上个作业的 `Shape` 类。
- （optional）白缝填补
- （optional）更多的 Warping 算法

## 0. 面向对象编程思想

通过 [C++ 课前热身练习](../../0_cpp_warmup/) 你已经掌握了面向对象编程的基本思想（类的封装、继承、多态），其理念就是：

- **程序＝对象＋对象＋对象＋…** 

- 对象＝数据结构＋算法

这与面向过程编程（程序＝数据结构＋算法）是不一样的。

## 1. 了解图像操作

如果运行成功，可以看到如下的界面

<div align=center><img width = 75% src ="figs/warp_0.jpg"/></div align>

作为图像编程的入门，我们封装了一个图像类 [`Image`](../../../Framework2D/include/common/image.h) ，其中提供获取和修改图像属性的基本操作，你可以通过阅读 `WarpingWidget::invert()`，`WarpingWidget::mirror()`中的代码，快速上手这些操作，它们分别实现了颜色反转、镜像的图像编辑，一些可能会用到的图像操作如下

```c++
int width(); // 获取宽度
int height(); // 获取高度
int channels(); // 获取通道数，例如 RGB 格式的图像是 3 通道，RGBA 格式的图像是 4 通道

// 获取 (x,y) 位置的像素值，是一个 0~255 值构成的，长度为通道数的数组
std::vector<unsigned char> get_pixel(int x, int y); 

// 设置 (x,y) 位置的像素值，需要输入一个符合通道长度的数组作为这个像素的颜色
// 经过特殊处理，4 通道的 RGBA 图像也可以输入长度为 3 的 RGB 数据 
void set_pixel(int x, int y, const std::vector<unsigned char>& values);
```

你只要看懂 `WarpingWidget::invert()` 等函数，**模仿使用 `Image` 类中的四个函数 ( `width()`, `height()`, `get_pixel()`, `set_pixel()`)** 即可操作图像的处理。不必去看其他图像处理的书籍和知识后才来处理图像编程。建议大家通过该工程来实现一个非常简单的图像算法，比如线性方法的 `Color2Gray` 把图像转灰度。

> **注意整型和浮点型的转换**，图像操作的行列下标是整型，但是在一些操作中，只有转化为浮点型运算才能保证计算的精度。

## 2. 鼠标选点的功能

我们已经提供了一个简单的交互选点操作，它将选定的点在图像中的相对位置记录在

```c++
std::vector<ImVec2> start_points_, end_points_;
```

你可以在 `warping()` 等函数中调用这些属性。

<div align=center><img width = 75% src ="figs/warp_1.jpg"/></div align>

## 3. 实现 warping 操作

单击 `Warping` 按钮，会执行 `warping()` 函数，现在里面的实现是一个（正向的）“鱼眼”变形，基本逻辑是

- 初始化一个图像副本，存储变形之后的数据；
- 为每个像素点 (x, y) 计算变形之后的位置 (x', y')；
- 从原始图像的 (x, y) 位置拷贝像素颜色，添加到新图像的 (x', y') 位置
- 把新图像存储下来

<div align=center><img width = 75% src ="figs/warp_2.jpg"/></div align>

你只需修改上面的第二小步：如何从选中的若干点对，计算符合这些点对的一个图像变形映射。具体而言，你需要实现两种不同的算法 [IDW](0_IDW.md) 和 [RBF](1_RBF.md)。

> 从代码的复用性和可读性考虑，**我们要求把 warping 的核心算法抽象出来封装成（若干个）类，而不是全部实现在 `WarpingWidget` 类里面。**, 图像处理应用 `WarpingWidget` 只需要调用其 `warp` 功能（和 MiniDraw 中的绘制形状类似）。
> 
> 提供的 `fisheye_warping()` 是一种 warping 操作，我们将要实现的 IDW 和 RBF 算法也是一种 warping 操作。能否从我们的任务中抽象出**图像无关**的**数学变换**？
> 
> 回顾 C++ 的面向对象性质，我们需要对 Image Warping 操作进行数学抽象，并设计合理的类结构和接口，在 [2_ImageWarping/](../../../Framework2D/src/assignments/2_ImageWarping/warper/) 下添加合适的 `.h` 文件和 `.cpp` 文件，并且在 `WarpingWidget` 类里面调用它们。

首先，根据 warping 映射的数学抽象修改 [Warper](../../../Framework2D/src/assignments/2_ImageWarping/warper/warper.h) 类，声明一个虚函数 `warp(...)` 作为外部调用的接口。此外，还需要提供输入点列进行初始化的方法。

### 3.1 IDW 方法

算法原理见 [0_IDW.md](./0_IDW.md)。

实现 [IDWWarper](../../../Framework2D/src/assignments/2_ImageWarping/warper/IDW_warper.h) 类，它需要提供我们在父类中声明的 `warp(...)` 接口的一个具体实现。

### 3.2 RBF 方法

算法原理见 [1_RBF.md](./1_RBF.md)。

实现 [RBFWarper](../../../Framework2D/src/assignments/2_ImageWarping/warper/RBF_warper.h) 类，它需要提供我们在父类中声明的 `warp(...)` 接口的一个具体实现。

#### Eigen库

- 实现RBF方法需要求解线性方程组，你可以自己实现，也可以从网上找其他程序或库来用
- 强烈推荐使用 Eigen 库来求解线性方程组，Eigen 库是强大的数学算法库，是计算机图形学必须了解的算法库
- 我们提供了 Eigen 库的使用示例：[eigen_example](./eigen_example/) 

> [eigen_example](eigen_example/) 演示的添加依赖的方式重点掌握，另外为了保证项目的简洁性，不要将依赖部分加到 git 版本管理中，使用 [.gitignore](../../../.gitignore) 忽略掉 [eigen_example/src/_deps/](eigen_example/src/_deps/) 

## 4. 补洞（optional）

结果图像中可能会出现白色空洞或条纹，你需要分析是什么原因造成的。

一种填补这些空洞的方式是利用周围的已知像素进行插值填充。这也是个**插值问题**（即利用空洞周围一定范围的已知像素来插值该像素的颜色）。你可以尝试如何用你实现的 IDW 和 RBF warping 类（或者对这些类简单改造。）来填充这些空洞像素的颜色。

<div align=center><img width = 50% src ="figs/white_stitch.jpg"/></div align>

#### ANN库（Optional）

若你需要用搜索最近点的任务（在补洞的任务中），建议学习使用如下的库：

- [Annoy(Approximate Nearest Neighbors Oh Yeah)](https://github.com/spotify/annoy)

我们提供了测试项目 [ann_example](ann_example/)

## 5. 使用神经网络拟合变形映射（optional）

在给定了输入输出点对之后，除了用 IDW 和 RBF 方法进行插值，得到目标的变形映射，还可以使用各种其他的拟合方法得到对应的映射。神经网络可以作为一种拟合器来拟合这些输入输出点对。因此，同学们可以以 warping 操作为例尝试神经网络的使用。

### Dlib 库的配置

在 C++ 下有一些简单的库实现了神经网络的相关算法，例如 [Dlib](https://dlib.net)。

我们提供了测试项目 [dlib_example](dlib_example/)

### 使用神经网络拟合

给定输入输出的二维点对`source` 和 `target`，我们可以构造输入维度为 2，输出维度为 2 的深度神经网络，例如：

```c++
using warping_net = loss_mean_squared_multioutput<    // loss mean squared
                    fc<2,                  // output layer: 1 dim
                    relu<fc<10,            // hidden layer 2: 10 dim + ReLU activation
                    relu<fc<10,            // hidden layer 1: 10 dim + ReLU activation
                    input<matrix<float>>   // input layer: 1 dim
                    >>>>>>; 
```

配置优化器：

```c++
dnn_trainer<net_type, adam> trainer(net);
```

然后进行训练：

```c++
trainer.train(inputs, targets);
```

得到的网络就是一个拟合所有点对的变形映射。

## 测试图片及报告范例

### 测试例子

须用以下 [**格子图像**](../data/test.png) 来进行测试，可以很清楚看到 warping 方法的特点

<div align=center><img width = 20% src ="../data/test.png"/></div align>

### 作业实验报告范例：[示例参考](https://rec.ustc.edu.cn/share/97ce81a0-dc93-11ee-8634-cbdc421a711c)

### 其他测试图片

- 用户交互示例：

<div align=center><img width = 50% src ="figs/ui_demo.jpg"/></div align>

- 变形效果示例：

<div align=center><img width = 50% src ="figs/warp_demo.jpg"/></div align>
