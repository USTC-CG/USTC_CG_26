#include "IDW_warper.h"
#include <cmath>

namespace USTC_CG
{
// initialize the IDW
IDWWarper::IDWWarper(const std::vector<ImVec2>& source_points, const std::vector<ImVec2>& target_points)
    : s_(source_points), t_(target_points)
{
    // initialize basic parameters
    T_.resize(s_.size());   // T_ is the 2x2 transformation matrix for each control point

    // compute every T for each control point
    for (size_t i = 0; i < s_.size(); i++)
    {
        // set matrix A and B to compute T
        Eigen::Matrix2f A = Eigen::Matrix2f::Zero();
        Eigen::Matrix2f B = Eigen::Matrix2f::Zero();

        for (size_t j = 0; j < s_.size(); j++)
        {
            if (i == j) continue;   // skip the control point itself

            float dist = std::sqrt(std::pow(s_[i].x - s_[j].x, 2) + std::pow(s_[i].y - s_[j].y, 2));    // compute the distance between 
            float sigma = std::pow(dist, -mu_);   // compute the weight

            Eigen::Vector2f diff_p(s_[j].x - s_[i].x, s_[j].y - s_[i].y);
            Eigen::Vector2f diff_q(t_[j].x - t_[i].x, t_[j].y - t_[i].y);

            // sum up A and B
            A += sigma * diff_p * diff_p.transpose();
            B += sigma * diff_p * diff_q.transpose();
        }
        // compute T
        T_[i] = B * A.inverse();
    }
}


// specific implementation for IDW warping
ImVec2 IDWWarper::warp(const ImVec2& input)
{
    if (s_.empty()) return input;   // if no control points exist, return directly

    Eigen::Vector2f output(0.0f, 0.0f);
    float total_weight = 0.0f;

    for (size_t i = 0; i < s_.size(); i++)
    {
        // compute the weight
        float dist = std::sqrt(std::pow(input.x - s_[i].x, 2) + std::pow(input.y - s_[i].y, 2));

        // avoid division by zero
        if (dist < IDW_EPSILON) return t_[i];

        float weight = std::pow(dist, -mu_);

        // compute f_i
        Eigen::Vector2f diff_p(input.x - s_[i].x, input.y - s_[i].y);
        Eigen::Vector2f f_i = Eigen::Vector2f(t_[i].x, t_[i].y) + T_[i] * diff_p;

        // 累加：result = sum(w_i * f_i)
        output += weight * f_i;
        total_weight += weight;
    }

    // normalize the result
    if (total_weight > 0.0f) output /= total_weight;

    return ImVec2(output.x(), output.y());
}

}