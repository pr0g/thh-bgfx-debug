#pragma once

#include "as/as-vec.hpp"
#include "bgfx/bgfx.h"

namespace dbg
{

struct DebugVertex
{
  DebugVertex() = default;
  DebugVertex(const as::vec3& position, const uint32_t color)
    : position_(position), color_(color)
  {
  }

  static void init();

  as::vec3 position_;
  uint32_t color_;

  static inline bgfx::VertexLayout Layout;
};

} // namespace dbg
