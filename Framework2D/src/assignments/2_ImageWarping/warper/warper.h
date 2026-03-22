#pragma once

#include <imgui.h>

namespace USTC_CG
{
class Warper
{
   public:
    virtual ~Warper() = default;

    virtual ImVec2 warp(const ImVec2& input) = 0;
};
}  // namespace USTC_CG