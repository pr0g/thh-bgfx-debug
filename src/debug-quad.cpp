#include "thh-bgfx-debug/debug-quad.hpp"

namespace dbg
{

const DebugVertex DebugQuads::QuadVertices[] = {
  {as::vec3{0.0f, 0.0f, 0.0f}, 0xffffffff},
  {as::vec3{1.0f, 0.0f, 0.0}, 0xffffffff},
  {as::vec3{1.0f, 1.0f, 0.0f}, 0xffffffff},
  {as::vec3{0.0f, 1.0f, 0.0f}, 0xffffffff}};

const uint16_t DebugQuads::QuadIndices[] = {0, 1, 2, 0, 2, 3};

DebugQuads::DebugQuads()
{
  quad_vbh_ = bgfx::createVertexBuffer(
    bgfx::makeRef(QuadVertices, sizeof(QuadVertices)), DebugVertex::Layout);
  quad_ibh_ =
    bgfx::createIndexBuffer(bgfx::makeRef(QuadIndices, sizeof(QuadIndices)));
}

DebugQuads::~DebugQuads()
{
  bgfx::destroy(quad_vbh_);
  bgfx::destroy(quad_ibh_);
}

void DebugQuads::setRenderContext(
  const bgfx::ViewId view, const bgfx::ProgramHandle program_handle)
{
  view_ = view;
  program_handle_ = program_handle;
}

void DebugQuads::reserveQuads(const size_t count)
{
  instances_.reserve(count);
}

void DebugQuads::submit()
{
  // 80 bytes stride = 64 bytes for mat4 + 16 bytes for RGBA color.
  const uint16_t instance_stride = 80;

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

      auto* color = (float*)&data[64];
      color[0] = quad_instance.color_[0];
      color[1] = quad_instance.color_[1];
      color[2] = quad_instance.color_[2];
      color[3] = quad_instance.color_[3];

      data += instance_stride;
    }

    bgfx::setVertexBuffer(view_, quad_vbh_);
    bgfx::setIndexBuffer(quad_ibh_);

    bgfx::setInstanceDataBuffer(&idb);

    bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA);
    bgfx::submit(view_, program_handle_);
  }

  instances_.clear();
}

} // namespace dbg
