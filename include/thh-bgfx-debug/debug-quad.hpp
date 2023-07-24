#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex.hpp"

#include <vector>

namespace dbg
{

class DebugQuads
{
  static const DebugVertex QuadVertices[];
  static const uint16_t QuadIndices[];

  bgfx::VertexBufferHandle quad_vbh_;
  bgfx::IndexBufferHandle quad_ibh_;
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;

  struct QuadInstance
  {
    QuadInstance() = default;
    QuadInstance(const as::mat4f& transform, const uint32_t color)
      : transform_(transform), color_(color)
    {
    }

    as::mat4f transform_;
    uint32_t color_;
  };

  std::vector<QuadInstance> instances_;

public:
  DebugQuads();
  ~DebugQuads();

  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void reserveQuads(size_t count);
  void addQuad(const as::mat4f& transform, uint32_t color);
  void submitAndClear();
  void submit();
  void clear();
};

inline void DebugQuads::addQuad(const as::mat4f& transform, const uint32_t color)
{
  instances_.emplace_back(transform, color);
}

} // namespace dbg
