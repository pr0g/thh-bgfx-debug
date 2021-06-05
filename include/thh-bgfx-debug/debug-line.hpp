#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex.hpp"

#include <vector>

namespace dbg
{

struct DebugLine
{
  DebugLine(const as::vec3& begin, const as::vec3& end, const uint32_t col)
    : begin_(begin, col), end_(end, col)
  {
  }

  DebugVertex begin_;
  DebugVertex end_;
};

class DebugLines
{
  as::mat4 transform_ = as::mat4::identity();
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;
  std::vector<DebugLine> lines_;

public:
  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void setTransform(const as::mat4& transform) { transform_ = transform; }
  void addLine(const as::vec3& begin, const as::vec3& end, uint32_t col);
  void submit();
};

} // namespace dbg
