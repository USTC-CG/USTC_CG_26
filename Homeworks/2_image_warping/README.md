# 2. 图像变形 Image Warping

> 作业步骤：
> - 阅读[文档](documents/README.md)，内含多个小教程
> - 在[项目目录](../../Framework2D/)中编写作业代码
> - 按照[作业规范](../README.md)提交作业

## 作业递交

- 递交内容：程序代码及实验报告 
- 递交时间：2026年3月15日（周日）晚

## 要求

- 实现（至少）两种 warping 算法（文档中已给出数学原理）
  - [Inverse distance-weighted interpolation method (IDW)](documents/0_IDW.md)
  - [Radial basis functions interpolation method (RBF)](documents/1_RBF.md)
- 巩固面向对象编程（OOP）思想
  - 巩固**抽象**：
    - 数学变换的抽象
    - 数学变换与图像无关（类的**解耦**）
  - 封装、继承、多态
- 白缝填补（optional）
- 了解简易的神经网络（optional）
- 作业实验报告范例：[示例参考](https://rec.ustc.edu.cn/share/97ce81a0-dc93-11ee-8634-cbdc421a711c)

## Extra：3D框架配置
在HW2-HW4期间,大家可以开始配置在HW5之后会用到的3D框架了。配置方法参见[3D框架配置说明](./documents/3DFramework.md)

完成配置之后，需要大家根据视频完成一个小动画练习。放心，一行代码都不用写，照着视频来就行

[点我前往Video](https://pan.ustc.edu.cn/share/index/ea5a20a663b247f2823e)

如果完成了3D框架的配置任务，**可获得0.1分的作业加分**，规则如下：
1. 该0.1分会直接加在你的最终作业评分上，不参与一般评分中的多尺度分数的平均计算
2. 该加分仅在原始分数<5时生效。加分后大于5者取5
3. 该加分项仅在HW2-HW4期间有效，且一人仅可加分一次

完成该部分内容后，**请录制运行成功的视频，并附加到作业压缩包中提交**！

## 目的

- 实现（至少）两种 warping 算法（[IDW](documents/0_IDW.md) 和 [RBF](documents/1_RBF.md)）：理解数学原理
- 线性方程组的求解：自己实现或者学习 Eigen 库的调用（提供[配置教程](documents/eigen_example/README.md)）
- 巩固面向对象编程思想
- 白缝填补（optional）：学习使用 [ANN](documents/ann_example/README.md)
- 用深度神经网络实现 warping（optional）：学习配置第三方库和使用 [Dlib](https://dlib.net)


## 提供的材料

依照上述要求和方法，根据说明文档`(1) documents`和作业框架`(2) Framework2D`的内容进行练习。

### (1) 说明文档 `documents` [->](documents/) 

本次作业的要求说明和一些辅助资料

### (2) 作业项目 `Framework2D` [->](../../Framework2D/) 

作业的基础代码框架

