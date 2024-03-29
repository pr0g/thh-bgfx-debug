#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex.hpp"

#include <array>
#include <vector>

namespace dbg
{

struct Triangle
{
  std::array<as::vec3f, 3> vertices_;
};

struct DebugTriangle
{
  DebugTriangle(
    const as::vec3f& v1, const as::vec3f& v2, const as::vec3f& v3,
    const uint32_t color)
    : vertices_(std::array{
      DebugVertex{v1, color}, DebugVertex{v2, color}, DebugVertex{v3, color}})
  {
  }

  std::array<DebugVertex, 3> vertices_;
};

class DebugTriangles
{
  as::mat4f transform_ = as::mat4f::identity();
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;
  std::vector<DebugTriangle> triangles_;
  uint64_t state_;

public:
  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void setTransform(const as::mat4f& transform) { transform_ = transform; }
  void addTriangle(const Triangle& triangle, uint32_t color);
  void addTriangle(
    const as::vec3f& v1, const as::vec3f& v2, const as::vec3f& v3, uint32_t color);
  void setState(uint64_t state);
  void submitAndClear();
  void submit();
  void clear();
};

} // namespace dbg
