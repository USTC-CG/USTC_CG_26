#include "freehand.h"

#include <imgui.h>

#include <cmath>

namespace USTC_CG
{
// Draw the ellipse using ImGui
// void AddEllipse(const ImVec2& center, const ImVec2& radius, ImU32 col, float rot, int num_segments, float thickness);
void Freehand::draw(const Config& config) const
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    std::vector<ImVec2> screen_points;
    screen_points.reserve(points_.size());
    for (const auto& p : points_)
    {
        screen_points.push_back(
            ImVec2(p.first + config.bias[0], p.second + config.bias[1]));
    }

    draw_list->AddPolyline(
        screen_points.data(),
        (int)screen_points.size(),
        IM_COL32(
            config.line_color[0],
            config.line_color[1],
            config.line_color[2],
            config.line_color[3]),
        0,
        config.line_thickness);
}

void Freehand::update(float x, float y)
{
    points_.push_back({ x, y });
}
}  // namespace USTC_CG
