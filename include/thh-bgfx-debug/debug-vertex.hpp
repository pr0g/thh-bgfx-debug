#pragma once

#include "as/as-vec.hpp"
#include "bgfx/bgfx.h"

namespace dbg
{

struct Rgba
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

inline uint32_t encodeColor(
  const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
  return (r << 24) | (g << 16) | (b << 8) | a;
}

inline uint32_t encodeColor(
  const float r, const float g, const float b, const float a)
{
  return (uint8_t(r * 255.0f) << 24) | (uint8_t(g * 255.0f) << 16)
       | (uint8_t(b * 255.0f) << 8) | uint8_t(a * 255.0f);
}

inline uint32_t encodeColor(const as::vec4& color)
{
  return (uint8_t(color.x * 255.0f) << 24) | (uint8_t(color.y * 255.0f) << 16)
       | (uint8_t(color.z * 255.0f) << 8) | uint8_t(color.w * 255.0f);
}

inline Rgba decodeColor(const uint32_t rgba)
{
  return {
    (uint8_t)((rgba >> 24) & 0xff), (uint8_t)((rgba >> 16) & 0xff),
    (uint8_t)((rgba >> 8) & 0xff), (uint8_t)((rgba)&0xff)};
}

inline as::vec4 decodeColorNormalized(const uint32_t rgba)
{
  const auto color = decodeColor(rgba);
  return {
    (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f,
    (float)color.a / 255.0f};
}

struct DebugVertex
{
  DebugVertex() = default;
  DebugVertex(const as::vec3& position, const uint32_t color)
    : position_(position), color_(color)
  {
  }

  static void init();

  as::vec3 position_;
  uint32_t color_;

  static inline bgfx::VertexLayout Layout;
};

} // namespace dbg
