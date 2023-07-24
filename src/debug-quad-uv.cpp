#include "thh-bgfx-debug/debug-quad-uv.hpp"

namespace dbg
{

const DebugUvVertex DebugUvQuads::QuadVertices[] = {
  {as::vec3f{0.0f, 0.0f, 0.0f}, as::vec2f{0.0f, 1.0f}},
  {as::vec3f{1.0f, 0.0f, 0.0f}, as::vec2f{1.0f, 1.0f}},
  {as::vec3f{1.0f, 1.0f, 0.0f}, as::vec2f{1.0f, 0.0f}},
  {as::vec3f{0.0f, 1.0f, 0.0f}, as::vec2f{0.0f, 0.0f}}};

const uint16_t DebugUvQuads::QuadIndices[] = {0, 1, 2, 0, 2, 3};

DebugUvQuads::DebugUvQuads()
{
  quad_vbh_ = bgfx::createVertexBuffer(
    bgfx::makeRef(QuadVertices, sizeof(QuadVertices)), DebugUvVertex::Layout);
  quad_ibh_ =
    bgfx::createIndexBuffer(bgfx::makeRef(QuadIndices, sizeof(QuadIndices)));
  state_ = BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA;
}

DebugUvQuads::~DebugUvQuads()
{
  bgfx::destroy(quad_vbh_);
  bgfx::destroy(quad_ibh_);
}

void DebugUvQuads::setRenderContext(
  const bgfx::ViewId view, const bgfx::ProgramHandle program_handle)
{
  view_ = view;
  program_handle_ = program_handle;
}

void DebugUvQuads::reserveQuads(const size_t count)
{
  instances_.reserve(count);
}

void DebugUvQuads::submit()
{
  // 64 bytes stride = 64 bytes for mat4
  const uint16_t instance_stride = 64;

  if (
    !instances_.empty()
    && bgfx::getAvailInstanceDataBuffer(instances_.size(), instance_stride)
         == instances_.size()) {
    bgfx::InstanceDataBuffer idb;
    bgfx::allocInstanceDataBuffer(&idb, instances_.size(), instance_stride);

    uint8_t* data = idb.data;
    for (const auto& quad_instance : instances_) {
      auto* inst_transform = (float*)data;
      std::copy(
        as::mat_const_data(quad_instance.transform_),
        as::mat_const_data(quad_instance.transform_) + 16, inst_transform);
      data += instance_stride;
    }

    bgfx::setVertexBuffer(0, quad_vbh_);
    bgfx::setIndexBuffer(quad_ibh_);
    bgfx::setInstanceDataBuffer(&idb);
    bgfx::setTexture(0, sampler_, texture_);
    bgfx::setState(state_);
    bgfx::submit(view_, program_handle_);
  }
}

void DebugUvQuads::setTexture(const bgfx::TextureHandle texture)
{
  texture_ = texture;
}

void DebugUvQuads::setSampler(const bgfx::UniformHandle sampler)
{
  sampler_ = sampler;
}

void DebugUvQuads::clear()
{
  instances_.clear();
}

void DebugUvQuads::submitAndClear()
{
  submit();
  clear();
}

} // namespace dbg
