#include "ellipse.h"

#include <imgui.h>

#include <cmath>

namespace USTC_CG
{
// Draw the ellipse using ImGui
// void AddEllipse(const ImVec2& center, const ImVec2& radius, ImU32 col, float rot, int num_segments, float thickness);
void Ellipse::draw(const Config& config) const
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->AddEllipse(
        ImVec2(
            (2.0f * config.bias[0] + start_point_x_ + end_point_x_) / 2.0f,
            (2.0f * config.bias[1] + start_point_y_ + end_point_y_) / 2.0f),
        ImVec2(
            fabs(end_point_x_ - start_point_x_) / 2.0f,
            fabs(end_point_y_ - start_point_y_) / 2.0f),
        IM_COL32(
            config.line_color[0],
            config.line_color[1],
            config.line_color[2],
            config.line_color[3]),
        0.f,  // no rotation
        0,    // auto-tessellated
        config.line_thickness);
}

void Ellipse::update(float x, float y)
{
    end_point_x_ = x;
    end_point_y_ = y;
}
}  // namespace USTC_CG
