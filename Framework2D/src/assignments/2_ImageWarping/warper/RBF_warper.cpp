#include "RBF_warper.h"
#include <cmath>

namespace USTC_CG
{
// initialize the RBF

// get distance between two points
float RBFWarper::dist(const ImVec2& p1, const ImVec2& p2) const
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

RBFWarper::RBFWarper(const std::vector<ImVec2>& source_points, const std::vector<ImVec2>& target_points)
    : s_(source_points)
{
    size_t n = s_.size();
    if (n == 0) return;    // ignore empty control points

    r_.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        float min_dist = 1e10f;   // initialize min_dist as a large value
        for (size_t j = 0; j < n; j++)
        {
            if (i == j) continue;   // skip the control point itself
            min_dist = std::min(min_dist, dist(s_[i], s_[j]));   // update min_dist
        }

        // compute r_i
        r_[i] = (n > 1) ? min_dist : 1.0f;   // avoid r_i being 1e10f when only one control point exists
    }

    // compute matrix G
    Eigen::MatrixXf G(n, n);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            float dSq = std::pow(dist(s_[i], s_[j]), 2);
            G(i, j) = std::sqrt(dSq + r_[j] * r_[j]);   // compute G_ij
        }
    }

    // let A = I, b = 0, the right hand side will be q_i - p_i
    Eigen::MatrixXf B(n, 2);
    for (size_t i = 0; i < n; ++i) {
        B(i, 0) = target_points[i].x - s_[i].x;
        B(i, 1) = target_points[i].y - s_[i].y;
    }

    alpha_ = G.colPivHouseholderQr().solve(B);   // solve for alpha
}

ImVec2 RBFWarper::warp(const ImVec2& input)
{
    if (s_.empty()) return input;

    Eigen::Vector2f output(input.x, input.y);

    // 累加径向基函数的贡献: output += sum( alpha_i * g(||input - p_i||) )
    for (size_t i = 0; i < s_.size(); ++i) {
        float dSq = std::pow(dist(input, s_[i]), 2);
        float g_i = std::sqrt(dSq + r_[i] * r_[i]);
        
        output.x() += alpha_(i, 0) * g_i;
        output.y() += alpha_(i, 1) * g_i;
    }

    return ImVec2(output.x(), output.y());
}

} // namespace USTC_CG