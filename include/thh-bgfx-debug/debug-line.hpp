#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex.hpp"

#include <vector>

namespace dbg
{

struct DebugLine
{
  DebugLine(const as::vec3f& begin, const as::vec3f& end, const uint32_t color)
    : begin_(begin, color), end_(end, color)
  {
  }

  DebugVertex begin_;
  DebugVertex end_;
};

class DebugLines
{
  as::mat4f transform_ = as::mat4f::identity();
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;
  std::vector<DebugLine> lines_;
  uint64_t state_;

public:
  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void setTransform(const as::mat4f& transform) { transform_ = transform; }
  void addLine(const as::vec3f& begin, const as::vec3f& end, uint32_t color);
  void setState(uint64_t state);
  void submitAndClear();
  void submit();
  void clear();
};

} // namespace dbg
