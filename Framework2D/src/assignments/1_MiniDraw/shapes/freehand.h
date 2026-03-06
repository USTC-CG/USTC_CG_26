#pragma once
#include "shape.h"
#include <vector>
#include <imgui.h>

namespace USTC_CG {
class Freehand : public Shape
{
   public:
    Freehand(float x, float y)
    {
        points_.push_back({ x, y });
    }

    void draw(const Config& config) const override;
    
    void update(float x, float y) override;

   private:
    std::vector<std::pair<float, float>> points_;
};
}