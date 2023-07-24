#include "thh-bgfx-debug/debug-sphere.hpp"

namespace dbg
{

DebugSpheres::DebugSpheres(DebugCircles& debug_circles)
  : debug_circles_(debug_circles)
{
}

void DebugSpheres::addSphere(const as::mat4f& transform, const uint32_t color)
{
  constexpr size_t Loops = 8;
  const float vertical_angle_inc_rad = as::radians(180.0f / float(Loops));
  const float starting_vertical_angle_rad = as::radians(90.0f);

  float current_vertical_angle_rad =
    starting_vertical_angle_rad + vertical_angle_inc_rad;
  for (size_t loop = 0; loop < Loops - 1; ++loop) {
    const float vertical_position = std::sin(current_vertical_angle_rad);
    const float horizontal_scale = std::cos(current_vertical_angle_rad);

    const auto translation = as::mat4_from_mat3_vec3(
      as::mat3_rotation_x(as::radians(90.0f)),
      as::vec3f::axis_y(vertical_position));
    const auto scale = as::mat4_from_mat3(as::mat3_scale(horizontal_scale));

    debug_circles_.addWireCircle(
      as::mat_mul(as::mat_mul(scale, translation), transform), color);

    current_vertical_angle_rad += vertical_angle_inc_rad;
  }
}

} // namespace dbg
