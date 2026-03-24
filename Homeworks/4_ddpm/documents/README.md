# DDPM作业说明

## 作业框架

### 框架结构

作业框架内结构如下：

- FrameworkDDPM
  - datasets-*: 我们提供的数据集。其中1为单图单类别，2为双图双类别。如果你需要使用自己的数据集，请使用与我们提供的数据集相同的格式，或者参考[torchvision.datasets.ImageFolder](https://docs.pytorch.org/vision/main/generated/torchvision.datasets.ImageFolder.html)官方文档进行创建。
  - requirements.txt： 依赖清单
  - dataloader.py ： 数据集加载相关代码
  - sampling.py ： 待补全的去噪代码
  - forward_noising.py： 待补全的加噪代码
  - training_model.py： 待补全的训练代码
  - unet.py： 网络结构代码

### 框架配置

首先确保本地已安装Python

遵循[PyTorch](https://pytorch.org/)官网的安装引导，安装适合你当前硬件的Pytorch版本

安装其他依赖项

```shell
pip install -r ./requirements.txt
```

## 作业说明

- 基础内容 [->](basics.md)
- 可选内容-Inpainting [->](op-inpainting.md)
- 其他可选内容以及扩展内容 [->](others.md)