#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex.hpp"

#include <array>
#include <vector>

namespace dbg
{

struct Triangle
{
  std::array<as::vec3, 3> vertices_;
};

struct DebugTriangle
{
  DebugTriangle(
    const as::vec3& v1, const as::vec3& v2, const as::vec3& v3,
    const uint32_t color)
    : vertices_(std::array{
      DebugVertex{v1, color}, DebugVertex{v2, color}, DebugVertex{v3, color}})
  {
  }

  std::array<DebugVertex, 3> vertices_;
};

class DebugTriangles
{
  as::mat4 transform_ = as::mat4::identity();
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;
  std::vector<DebugTriangle> triangles_;

public:
  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void setTransform(const as::mat4& transform) { transform_ = transform; }
  void addTriangle(const Triangle& triangle, uint32_t color);
  void addTriangle(
    const as::vec3& v1, const as::vec3& v2, const as::vec3& v3, uint32_t color);
  void submit_and_clear();
  void submit();
  void clear();
};

} // namespace dbg
