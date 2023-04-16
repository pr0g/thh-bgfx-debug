#pragma once

#include "as/as-math-ops.hpp"
#include "debug-vertex.hpp"

#include <vector>

namespace dbg
{

class DebugCubes
{
  static DebugVertex CubeVertices[];
  static uint16_t CubeIndices[];

  bgfx::VertexBufferHandle cube_vbh_;
  bgfx::IndexBufferHandle cube_ibh_;
  bgfx::ProgramHandle program_handle_;
  bgfx::ViewId view_;

  struct CubeInstance
  {
    CubeInstance() = default;
    CubeInstance(const as::mat4& transform, uint32_t color)
      : transform_(transform), color_(color)
    {
    }

    as::mat4 transform_;
    uint32_t color_;
  };

  std::vector<CubeInstance> instances_;

public:
  static void init();

  DebugCubes();
  ~DebugCubes();

  void setRenderContext(bgfx::ViewId view, bgfx::ProgramHandle program_handle);
  void reserveCubes(size_t count);
  void addCube(const as::mat4& transform, uint32_t color);
  void submitAndClear();
  void submit();
  void clear();
};

inline void DebugCubes::addCube(
  const as::mat4& transform, uint32_t color)
{
  instances_.emplace_back(transform, color);
}

} // namespace dbg
