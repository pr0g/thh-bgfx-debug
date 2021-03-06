#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex.hpp"

#include <vector>

namespace dbg
{

class DebugCircles
{
  static DebugVertex CircleVertices[];
  static uint16_t CircleIndices[];

  bgfx::VertexBufferHandle circle_vbh_;
  bgfx::IndexBufferHandle circle_ibh_;
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;

  struct CircleInstance
  {
    CircleInstance() = default;
    CircleInstance(const as::mat4& transform, const as::vec4& color)
      : transform_(transform), color_(color)
    {
    }

    as::mat4 transform_;
    as::vec4 color_;
  };

  std::vector<CircleInstance> instances_;

public:
  static void init();

  DebugCircles();
  ~DebugCircles();

  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void reserveCircles(size_t count);
  void addCircle(const as::mat4& transform, const as::vec4& color);
  void submit();
};

inline void DebugCircles::addCircle(
  const as::mat4& transform, const as::vec4& color)
{
  instances_.emplace_back(transform, color);
}

} // namespace dbg
