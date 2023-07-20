#include "thh-bgfx-debug/debug-quad-uv-dynamic.hpp"

#include <cstring>

namespace dbg
{

DebugUvQuadsDynamic::DebugUvQuadsDynamic()
{
  state_ = BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA;
}

DebugUvQuadsDynamic::~DebugUvQuadsDynamic()
{
}

void DebugUvQuadsDynamic::setSampler(const bgfx::UniformHandle sampler)
{
  sampler_ = sampler;
}

void DebugUvQuadsDynamic::setRenderContext(
  const bgfx::ViewId view, const bgfx::ProgramHandle program_handle)
{
  view_ = view;
  program_handle_ = program_handle;
}

static void appendIndices(std::vector<uint16_t>& indices)
{
  const auto index_count = static_cast<uint16_t>((indices.size() / 6) * 4);
  indices.insert(
    indices.end(), {static_cast<uint16_t>(0 + index_count),
                    static_cast<uint16_t>(1 + index_count),
                    static_cast<uint16_t>(2 + index_count),
                    static_cast<uint16_t>(0 + index_count),
                    static_cast<uint16_t>(2 + index_count),
                    static_cast<uint16_t>(3 + index_count)});
}

void DebugUvQuadsDynamic::addQuad(
  const as::vec3& min, const as::vec3& max,
  const bgfx::TextureHandle texture_handle)
{
  quads_.emplace_back(min, max);
  appendIndices(indices_);
  textures_.push_back(texture_handle);
}

void DebugUvQuadsDynamic::addQuad(
  const as::vec3& min, const as::vec3& max, const float l, const float r,
  const float t, const float b, const bgfx::TextureHandle texture_handle)
{
  quads_.emplace_back(min, max, l, r, t, b);
  appendIndices(indices_);
  textures_.push_back(texture_handle);
}

void DebugUvQuadsDynamic::submit()
{
  const auto requested_vertex_count = quads_.size() * 4;
  if (requested_vertex_count == 0) {
    return;
  }

  const auto available_vertex_count = bgfx::getAvailTransientVertexBuffer(
    requested_vertex_count, DebugUvVertex::Layout);
  if (available_vertex_count != requested_vertex_count) {
    return;
  }

  bgfx::TransientVertexBuffer quad_tvb;
  bgfx::TransientIndexBuffer quad_tib;

  const auto requested_index_count = quads_.size() * 6;
  bgfx::allocTransientBuffers(
    &quad_tvb, DebugUvVertex::Layout, requested_vertex_count, &quad_tib,
    requested_index_count);

  std::memcpy(
    quad_tvb.data, quads_.data(),
    DebugUvVertex::Layout.getStride() * requested_vertex_count);
  std::memcpy(
    quad_tib.data, indices_.data(), sizeof(uint16_t) * requested_index_count);

  float transform[16];
  as::mat_to_arr(transform_, transform);
  bgfx::setTransform(transform);

  for (size_t quad_index = 0; quad_index < quads_.size(); ++quad_index) {
    bgfx::setVertexBuffer(0, &quad_tvb, quad_index * 4, (quad_index + 1UL) * 4);
    bgfx::setIndexBuffer(&quad_tib, quad_index * 6, (quad_index + 1UL) * 6);
    bgfx::setState(state_);
    bgfx::setTexture(0, sampler_, textures_[quad_index]);
    bgfx::submit(view_, program_handle_);
  }
}

void DebugUvQuadsDynamic::setState(const uint64_t state)
{
  state_ = state;
}

void DebugUvQuadsDynamic::clear()
{
  quads_.clear();
  indices_.clear();
  textures_.clear();
}

void DebugUvQuadsDynamic::submitAndClear()
{
  submit();
  clear();
}

} // namespace dbg
