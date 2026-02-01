#pragma once

#include <memory>

#include "common/window.h"
#include "source_image_widget.h"
#include "target_image_widget.h"

namespace USTC_CG
{
class PoissonWindow : public Window
{
   public:
    explicit PoissonWindow(const std::string& window_name);
    ~PoissonWindow();

    void draw();

   private:
    void draw_toolbar();
    void draw_target();
    void draw_source();

    void draw_open_target_image_file_dialog();
    void draw_open_source_image_file_dialog();
    void draw_save_image_file_dialog();

    void add_tooltips(std::string desc);

    // Target Image Component
    std::shared_ptr<TargetImageWidget> p_target_ = nullptr;
    // Source Image Component
    std::shared_ptr<SourceImageWidget> p_source_ = nullptr;

    bool flag_show_target_view_ = true;
    bool flag_show_source_view_ = true;
    bool flag_open_target_file_dialog_ = false;
    bool flag_open_source_file_dialog_ = false;
    bool flag_save_file_dialog_ = false;
};
}  // namespace USTC_CG