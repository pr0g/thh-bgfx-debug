#include "thh-bgfx-debug/debug-shader.hpp"

#include "bgfx/embedded_shader.h"
#include "shader/instance/fs_instance.bin.h"
#include "shader/instance/vs_instance.bin.h"
#include "shader/simple/fs_simple.bin.h"
#include "shader/simple/vs_simple.bin.h"

namespace dbg
{

static const bgfx::EmbeddedShader SimpleEmbeddedShaders[] = {
  BGFX_EMBEDDED_SHADER(vs_simple), BGFX_EMBEDDED_SHADER(fs_simple),

  BGFX_EMBEDDED_SHADER_END()};

static const bgfx::EmbeddedShader InstanceEmbeddedShaders[] = {
  BGFX_EMBEDDED_SHADER(vs_instance), BGFX_EMBEDDED_SHADER(fs_instance),

  BGFX_EMBEDDED_SHADER_END()};

struct EmbeddedShaderArgs
{
  const char* vert_shader_name_;
  const char* frag_shader_name_;
  const bgfx::EmbeddedShader* embedded_shaders_;
};

const EmbeddedShaderArgs SimpleEmbeddedShaderArgs = {
  "vs_simple", "fs_simple", SimpleEmbeddedShaders};

const EmbeddedShaderArgs InstanceEmbeddedShaderArgs = {
  "vs_instance", "fs_instance", InstanceEmbeddedShaders};

void EmbeddedShaderProgram::init(const EmbeddedShaderArgs& embedded_shader_args)
{
  const bgfx::RendererType::Enum type = bgfx::getRendererType();

  const bgfx::ShaderHandle vsh = bgfx::createEmbeddedShader(
    embedded_shader_args.embedded_shaders_, type,
    embedded_shader_args.vert_shader_name_);
  const bgfx::ShaderHandle fsh = bgfx::createEmbeddedShader(
    embedded_shader_args.embedded_shaders_, type,
    embedded_shader_args.frag_shader_name_);

  program_handle_ = bgfx::createProgram(vsh, fsh, true);
}

void EmbeddedShaderProgram::deinit()
{
  bgfx::destroy(program_handle_);
}

} // namespace dbg
