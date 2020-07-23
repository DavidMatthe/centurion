#include "surface.hpp"

#include <SDL_image.h>

#include "error.hpp"

namespace centurion {

surface::surface(nn_czstring file) : m_surface{IMG_Load(file)}
{
  if (!m_surface) {
    throw detail::img_error("Failed to create surface!");
  }
}

surface::surface(nn_owner<SDL_Surface*> surface) : m_surface{surface}
{}

surface::surface(const surface& other)
{
  copy(other);
}

auto surface::operator=(const surface& other) -> surface&
{
  if (this != &other) {
    copy(other);
  }
  return *this;
}

auto surface::unique(nn_czstring file) -> surface::uptr
{
  return std::make_unique<surface>(file);
}

auto surface::unique(nn_owner<SDL_Surface*> sdlSurface) -> surface::uptr
{
  return std::make_unique<surface>(sdlSurface);
}

auto surface::shared(nn_czstring file) -> surface::sptr
{
  return std::make_shared<surface>(file);
}

auto surface::shared(nn_owner<SDL_Surface*> sdlSurface) -> surface::sptr
{
  return std::make_shared<surface>(sdlSurface);
}

void surface::copy(const surface& other)
{
  m_surface.reset(other.copy_surface());
}

auto surface::in_bounds(const point_i& point) const noexcept -> bool
{
  return !(point.x() < 0 || point.y() < 0 || point.x() >= width() ||
           point.y() >= height());
}

auto surface::must_lock() const noexcept -> bool
{
  return SDL_MUSTLOCK(m_surface);
}

auto surface::lock() noexcept -> bool
{
  if (must_lock()) {
    const auto result = SDL_LockSurface(m_surface.get());
    return result == 0;
  } else {
    return true;
  }
}

void surface::unlock() noexcept
{
  if (must_lock()) {
    SDL_UnlockSurface(m_surface.get());
  }
}

auto surface::copy_surface() const -> owner<SDL_Surface*>
{
  auto* copy = SDL_DuplicateSurface(m_surface.get());
  if (!copy) {
    throw detail::core_error("Failed to duplicate Surface!");
  } else {
    return copy;
  }
}

void surface::set_pixel(const point_i& pixel, const color& color) noexcept
{
  if (!in_bounds(pixel)) {
    return;
  }

  const auto success = lock();
  if (!success) {
    return;
  }

  const int nPixels = (m_surface->pitch / 4) * height();
  const int index = (pixel.y() * width()) + pixel.x();

  if ((index >= 0) && (index < nPixels)) {
    const auto value = SDL_MapRGBA(m_surface->format,
                                   color.red(),
                                   color.green(),
                                   color.blue(),
                                   color.alpha());
    auto* pixels = reinterpret_cast<u32*>(m_surface->pixels);
    pixels[index] = value;
  }

  unlock();
}

void surface::set_alpha(u8 alpha) noexcept
{
  SDL_SetSurfaceAlphaMod(m_surface.get(), alpha);
}

void surface::set_color_mod(const color& color) noexcept
{
  SDL_SetSurfaceColorMod(
      m_surface.get(), color.red(), color.green(), color.blue());
}

void surface::set_blend_mode(enum blend_mode mode) noexcept
{
  SDL_SetSurfaceBlendMode(m_surface.get(), static_cast<SDL_BlendMode>(mode));
}

auto surface::alpha() const noexcept -> u8
{
  u8 alpha{0xFF};
  SDL_GetSurfaceAlphaMod(m_surface.get(), &alpha);
  return alpha;
}

auto surface::color_mod() const noexcept -> color
{
  u8 red{};
  u8 green{};
  u8 blue{};
  SDL_GetSurfaceColorMod(m_surface.get(), &red, &green, &blue);
  return color{red, green, blue};
}

auto surface::get_blend_mode() const noexcept -> blend_mode
{
  SDL_BlendMode mode{};
  SDL_GetSurfaceBlendMode(m_surface.get(), &mode);
  return static_cast<blend_mode>(mode);
}

auto surface::convert(pixel_format format) const -> surface
{
  const auto pixelFormat = static_cast<u32>(format);
  auto* converted = SDL_ConvertSurfaceFormat(m_surface.get(), pixelFormat, 0);
  SDL_SetSurfaceBlendMode(converted,
                          static_cast<SDL_BlendMode>(get_blend_mode()));
  return surface{converted};
}

}  // namespace centurion
