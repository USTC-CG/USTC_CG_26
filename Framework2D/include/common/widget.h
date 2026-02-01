#pragma once

#include <string>

namespace USTC_CG
{

class Widget
{
   public:
    explicit Widget(const std::string& label) : label_(label)
    {
    }
    virtual ~Widget() = default;

    virtual void draw() = 0;

   protected:
    std::string label_;
};

}  // namespace USTC_CG
