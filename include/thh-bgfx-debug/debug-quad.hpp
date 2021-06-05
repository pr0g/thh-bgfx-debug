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
    QuadInstance(const as::mat4& transform, const as::vec4& color)
      : transform_(transform), color_(color)
    {
    }

    as::mat4 transform_;
    as::vec4 color_;
  };

  std::vector<QuadInstance> instances_;

public:
  DebugQuads();
  ~DebugQuads();

  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void reserveQuads(size_t count);
  void addQuad(const as::mat4& transform, const as::vec4& color);
  void submit();
};

inline void DebugQuads::addQuad(
  const as::mat4& transform, const as::vec4& color)
{
  instances_.emplace_back(transform, color);
}

} // namespace dbg
