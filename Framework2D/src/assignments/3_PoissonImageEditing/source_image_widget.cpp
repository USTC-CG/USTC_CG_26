#include "source_image_widget.h"

#include <algorithm>
#include <cmath>

namespace USTC_CG
{
using uchar = unsigned char;

SourceImageWidget::SourceImageWidget(
    const std::string& label,
    const std::string& filename)
    : ImageWidget(label, filename)
{
    if (data_)
        selected_region_mask_ =
            std::make_shared<Image>(data_->width(), data_->height(), 1);
}

void SourceImageWidget::draw()
{
    // Draw the image
    ImageWidget::draw();
    // Draw selected region
    if (flag_enable_selecting_region_)
        select_region();
}

void SourceImageWidget::enable_selecting(bool flag)
{
    flag_enable_selecting_region_ = flag;
}

void SourceImageWidget::select_region()
{
    /// Invisible button over the canvas to capture mouse interactions.
    ImGui::SetCursorScreenPos(position_);
    ImGui::InvisibleButton(
        label_.c_str(),
        ImVec2(
            static_cast<float>(image_width_),
            static_cast<float>(image_height_)),
        ImGuiButtonFlags_MouseButtonLeft);
    // Record the current status of the invisible button
    bool is_hovered_ = ImGui::IsItemHovered();
    ImGuiIO& io = ImGui::GetIO();
    // Mouse events
    if (is_hovered_ && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        mouse_click_event();
    }
    mouse_move_event();
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
        mouse_release_event();

    // Region Shape Visualization
    if (selected_shape_)
    {
        Shape::Config s = { .bias = { position_.x, position_.y },
                            .line_color = { 255, 0, 0, 255 },
                            .line_thickness = 2.0f };
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        selected_shape_->draw(s);
    }  
}

std::shared_ptr<Image> SourceImageWidget::get_region_mask()
{
    return selected_region_mask_;
}

std::shared_ptr<Image> SourceImageWidget::get_data()
{
    return data_;
}

ImVec2 SourceImageWidget::get_position() const
{
    return start_;
}

void SourceImageWidget::mouse_click_event()
{
    // Start drawing the region 
    if (!draw_status_)
    {
        draw_status_ = true;
        start_ = end_ = mouse_pos_in_canvas();
        // HW3_TODO(optional): You can add more shapes for region selection. You
        // can also consider using the implementation in HW1. (We use rectangle
        // for example)
        switch (region_type_)
        {
            case USTC_CG::SourceImageWidget::kDefault: break;
            case USTC_CG::SourceImageWidget::kRect:
            {
                selected_shape_ =
                    std::make_unique<Rect>(start_.x, start_.y, end_.x, end_.y);
                break;
            }
            default: break;
        }
    }
}

void SourceImageWidget::mouse_move_event()
{
    // Keep updating the region
    if (draw_status_)
    {
        end_ = mouse_pos_in_canvas();
        if (selected_shape_)
            selected_shape_->update(end_.x, end_.y);
    }
}

void SourceImageWidget::mouse_release_event()
{
    // Finish drawing the region
    if (draw_status_ && selected_shape_)
    {
        draw_status_ = false;
        // Update the selected region.
        update_selected_region();
    }
}

ImVec2 SourceImageWidget::mouse_pos_in_canvas() const
{
    ImGuiIO& io = ImGui::GetIO();
    // The position should not be out of the canvas
    const ImVec2 mouse_pos_in_canvas(
        std::clamp<float>(io.MousePos.x - position_.x, 0, (float)image_width_),
        std::clamp<float>(
            io.MousePos.y - position_.y, 0, (float)image_height_));
    return mouse_pos_in_canvas;
}

void SourceImageWidget::update_selected_region()
{
    if (selected_shape_ == nullptr)
        return;
    // HW3_TODO(Optional): The selected_shape_ call its get_interior_pixels()
    // function to get the interior pixels. For other shapes, you can implement
    // their own get_interior_pixels()
    std::vector<std::pair<int, int>> interior_pixels =
        selected_shape_->get_interior_pixels();
    // Clear the selected region mask
    for (int i = 0; i < selected_region_mask_->width(); ++i)
        for (int j = 0; j < selected_region_mask_->height(); ++j)
            selected_region_mask_->set_pixel(i, j, { 0 });
    // Set the selected pixels with 255
    for (const auto& pixel : interior_pixels)
    {
        int x = pixel.first;
        int y = pixel.second;
        if (x < 0 || x >= selected_region_mask_->width() || 
            y < 0 || y >= selected_region_mask_->height())
            continue;
        selected_region_mask_->set_pixel(x, y, { 255 });
    }
}
}  // namespace USTC_CG