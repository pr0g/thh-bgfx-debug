#pragma once

#include "bgfx/bgfx.h"

namespace dbg
{

struct EmbeddedShaderArgs;
extern const EmbeddedShaderArgs SimpleEmbeddedShaderArgs;
extern const EmbeddedShaderArgs InstanceEmbeddedShaderArgs;

class EmbeddedShaderProgram
{
  bgfx::ProgramHandle program_handle_;

public:
  EmbeddedShaderProgram() = default;

  void init(const EmbeddedShaderArgs& embedded_shader_args);
  void deinit();

  [[nodiscard]] bgfx::ProgramHandle handle() const { return program_handle_; };
};

} // namespace dbg
