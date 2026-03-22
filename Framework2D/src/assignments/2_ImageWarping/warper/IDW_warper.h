#pragma once

#include "warper.h"
#include <iostream>
#include <vector>
#include <Eigen/Dense>

#define IDW_EPSILON 1e-5f   // IDW threshold

namespace USTC_CG
{
class IDWWarper : public Warper
{
   public:
    IDWWarper() = default;

    // Constructor, input control points to define the warping method
    IDWWarper(const std::vector<ImVec2>& source_points, const std::vector<ImVec2>& target_points);

    virtual ~IDWWarper() = default;
    
    ImVec2 warp(const ImVec2& input) override;

   private:
    std::vector<ImVec2> s_;    // source control points
    std::vector<ImVec2> t_;    // target control points
    std::vector<Eigen::Matrix2f> T_;  // transformation matrices
     const float mu_ = 2.0f;    // mu_ parameter for IDW
};
}  // namespace USTC_CG