#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex-uv.hpp"

#include <vector>

namespace dbg
{

struct DebugUvQuadDynamic
{
  DebugUvQuadDynamic(const as::vec3& min, const as::vec3& max)
    : bl_(as::vec3(min.x, min.y, min.z), as::vec2f{0.0f, 1.0f}),
      br_(as::vec3(max.x, min.y, max.z), as::vec2f{1.0f, 1.0f}),
      tr_(as::vec3(max.x, max.y, max.z), as::vec2f{1.0f, 0.0f}),
      tl_(as::vec3(min.x, max.y, min.z), as::vec2f{0.0f, 0.0f})
  {
  }

  DebugUvQuadDynamic(
    const as::vec3& min, const as::vec3& max, const float l, const float r,
    const float t, const float b)
    : bl_(as::vec3(min.x, min.y, min.z), as::vec2f{l, t}),
      br_(as::vec3(max.x, min.y, max.z), as::vec2f{r, t}),
      tr_(as::vec3(max.x, max.y, max.z), as::vec2f{r, b}),
      tl_(as::vec3(min.x, max.y, min.z), as::vec2f{l, b})
  {
  }

  DebugUvVertex bl_;
  DebugUvVertex br_;
  DebugUvVertex tr_;
  DebugUvVertex tl_;
};

class DebugUvQuadsDynamic
{
  as::mat4f transform_ = as::mat4f::identity();
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;
  std::vector<uint16_t> indices_;
  std::vector<DebugUvQuadDynamic> quads_;
  std::vector<bgfx::TextureHandle> textures_;
  bgfx::UniformHandle sampler_;
  uint64_t state_;

public:
  DebugUvQuadsDynamic();
  ~DebugUvQuadsDynamic();

  void setSampler(bgfx::UniformHandle sampler);
  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void setTransform(const as::mat4f& transform) { transform_ = transform; }
  void addQuad(
    const as::vec3& min, const as::vec3& max,
    bgfx::TextureHandle texture_handle);
  void addQuad(
    const as::vec3& min, const as::vec3& max, float l, float r, float t,
    float b, bgfx::TextureHandle texture_handle);
  void setState(uint64_t state);
  void submitAndClear();
  void submit();
  void clear();
};

} // namespace dbg
