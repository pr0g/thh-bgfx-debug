#include "thh-bgfx-debug/debug-circle.hpp"

#include "thh-bgfx-debug/debug-color.hpp"

namespace dbg
{

static constexpr int WireCircleVerticesCount = 20;
static constexpr int WireCircleIndicesCount = 21;
static constexpr int SolidCircleVerticesCount = 21;
static constexpr int SolidCircleIndicesCount = 60;

static DebugVertex WireCircleVertices[WireCircleVerticesCount];
static uint16_t WireCircleIndices[WireCircleIndicesCount];
static DebugVertex SolidCircleVertices[SolidCircleVerticesCount];
static uint16_t SolidCircleIndices[SolidCircleIndicesCount];

void DebugCircles::init()
{
  {
    SolidCircleVertices[0] = {as::vec3::zero(), 0xffffffff};

    float rot = 0.0f;
    const float increment =
      as::k_tau / static_cast<float>(SolidCircleVerticesCount - 1);
    for (size_t i = 1; i < SolidCircleVerticesCount; ++i) {
      SolidCircleVertices[i] = {
        as::vec3(std::cos(rot), std::sin(rot), 0.0f), 0xffffffff};
      rot += increment;
    }

    for (size_t i = 0, v = 1; i < SolidCircleIndicesCount - 3; i += 3, ++v) {
      SolidCircleIndices[i] = 0;
      SolidCircleIndices[i + 1] = v;
      SolidCircleIndices[i + 2] = v + 1;
    }

    SolidCircleIndices[SolidCircleIndicesCount - 3] = 0;
    SolidCircleIndices[SolidCircleIndicesCount - 2] =
      SolidCircleVerticesCount - 1;
    SolidCircleIndices[SolidCircleIndicesCount - 1] = 1;
  }

  {
    float rot = 0.0f;
    const float increment =
      as::k_tau / static_cast<float>(WireCircleVerticesCount);
    for (size_t i = 0; i < WireCircleVerticesCount; ++i) {
      WireCircleVertices[i] = {
        as::vec3(std::cos(rot), std::sin(rot), 0.0f), 0xffffffff};
      WireCircleIndices[i] = i;
      rot += increment;
    }
    WireCircleIndices[WireCircleIndicesCount - 1] = 0;
  }
}

DebugCircles::DebugCircles()
{
  solid_circle_vbh_ = bgfx::createVertexBuffer(
    bgfx::makeRef(SolidCircleVertices, sizeof(SolidCircleVertices)),
    DebugVertex::Layout);
  solid_circle_ibh_ = bgfx::createIndexBuffer(
    bgfx::makeRef(SolidCircleIndices, sizeof(SolidCircleIndices)));

  wire_circle_vbh_ = bgfx::createVertexBuffer(
    bgfx::makeRef(WireCircleVertices, sizeof(WireCircleVertices)),
    DebugVertex::Layout);
  wire_circle_ibh_ = bgfx::createIndexBuffer(
    bgfx::makeRef(WireCircleIndices, sizeof(WireCircleIndices)));

  wire_state_ = BGFX_STATE_DEFAULT | BGFX_STATE_PT_LINESTRIP | BGFX_STATE_LINEAA
              | BGFX_STATE_BLEND_ALPHA;
  solid_state_ = BGFX_STATE_DEFAULT | BGFX_STATE_BLEND_ALPHA | BGFX_STATE_MSAA;
}

DebugCircles::~DebugCircles()
{
  bgfx::destroy(solid_circle_vbh_);
  bgfx::destroy(solid_circle_ibh_);
  bgfx::destroy(wire_circle_vbh_);
  bgfx::destroy(wire_circle_ibh_);
}

void DebugCircles::setRenderContext(
  const bgfx::ViewId view, const bgfx::ProgramHandle program_handle)
{
  view_ = view;
  program_handle_ = program_handle;
}

void DebugCircles::reserveSolidCircles(const size_t count)
{
  solid_instances_.reserve(count);
}

void DebugCircles::reserveWireCircles(const size_t count)
{
  wire_instances_.reserve(count);
}

static void submitCircles(
  const bgfx::VertexBufferHandle circle_vbh,
  const bgfx::IndexBufferHandle circle_ibh, const uint64_t state_flags,
  const bgfx::ViewId view, const bgfx::ProgramHandle program_handle,
  const std::vector<CircleInstance>& instances)
{
  // 80 bytes stride = 64 bytes for mat4 + 16 bytes for RGBA color.
  constexpr uint16_t instance_stride = 80;

  if (
    !instances.empty()
    && bgfx::getAvailInstanceDataBuffer(instances.size(), instance_stride)
         == instances.size()) {
    bgfx::InstanceDataBuffer idb;
    bgfx::allocInstanceDataBuffer(&idb, instances.size(), instance_stride);

    uint8_t* data = idb.data;
    for (const auto& circle_instance : instances) {
      auto* inst_transform = (float*)data;
      std::copy(
        as::mat_const_data(circle_instance.transform_),
        as::mat_const_data(circle_instance.transform_) + 16, inst_transform);

      const auto decoded_color =
        decodeColorAbgrNormalized(circle_instance.color_);
      auto* color = (float*)&data[64];
      color[0] = decoded_color.r;
      color[1] = decoded_color.g;
      color[2] = decoded_color.b;
      color[3] = decoded_color.a;

      data += instance_stride;
    }

    bgfx::setVertexBuffer(0, circle_vbh);
    bgfx::setIndexBuffer(circle_ibh);
    bgfx::setInstanceDataBuffer(&idb);
    bgfx::setState(state_flags);
    bgfx::submit(view, program_handle);
  }
}

void DebugCircles::submit()
{
  submitCircles(
    solid_circle_vbh_, solid_circle_ibh_, solid_state_, view_, program_handle_,
    solid_instances_);
  submitCircles(
    wire_circle_vbh_, wire_circle_ibh_, wire_state_, view_, program_handle_,
    wire_instances_);
}

void DebugCircles::setSolidState(const uint64_t state)
{
  solid_state_ = state;
}

void DebugCircles::setWireState(const uint64_t state)
{
  wire_state_ = state;
}

void DebugCircles::clear()
{
  wire_instances_.clear();
  solid_instances_.clear();
}

void DebugCircles::submitAndClear()
{
  submit();
  clear();
}

} // namespace dbg
