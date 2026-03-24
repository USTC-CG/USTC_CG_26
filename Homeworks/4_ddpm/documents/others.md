# 其他可选内容&扩展内容说明

除了基础内容以及Inpaint部分，我们没有在代码中添加相应的功能。请大家**自行修改代码，以实现对应的内容**。这些内容**都不是必做的**，你做多少，我们给多少分

## 文生图

其核心在于去噪过程中，噪声的预测还需要输入对应的**条件**。原始的噪声预测公式为

$$
\epsilon_t = \epsilon_\theta(x_t, t)
$$

仅与图像&时间步相关。而文生图任务中，这个网络的输入会多一个量$c$以指定生成对象，即

$$
\epsilon_t = \epsilon_\theta(x_t, t, c)
$$

常用的特征是[openai/CLIP: CLIP (Contrastive Language-Image Pretraining), Predict the most relevant text snippet given an image](https://github.com/openai/CLIP)，它可以将文本信息编码为对应的特征向量。当然，对于我们仅有两类的数据集，用不着这么复杂的编码方式，我们可以将这个过程简化为手动为两个类别指定不同的编码（比如0或者1），在生成过程中，将它们注入到网络之中，以实现条件控制。注入方式可以**仿照时间步的编码**，也可以**尝试其他的编码方法**。

你需要修改网络的结果以及训练、推理的代码，在我们给的datasets-2数据集上实现两个类别的生成。

## 多图泛化性

你需要扩展数据集的大小，为其添加更多的图片。算力充足的同学可以尝试一下。如果你希望在数据集数量更大的情况下也能达到好的生成效果，可以引入VAE，详情可参考[变分编码器VAE（Variational Auto-Encoder)通俗解读 - 知乎](https://zhuanlan.zhihu.com/p/661966176)

同时多图泛化与上面的文生图任务可以相结合，以生成多种类型的图片。

## Flow Matching

参考我们提供的资料，完成基于Flow Matching的图像生成任务。

https://arxiv.org/abs/2210.02747

[通俗易懂的Flow Matching原理解读（附核心公式推导和源代码） - 知乎](https://zhuanlan.zhihu.com/p/4116861550)

[小白也能懂的flow matching - 知乎](https://zhuanlan.zhihu.com/p/2018059592370771135)

[blog.palind-rome.top/2025/07/13/Flow-Matching（流匹配）学习笔记/](https://blog.palind-rome.top/2025/07/13/Flow-Matching%EF%BC%88%E6%B5%81%E5%8C%B9%E9%85%8D%EF%BC%89%E5%AD%A6%E4%B9%A0%E7%AC%94%E8%AE%B0/)
