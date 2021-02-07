#include "thh-bgfx-debug/debug-cube.hpp"

namespace dbg
{

static constexpr int CubeVerticesCount = 8;
static constexpr int CubeIndicesCount = 24;

DebugVertex DebugCubes::CubeVertices[CubeVerticesCount] = {
  {{-0.5f, 0.5f, 0.5f}, 0xffffffff},   {{0.5f, 0.5f, 0.5f}, 0xffffffff},
  {{-0.5f, -0.5f, 0.5f}, 0xffffffff},  {{0.5f, -0.5f, 0.5f}, 0xffffffff},
  {{-0.5f, 0.5f, -0.5f}, 0xffffffff},  {{0.5f, 0.5f, -0.5f}, 0xffffffff},
  {{-0.5f, -0.5f, -0.5f}, 0xffffffff}, {{0.5f, -0.5f, -0.5f}, 0xffffffff}
};

uint16_t DebugCubes::CubeIndices[CubeIndicesCount] = {
  0, 1, 2, 3, 4, 5, 6, 7,
  0, 2, 1, 3, 4, 6, 5, 7,
  0, 4, 1, 5, 2, 6, 3, 7
};

void DebugCubes::init()
{
}

DebugCubes::DebugCubes(
  const bgfx::ViewId view, const bgfx::ProgramHandle program_handle)
  : view_(view), program_handle_(program_handle)
{
  cube_vbh_ = bgfx::createVertexBuffer(
    bgfx::makeRef(CubeVertices, sizeof(CubeVertices)), DebugVertex::Layout);
  cube_ibh_ = bgfx::createIndexBuffer(
    bgfx::makeRef(CubeIndices, sizeof(CubeIndices)));
}

DebugCubes::~DebugCubes()
{
  bgfx::destroy(cube_vbh_);
  bgfx::destroy(cube_ibh_);
}

void DebugCubes::reserveCubes(const size_t count)
{
  instances_.reserve(count);
}

void DebugCubes::submit()
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
    for (const auto& cube_instance : instances_) {
      auto* inst_transform = (float*)data;
      std::copy(
        as::mat_const_data(cube_instance.transform_),
        as::mat_const_data(cube_instance.transform_) + 16, inst_transform);

      auto* color = (float*)&data[64];
      color[0] = cube_instance.color_[0];
      color[1] = cube_instance.color_[1];
      color[2] = cube_instance.color_[2];
      color[3] = cube_instance.color_[3];

      data += instance_stride;
    }

    bgfx::setVertexBuffer(view_, cube_vbh_);
    bgfx::setIndexBuffer(cube_ibh_);

    bgfx::setInstanceDataBuffer(&idb);

    bgfx::setState(BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINES);
    bgfx::submit(view_, program_handle_);
  }
}

} // namespace dbg
