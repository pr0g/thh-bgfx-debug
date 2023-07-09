#pragma once

#include "as/as-vec.hpp"
#include "bgfx/bgfx.h"

namespace dbg
{

struct DebugUvVertex
{
  DebugUvVertex() = default;
  DebugUvVertex(const as::vec3& position, const as::vec<int16_t, 2>& uv)
    : position_(position), uv_(uv)
  {
  }

  static void init();

  as::vec3 position_;
  as::vec<int16_t, 2> uv_;

  static inline bgfx::VertexLayout Layout;
};

} // namespace dbg
