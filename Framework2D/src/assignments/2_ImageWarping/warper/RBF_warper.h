#pragma once

#include "warper.h"
#include <iostream>
#include <vector>
#include <Eigen/Dense>

#define RBF_EPSILON 1e-5f   // RBF threshold

namespace USTC_CG
{
class RBFWarper : public Warper
{
   public:
    RBFWarper() = default;

    virtual ~RBFWarper() = default;

    // Constructor, input control points to define the warping method
    RBFWarper(const std::vector<ImVec2>& source_points, const std::vector<ImVec2>& target_points);
    
    ImVec2 warp(const ImVec2& input) override;

    private:
     std::vector<ImVec2> s_;    // source control points
     Eigen::MatrixXf alpha_;
     std::vector<float> r_; 

     float dist(const ImVec2& p1, const ImVec2& p2) const;
};
}  // namespace USTC_CG