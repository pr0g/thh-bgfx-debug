#include "thh-bgfx-debug/debug-triangle.hpp"

#include <cstring>

namespace dbg
{

void DebugTriangles::setRenderContext(
  const bgfx::ViewId view, const bgfx::ProgramHandle program_handle)
{
  view_ = view;
  program_handle_ = program_handle;
}

void DebugTriangles::addTriangle(const Triangle& triangle, const uint32_t color)
{
  addTriangle(
    triangle.vertices_[0], triangle.vertices_[1], triangle.vertices_[2], color);
}

void DebugTriangles::addTriangle(
  const as::vec3& v1, const as::vec3& v2, const as::vec3& v3,
  const uint32_t color)
{
  triangles_.emplace_back(v1, v2, v3, color);
}

void DebugTriangles::submit()
{
  const auto requested_vertex_count = triangles_.size() * 3;
  if (requested_vertex_count == 0) {
    return;
  }

  const auto available_vertex_count = bgfx::getAvailTransientVertexBuffer(
    requested_vertex_count, DebugVertex::Layout);
  if (available_vertex_count != requested_vertex_count) {
    return;
  }

  bgfx::TransientVertexBuffer triangle_tvb;
  bgfx::allocTransientVertexBuffer(
    &triangle_tvb, requested_vertex_count, DebugVertex::Layout);

  std::memcpy(
    triangle_tvb.data, triangles_.data(),
    DebugVertex::Layout.getStride() * requested_vertex_count);

  float transform[16];
  as::mat_to_arr(transform_, transform);
  bgfx::setTransform(transform);

  bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA);

  bgfx::setVertexBuffer(0, &triangle_tvb, 0, requested_vertex_count);
  bgfx::submit(view_, program_handle_);
}

void DebugTriangles::drop()
{
  triangles_.clear();
}

} // namespace dbg
