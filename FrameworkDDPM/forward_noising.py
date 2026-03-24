import torch
import torch.nn.functional as F
import matplotlib.pyplot as plt
from dataloader import load_transformed_dataset, show_tensor_image


def linear_beta_schedule(timesteps, start=0.0001, end=0.02):
    return torch.linspace(start, end, timesteps)


def get_index_from_list(vals, time_step, x_shape):
    """
    Returns a specific index t of a passed list of values vals
    while considering the batch dimension.
    """
    batch_size = time_step.shape[0]
    out = vals.gather(-1, time_step.cpu())
    return out.reshape(batch_size, *((1,) * (len(x_shape) - 1))).to(time_step.device)




# Define beta schedule
T = 300
betas = linear_beta_schedule(timesteps=T)

# Pre-calculate different hyperparameters (alpha and beta) for closed form
alphas = 1.0 - betas
alphas_cumprod = torch.cumprod(alphas, axis=0)
alphas_cumprod_prev = F.pad(alphas_cumprod[:-1], (1, 0), value=1.0)
sqrt_recip_alphas = torch.sqrt(1.0 / alphas)
sqrt_alphas_cumprod = torch.sqrt(alphas_cumprod)
sqrt_one_minus_alphas_cumprod = torch.sqrt(1.0 - alphas_cumprod)
posterior_variance = betas * (1.0 - alphas_cumprod_prev) / (1.0 - alphas_cumprod)



# TODO: 你需要完善这个函数，以实现对输入图像的加噪过程
def forward_diffusion_sample(x_0, time_step, device="cpu"):
    noise = torch.randn_like(x_0)    
    return x_0, noise
