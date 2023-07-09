#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex-uv.hpp"

#include <vector>

namespace dbg
{

class DebugUvQuads
{
  static const DebugUvVertex QuadVertices[];
  static const uint16_t QuadIndices[];

  bgfx::VertexBufferHandle quad_vbh_;
  bgfx::IndexBufferHandle quad_ibh_;
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;
  uint64_t state_;

  struct QuadInstance
  {
    QuadInstance() = default;
    QuadInstance(const as::mat4& transform) : transform_(transform) {}
    as::mat4 transform_;
  };

  std::vector<QuadInstance> instances_;

public:
  DebugUvQuads();
  ~DebugUvQuads();

  bgfx::UniformHandle sampler_;
  bgfx::TextureHandle texture_;

  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void reserveQuads(size_t count);
  void addQuad(const as::mat4& transform);
  void setState(uint64_t state);
  void submitAndClear();
  void submit();
  void clear();
};

inline void DebugUvQuads::addQuad(const as::mat4& transform)
{
  instances_.emplace_back(transform);
}

inline void DebugUvQuads::setState(const uint64_t state)
{
  state_ = state;
}

} // namespace dbg
