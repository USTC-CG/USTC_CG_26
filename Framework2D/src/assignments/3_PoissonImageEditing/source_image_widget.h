#pragma once

#include "common/image_widget.h"
#include "shapes/rect.h"

namespace USTC_CG
{
class SourceImageWidget : public ImageWidget
{
   public:
    // HW3_TODO(optional): Add more region shapes like polygon and freehand.
    enum RegionType
    {
        kDefault = 0,
        kRect = 1
    };

    explicit SourceImageWidget(
        const std::string& label,
        const std::string& filename);
    virtual ~SourceImageWidget() noexcept = default;

    void draw() override;

    // Region selecting interaction
    void enable_selecting(bool flag);
    void select_region();
    // Get the selected region in the source image, this would be a binary mask.
    // The **size** of the mask should be the same as the source image.
    // The **value** of the mask should be 0 or 255: 0 for the background and
    // 255 for the selected region.
    std::shared_ptr<Image> get_region_mask();
    // Get the source image data
    std::shared_ptr<Image> get_data();
    // Get the position to locate the region in the target image.
    // We return the start point of the selected region as default.
    ImVec2 get_position() const;

   private:
    // Event handlers for mouse interactions.
    void mouse_click_event();
    void mouse_move_event();
    void mouse_release_event();

    // Calculates mouse's relative position in the canvas.
    ImVec2 mouse_pos_in_canvas() const;

    // Fill the selected region by the picking the pixels in the selected shape
    void update_selected_region();

    RegionType region_type_ = kRect;
    // The shape we draw in the source image to select the region.
    // By default, we use a rectangle to select the region.
    // HW3_TODO(optional): You can add more shapes for region selection.
    std::unique_ptr<Rect> selected_shape_;
    // The selected region in the source image, this would be a binary mask.
    // The **size** of the mask should be the same as the source image.
    // The **value** of the mask should be 0 or 255: 0 for the background and
    // 255 for the selected region.
    std::shared_ptr<Image> selected_region_mask_;

    ImVec2 start_, end_;
    bool flag_enable_selecting_region_ = false;
    bool draw_status_ = false;
};

}  // namespace USTC_CG