#include <stdexcept>

#include "warping_window.h"

int main()
{
    // init and run the application
    try
    {
        USTC_CG::ImageWarping w("Image Warping");
        if (!w.init())
            return 1;

        w.run();
        return 0;
    }
    catch (const std::exception& e)
    {
        fprintf(stderr, "Error: %s\n", e.what());
        return 1;
    }
}