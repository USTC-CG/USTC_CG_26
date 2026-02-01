#pragma once

#include <memory>

#include "common/image_widget.h"
#include "common/window.h"

namespace USTC_CG
{
class Demo : public Window
{
   public:
    explicit Demo(const std::string& window_name);
    ~Demo();
    void draw();

    void draw_toolbar();
    void draw_image();
    void draw_open_image_file_dialog();

   private:
    std::shared_ptr<ImageWidget> p_image_ = nullptr;

    bool flag_show_main_view_ = true;
    bool flag_open_file_dialog_ = false;
};
}  // namespace USTC_CG