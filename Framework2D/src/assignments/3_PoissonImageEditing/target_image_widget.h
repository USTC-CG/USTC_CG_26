#pragma once

#include "source_image_widget.h"
#include "common/image_widget.h"

namespace USTC_CG
{
class TargetImageWidget : public ImageWidget
{
   public:
    // HW3_TODO: Add more types of cloning, we have implemented the "Paste"
    // type, you can implement seamless cloning, mix-gradient cloning, etc.
    enum CloneType
    {
        kDefault = 0,
        kPaste = 1,
        kSeamless = 2
    };

    explicit TargetImageWidget(
        const std::string& label,
        const std::string& filename);
    virtual ~TargetImageWidget() noexcept = default;

    void draw() override;
    // Bind the source image component
    void set_source(std::shared_ptr<SourceImageWidget> source);
    // Enable real-time updating
    void set_realtime(bool flag);
    // Restore the target image
    void restore();
    // HW3_TODO: Add more types of cloning, we have implemented the "Paste"
    // type, you can implement seamless cloning, mix-gradient cloning, etc.
    void set_paste();
    void set_seamless();

    // The clone function
    void clone();

   private:
    // Event handlers for mouse interactions.
    void mouse_click_event();
    void mouse_move_event();
    void mouse_release_event();

    // Calculates mouse's relative position in the canvas.
    ImVec2 mouse_pos_in_canvas() const;

    // Store the original image data
    std::shared_ptr<Image> back_up_;
    // Source image
    std::shared_ptr<SourceImageWidget> source_image_;
    CloneType clone_type_ = kDefault;

    ImVec2 mouse_position_;
    bool edit_status_ = false;
    bool flag_realtime_updating = false;
};
}  // namespace USTC_CG