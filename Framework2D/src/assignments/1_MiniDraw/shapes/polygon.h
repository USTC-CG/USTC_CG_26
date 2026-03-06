#pragma once

#include "shape.h"

#include <vector>

namespace USTC_CG
{
class Polygon : public Shape
{
   public:
    Polygon() = default;

    // Constructor to initialize a Polygon with start and end coordinates
    Polygon(
        float start_point_x,
        float start_point_y,
        float end_point_x,
        float end_point_y)
        : start_point_x_(start_point_x),
          start_point_y_(start_point_y),
          end_point_x_(end_point_x),
          end_point_y_(end_point_y)
    {
    }

    virtual ~Polygon() = default;

    // Overrides draw function to implement Polygon-specific drawing logic
    void draw(const Config& config) const override;

    // Overrides Shape's update function to adjust the end point during
    // interaction
    void update(float x, float y) override;

    // we already have start and end points, so this can be used to implement right click to connect the last point to the first point,
    // need to implement override add_control_point function to add more control points for polygon, just draw line between the nearby control points 
    void add_control_point(float x, float y) override;

    // complete the polygon
    void set_done();

   private:
    float start_point_x_, start_point_y_, end_point_x_, end_point_y_;
    std::vector<std::pair<float, float>> control_points_;  // control points for polygon vertices
};
}  // namespace USTC_CG
