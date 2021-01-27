#include "thh-bgfx-debug/debug-vertex.hpp"

namespace dbg
{

void DebugVertex::init()
{
  Layout.begin()
    .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
    .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
    .end();
}

} // namespace dbg
