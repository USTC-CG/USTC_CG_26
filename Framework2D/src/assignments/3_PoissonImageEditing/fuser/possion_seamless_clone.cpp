#include "possion_seamless_clone.h"

#include <algorithm>
#include <cmath>
#include <vector>

namespace USTC_CG
{
// clamp double to [0,255] avoids weird colors
inline unsigned char clamp_rgb(double v)
{
    if (v < 0.0)
        return 0;
    if (v > 255.0)
        return 255;
    return static_cast<unsigned char>(std::round(v));
}

// read pixel at (x, y) in channel c as double, optionally return zero
inline double
read_channel(const Image& img, int x, int y, int c, bool zero_outside)
{
    const bool out_of_bounds =
        (x < 0 || x >= img.width() || y < 0 || y >= img.height());
    if (out_of_bounds)
    {
        if (zero_outside)
            return 0.0;
        x = std::clamp(x, 0, img.width() - 1);
        y = std::clamp(y, 0, img.height() - 1);
    }
    return static_cast<double>(img.get_pixel(x, y)[c]);
}

bool PossionSeamlessClone::build_and_factorize_A(const Image& mask)
{
    // get size
    const int w = mask.width();
    const int h = mask.height();
    const int n = w * h;

    // put pixels in the mask to pixels[], if outside, -1, else set to 0, 1, 2,
    // ...
    std::vector<int> pixels(n, -1);
    int cnt_selected = 0;
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            if (mask.get_pixel(x, y)[0] > 0)
            {
                pixels[index(x, y, w)] = cnt_selected;
                ++cnt_selected;
            }
        }
    }

    // if no pixel selected, return true directly
    if (cnt_selected == 0)
    {
        A_.resize(0, 0);
        return true;
    }

    // Delta f = 4f(p) - f(right) - f(left) - f(down) - f(up)
    A_.resize(cnt_selected, cnt_selected);
    std::vector<Eigen::Triplet<double>> trips;  // trips: (row, col, value)
    trips.reserve(cnt_selected * 5);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            const int row = pixels[index(x, y, w)];
            if (row < 0)
                continue;

            // center pixel
            trips.emplace_back(row, row, 4.0);

            // right
            if (x + 1 < w)
            {
                const int col = pixels[index(x + 1, y, w)];
                if (col >= 0)
                    trips.emplace_back(row, col, -1.0);
            }
            // left
            if (x - 1 >= 0)
            {
                const int col = pixels[index(x - 1, y, w)];
                if (col >= 0)
                    trips.emplace_back(row, col, -1.0);
            }
            // down
            if (y + 1 < h)
            {
                const int col = pixels[index(x, y + 1, w)];
                if (col >= 0)
                    trips.emplace_back(row, col, -1.0);
            }
            // up
            if (y - 1 >= 0)
            {
                const int col = pixels[index(x, y - 1, w)];
                if (col >= 0)
                    trips.emplace_back(row, col, -1.0);
            }
        }
    }

    A_.setFromTriplets(trips.begin(), trips.end());
    solver_.compute(A_);
    return solver_.info() == Eigen::Success;
}

std::shared_ptr<Image> PossionSeamlessClone::fuse(
    const Image& source,
    const Image& target,
    const Image& mask,
    int offset_x,
    int offset_y)
{
    auto result = std::make_shared<Image>(target);
    const int w = mask.width();
    const int h = mask.height();

    // scan the mask, get selected pixels, selected_pixels[i] = (x, y);
    // pixel_to_id[y * w + x] = i
    std::vector<std::pair<int, int>> selected_pixels;
    std::vector<int> pixel_to_id(w * h, -1);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            if (mask.get_pixel(x, y)[0] > 0)
            {
                pixel_to_id[y * w + x] = selected_pixels.size();
                selected_pixels.push_back({ x, y });
            }
        }
    }

    const int cnt = static_cast<int>(selected_pixels.size());

    build_and_factorize_A(mask);

    // get right hand side B
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(cnt, 3);
    for (int i = 0; i < cnt; ++i)
    {
        int x = selected_pixels[i].first;
        int y = selected_pixels[i].second;

        int tx = x + offset_x,
            ty = y + offset_y;  // target coordinates (tx, ty)

        for (int c = 0; c < 3; ++c)
        {
            double rhs = 0;
            double boundary_term = 0;
            double gp = read_channel(source, x, y, c, false);
            double fp = read_channel(target, tx, ty, c, true);

            // Right
            {
                int nx = x + 1, ny = y;
                double s_grad = gp - read_channel(source, nx, ny, c, false);
                double t_grad = fp - read_channel(target, tx + 1, ty, c, true);
                if (use_mixed_gradient_ && std::abs(t_grad) > std::abs(s_grad))
                    rhs += t_grad;
                else
                    rhs += s_grad;

                if (!(nx >= 0 && nx < w && ny >= 0 && ny < h &&
                      mask.get_pixel(nx, ny)[0] > 0))
                {
                    boundary_term += read_channel(target, tx + 1, ty, c, true);
                }
            }
            // Left
            {
                int nx = x - 1, ny = y;
                double s_grad = gp - read_channel(source, nx, ny, c, false);
                double t_grad = fp - read_channel(target, tx - 1, ty, c, true);
                if (use_mixed_gradient_ && std::abs(t_grad) > std::abs(s_grad))
                    rhs += t_grad;
                else
                    rhs += s_grad;

                if (!(nx >= 0 && nx < w && ny >= 0 && ny < h &&
                      mask.get_pixel(nx, ny)[0] > 0))
                {
                    boundary_term += read_channel(target, tx - 1, ty, c, true);
                }
            }
            // Down
            {
                int nx = x, ny = y + 1;
                double s_grad = gp - read_channel(source, nx, ny, c, false);
                double t_grad = fp - read_channel(target, tx, ty + 1, c, true);
                if (use_mixed_gradient_ && std::abs(t_grad) > std::abs(s_grad))
                    rhs += t_grad;
                else
                    rhs += s_grad;

                if (!(nx >= 0 && nx < w && ny >= 0 && ny < h &&
                      mask.get_pixel(nx, ny)[0] > 0))
                {
                    boundary_term += read_channel(target, tx, ty + 1, c, true);
                }
            }
            // Up
            {
                int nx = x, ny = y - 1;
                double s_grad = gp - read_channel(source, nx, ny, c, false);
                double t_grad = fp - read_channel(target, tx, ty - 1, c, true);
                if (use_mixed_gradient_ && std::abs(t_grad) > std::abs(s_grad))
                    rhs += t_grad;
                else
                    rhs += s_grad;

                if (!(nx >= 0 && nx < w && ny >= 0 && ny < h &&
                      mask.get_pixel(nx, ny)[0] > 0))
                {
                    boundary_term += read_channel(target, tx, ty - 1, c, true);
                }
            }

            B(i, c) = rhs + boundary_term;
        }
    }

    // solve AX = B, separately for each channel
    for (int c = 0; c < 3; ++c)
    {
        Eigen::VectorXd X = solver_.solve(B.col(c));

        for (int i = 0; i < cnt; ++i)
        {
            int tx = selected_pixels[i].first + offset_x,
                ty = selected_pixels[i].second + offset_y;

            if (tx >= 0 && tx < target.width() && ty >= 0 &&
                ty < target.height())
            {
                auto p = result->get_pixel(tx, ty);
                p[c] = clamp_rgb(X[i]);
                result->set_pixel(tx, ty, p);  // right back
            }
        }
    }

    return result;
}

void PossionSeamlessClone::clear_cache()
{
    A_.resize(0, 0);
    solver_.compute(A_);
}

}  // namespace USTC_CG