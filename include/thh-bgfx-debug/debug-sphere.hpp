#pragma once

#include "as/as-math-ops.hpp"
#include "debug-circle.hpp"

namespace dbg
{

class DebugSpheres
{
  DebugCircles& debug_circles_;

public:
  explicit DebugSpheres(DebugCircles& debug_circles);

  void addSphere(const as::mat4& transform, const as::vec4& color);
};

} // namespace dbg
