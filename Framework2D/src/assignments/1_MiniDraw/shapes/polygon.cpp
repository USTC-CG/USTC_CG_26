#include "polygon.h"

#include <imgui.h>

namespace USTC_CG
{
// Draw the polygon using ImGui
void Polygon::draw(const Config& config) const
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // If control_points_ is empty, we don't have anything to draw yet
    if (control_points_.empty()) {
        return;
    }

    // draw loop for every pair verticies the polygon
    auto itr = control_points_.begin();
    auto itr_next = std::next(itr);

    // draw existing points in control_points_
    while (itr_next != control_points_.end()) {
        draw_list->AddLine(
            ImVec2(
                config.bias[0] + (*itr).first, config.bias[1] + (*itr).second),
            ImVec2(config.bias[0] + (*itr_next).first, config.bias[1] + (*itr_next).second),
            IM_COL32(
                config.line_color[0],
                config.line_color[1],
                config.line_color[2],
                config.line_color[3]),
            config.line_thickness);
        
        itr = std::next(itr);
        itr_next = std::next(itr_next);
    }

    // draw the line between the last point of control_points_ and end_points
    draw_list->AddLine(
        ImVec2(
            config.bias[0] + (*itr).first, config.bias[1] + (*itr).second),
        ImVec2(config.bias[0] + end_point_x_, config.bias[1] + end_point_y_),
        IM_COL32(
            config.line_color[0],
            config.line_color[1],
            config.line_color[2],
            config.line_color[3]),
        config.line_thickness);
}

void Polygon::set_done()
{
    end_point_x_ = start_point_x_;
    end_point_y_ = start_point_y_;
}

void Polygon::update(float x, float y)
{
    end_point_x_ = x;
    end_point_y_ = y;
}

void Polygon::add_control_point(float x, float y)
{
    control_points_.emplace_back(std::pair<float, float>(x, y));
}

}  // namespace USTC_CG