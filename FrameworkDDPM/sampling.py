import torch
from forward_noising import (
    get_index_from_list,
    sqrt_one_minus_alphas_cumprod,
    betas,
    posterior_variance,
    sqrt_recip_alphas,
    forward_diffusion_sample,
)
import matplotlib.pyplot as plt
from dataloader import show_tensor_image
from unet import SimpleUnet
import numpy as np
import cv2 as cv


# TODO: 你需要在这个函数中实现单步去噪过程
@torch.no_grad()
def sample_timestep(model, x, t):
    return x

# TODO: 你需要在这个函数中完成对纯高斯噪声的去噪，并输出对应的去噪图片
# 你需要调用上面的sample_timestep函数，以实现单步去噪
@torch.no_grad()
def sample_plot_image(model, device, img_size, T):
    pass

# TODO: 你需要在这个函数中完成模型以及其他相关资源的加载，并调用sample_plot_image进行去噪，以生成图片
def test_image_generation():
    pass

# TODO：你需要在这个函数中实现图像的补充
# Follows: RePaint: Inpainting using Denoising Diffusion Probabilistic Models
@torch.no_grad()
def inpaint(model, device, img, mask, t_max=50):
    return img

# TODO: 你需要在这个函数中完成模型以及其他相关资源的加载，并调用inpaint进行图像补全，以生成图片
def test_image_inpainting():
    pass
    

if __name__ == "__main__":
    test_image_generation()
    test_image_inpainting()