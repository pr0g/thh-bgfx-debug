#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex.hpp"

#include <vector>

namespace dbg
{

struct CircleInstance
{
  CircleInstance() = default;
  CircleInstance(const as::mat4& transform, const uint32_t color)
    : transform_(transform), color_(color)
  {
  }

  as::mat4 transform_;
  uint32_t color_;
};

class DebugCircles
{
  bgfx::VertexBufferHandle solid_circle_vbh_;
  bgfx::IndexBufferHandle solid_circle_ibh_;
  bgfx::VertexBufferHandle wire_circle_vbh_;
  bgfx::IndexBufferHandle wire_circle_ibh_;
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;

  std::vector<CircleInstance> wire_instances_;
  std::vector<CircleInstance> solid_instances_;

public:
  static void init();

  DebugCircles();
  ~DebugCircles();

  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void reserveSolidCircles(size_t count);
  void reserveWireCircles(size_t count);
  void addSolidCircle(const as::mat4& transform, uint32_t color);
  void addWireCircle(const as::mat4& transform, uint32_t color);
  void submitAndClear();
  void submit();
  void clear();
};

inline void DebugCircles::addSolidCircle(
  const as::mat4& transform, const uint32_t color)
{
  solid_instances_.emplace_back(transform, color);
}

inline void DebugCircles::addWireCircle(
  const as::mat4& transform, const uint32_t color)
{
  wire_instances_.emplace_back(transform, color);
}

} // namespace dbg
