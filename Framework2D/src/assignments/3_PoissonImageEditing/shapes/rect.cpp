#include "rect.h"

#include <imgui.h>

namespace USTC_CG
{
// Draw the rectangle using ImGui
void Rect::draw(const Config& config) const
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->AddRect(
        ImVec2(
            config.bias[0] + start_point_x_, config.bias[1] + start_point_y_),
        ImVec2(config.bias[0] + end_point_x_, config.bias[1] + end_point_y_),
        IM_COL32(
            config.line_color[0],
            config.line_color[1],
            config.line_color[2],
            config.line_color[3]),
        0.f,  // No rounding of corners
        ImDrawFlags_None,
        config.line_thickness);
}

void Rect::update(float x, float y)
{
    end_point_x_ = x;
    end_point_y_ = y;
}

std::vector<std::pair<int, int>> Rect::get_interior_pixels() const
{
    int start_pixel_x = static_cast<int>(start_point_x_);
    int start_pixel_y = static_cast<int>(start_point_y_);
    int end_pixel_x = static_cast<int>(end_point_x_);
    int end_pixel_y = static_cast<int>(end_point_y_);
    // Sort the start and end points
    if (start_pixel_x > end_pixel_x)
    {
        std::swap(start_pixel_x, end_pixel_x);
    }
    if (start_pixel_y > end_pixel_y)
    {
        std::swap(start_pixel_y, end_pixel_y);
    }
    // Then the width and height are positive
    int width = end_pixel_x - start_pixel_x + 1;
    int height = end_pixel_y - start_pixel_y + 1;
    // Pick the pixels in the rectangle (including the boundary)
    std::vector<std::pair<int, int>> int_pixels;
    int_pixels.reserve(width * height);
    for (int i = start_pixel_x; i <= end_pixel_x; ++i)
    {
        for (int j = start_pixel_y; j <= end_pixel_y; ++j)
        {
            int_pixels.push_back(std::make_pair(i, j));
        }
    }
    return int_pixels;
}

}  // namespace USTC_CG
