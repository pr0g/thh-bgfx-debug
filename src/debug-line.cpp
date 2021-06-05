#include "thh-bgfx-debug/debug-line.hpp"

#include <cstring>

namespace dbg
{

void DebugLines::setRenderContext(
  const bgfx::ViewId view, const bgfx::ProgramHandle program_handle)
{
  view_ = view;
  program_handle_ = program_handle;
}

void DebugLines::addLine(
  const as::vec3& begin, const as::vec3& end, const uint32_t col)
{
  lines_.emplace_back(begin, end, col);
}

void DebugLines::submit()
{
  const auto requested_vertex_count = lines_.size() * 2;
  if (requested_vertex_count == 0) {
    return;
  }

  const auto available_vertex_count = bgfx::getAvailTransientVertexBuffer(
    requested_vertex_count, DebugVertex::Layout);
  if (available_vertex_count != requested_vertex_count) {
    return;
  }

  bgfx::TransientVertexBuffer line_tvb;
  bgfx::allocTransientVertexBuffer(
    &line_tvb, requested_vertex_count, DebugVertex::Layout);

  std::memcpy(
    line_tvb.data, lines_.data(),
    DebugVertex::Layout.getStride() * requested_vertex_count);

  float transform[16];
  as::mat_to_arr(transform_, transform);
  bgfx::setTransform(transform);

  bgfx::setState(
    BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA
    | BGFX_STATE_BLEND_ALPHA);

  bgfx::setVertexBuffer(0, &line_tvb, 0, requested_vertex_count);
  bgfx::submit(view_, program_handle_);

  lines_.clear();
}

} // namespace dbg
