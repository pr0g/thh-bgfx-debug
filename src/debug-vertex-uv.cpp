#include "thh-bgfx-debug/debug-vertex-uv.hpp"

namespace dbg
{

void DebugUvVertex::init()
{
  Layout.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
    .end();
}

} // namespace dbg
