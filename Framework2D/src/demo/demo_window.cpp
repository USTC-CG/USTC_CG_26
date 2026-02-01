#include "demo_window.h"

#include <ImGuiFileDialog.h>

namespace USTC_CG
{
Demo::Demo(const std::string& window_name) : Window(window_name)
{
}
Demo::~Demo()
{
}
void Demo::draw()
{
    draw_toolbar();
    if (flag_open_file_dialog_)
        draw_open_image_file_dialog();
    // Fill the whole window
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    if (ImGui::Begin(
            "Demo",
            &flag_show_main_view_,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground))
    {
        if (p_image_)
            draw_image();
        ImGui::End();
    }
}
void Demo::draw_toolbar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Image File.."))
            {
                flag_open_file_dialog_ = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
void Demo::draw_image()
{
    const auto& canvas_min = ImGui::GetCursorScreenPos();
    const auto& canvas_size = ImGui::GetContentRegionAvail();
    const auto& image_size = p_image_->get_image_size();
    // Center the image in the window
    ImVec2 pos = ImVec2(
        canvas_min.x + canvas_size.x / 2 - image_size.x / 2,
        canvas_min.y + canvas_size.y / 2 - image_size.y / 2);
    p_image_->set_position(pos);
    p_image_->draw();
}
void Demo::draw_open_image_file_dialog()
{
    IGFD::FileDialogConfig config; config.path = ".";
    ImGuiFileDialog::Instance()->OpenDialog(
        "ChooseImageOpenFileDlg", "Choose Image File", ".png,.jpg", config);
    if (ImGuiFileDialog::Instance()->Display("ChooseImageOpenFileDlg"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName =
                ImGuiFileDialog::Instance()->GetFilePathName();
            std::string label = filePathName;
            p_image_ = std::make_shared<ImageWidget>(label, filePathName);
        }
        ImGuiFileDialog::Instance()->Close();
        flag_open_file_dialog_ = false;
    }
}
}  // namespace USTC_CG