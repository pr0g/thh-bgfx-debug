#pragma once

#include <cstdint>

namespace dbg
{

struct Rgba
{
  Rgba(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
    : r(r), g(g), b(b), a(a)
  {
  }

  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

struct NormalizedRgba
{
  NormalizedRgba(const float r, const float g, const float b, const float a)
    : r(r), g(g), b(b), a(a)
  {
  }
  NormalizedRgba(const float rgba) : r(rgba), g(rgba), b(rgba), a(rgba) {}
  NormalizedRgba(const float rgb, const float a) : r(rgb), g(rgb), b(rgb), a(a)
  {
  }

  float r;
  float g;
  float b;
  float a;
};

inline uint32_t rgbaFromAbgr(const uint32_t abgr)
{
  return ((abgr & 0xff000000) >> 24) | ((abgr & 0xff0000) >> 8)
       | ((abgr & 0xff00) << 8) | ((abgr & 0xff) << 24);
}

inline uint32_t abgrFromRgba(const uint32_t rgba)
{
  return rgbaFromAbgr(rgba);
}

inline uint32_t encodeColorAbgr(
  const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
  return (a << 24) | (b << 16) | (g << 8) | r;
}

inline uint32_t encodeColorAbgr(
  const float r, const float g, const float b, const float a)
{
  return (uint8_t(a * 255.0f) << 24) | (uint8_t(b * 255.0f) << 16)
       | (uint8_t(g * 255.0f) << 8) | uint8_t(r * 255.0f);
}

inline uint32_t encodeColorAbgr(const NormalizedRgba& colorRgba)
{
  return encodeColorAbgr(colorRgba.r, colorRgba.g, colorRgba.b, colorRgba.a);
}

inline Rgba decodeColorAbgr(const uint32_t abgr)
{
  return {
    (uint8_t)(abgr & 0xff), (uint8_t)((abgr >> 8) & 0xff),
    (uint8_t)((abgr >> 16) & 0xff), (uint8_t)((abgr >> 24) & 0xff)};
}

inline NormalizedRgba decodeColorAbgrNormalized(const uint32_t abgr)
{
  const auto color = decodeColorAbgr(abgr);
  return {
    (float)color.r / 255.0f, (float)color.g / 255.0f, (float)color.b / 255.0f,
    (float)color.a / 255.0f};
}

} // namespace dbg
