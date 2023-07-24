#pragma once

#include "as/as-vec.hpp"
#include "bgfx/bgfx.h"

namespace dbg
{

struct DebugUvVertex
{
  DebugUvVertex() = default;
  DebugUvVertex(const as::vec3f& position, const as::vec2f& uv)
    : position_(position), uv_(uv)
  {
  }

  static void init();

  as::vec3f position_;
  as::vec2f uv_;

  static inline bgfx::VertexLayout Layout;
};

} // namespace dbg
