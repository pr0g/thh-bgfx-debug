#pragma once

#include "bgfx/bgfx.h"

namespace dbg
{

struct EmbeddedShaderArgs;
extern const EmbeddedShaderArgs g_simple_embedded_shader_args;
extern const EmbeddedShaderArgs g_instance_embedded_shader_args;

class EmbeddedShaderProgram
{
  bgfx::ProgramHandle program_handle_;

public:
  EmbeddedShaderProgram() = default;

  void init(const EmbeddedShaderArgs& embedded_shader_args);
  void deinit();

  bgfx::ProgramHandle handle() const { return program_handle_; };
};

} // namespace dbg
