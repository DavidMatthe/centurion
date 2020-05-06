#ifndef CENTURION_IMAGE_SOURCE
#define CENTURION_IMAGE_SOURCE

#include "texture.h"

#include <SDL_image.h>

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"
#include "renderer.h"
#include "surface.h"

namespace centurion {
namespace video {

CENTURION_DEF
Texture::Texture(gsl::owner<SDL_Texture*> texture)
{
  if (!texture) {
    throw CenturionException{"Texture can't be created from null SDL texture!"};
  }
  this->texture = texture;
}

CENTURION_DEF
Texture::Texture(const Renderer& renderer, const char* path)
{
  if (!path) {
    throw CenturionException{"Can't load texture from null path!"};
  }

  texture = IMG_LoadTexture(renderer.get_internal(), path);

  if (!texture) {
    const auto strPath = std::string{path};
    throw CenturionException{"Failed to load texture from " + strPath};
  }
}

CENTURION_DEF
Texture::Texture(const Renderer& renderer, const Surface& surface)
{
  this->texture = SDL_CreateTextureFromSurface(renderer.get_internal(),
                                               surface.get_internal());
  if (!texture) {
    throw CenturionException{"Failed to create texture from surface! " +
                             Error::msg()};
  }
}

CENTURION_DEF
Texture::Texture(const Renderer& renderer,
                 PixelFormat format,
                 TextureAccess access,
                 int width,
                 int height)
{
  texture = SDL_CreateTexture(renderer,
                              static_cast<Uint32>(format),
                              static_cast<int>(access),
                              width,
                              height);
  if (!texture) {
    throw CenturionException{"Failed to create texture! " + Error::msg()};
  }
}

CENTURION_DEF
Texture::Texture(Texture&& other) noexcept
{
  if (this != &other) {
    destroy();
    texture = other.texture;
    other.texture = nullptr;
  }
}

CENTURION_DEF
Texture::~Texture() noexcept
{
  destroy();
}

CENTURION_DEF
Texture& Texture::operator=(Texture&& other) noexcept
{
  if (this != &other) {
    destroy();
    texture = other.texture;
    other.texture = nullptr;
  }
  return *this;
}

CENTURION_DEF
std::unique_ptr<Texture> Texture::unique(gsl::owner<SDL_Texture*> texture)
{
  return centurion::make_unique<Texture>(texture);
}

CENTURION_DEF
std::unique_ptr<Texture> Texture::unique(const Renderer& renderer,
                                         const char* path)
{
  return centurion::make_unique<Texture>(renderer, path);
}

CENTURION_DEF
std::unique_ptr<Texture> Texture::unique(const Renderer& renderer,
                                         const Surface& surface)
{
  return centurion::make_unique<Texture>(renderer, surface);
}

CENTURION_DEF
std::unique_ptr<Texture> Texture::unique(const Renderer& renderer,
                                         PixelFormat format,
                                         TextureAccess access,
                                         int width,
                                         int height)
{
  return centurion::make_unique<Texture>(
      renderer, format, access, width, height);
}

CENTURION_DEF
std::shared_ptr<Texture> Texture::shared(gsl::owner<SDL_Texture*> texture)
{
  return std::make_shared<Texture>(texture);
}

CENTURION_DEF
std::shared_ptr<Texture> Texture::shared(const Renderer& renderer,
                                         const char* path)
{
  return std::make_shared<Texture>(renderer, path);
}

CENTURION_DEF
std::shared_ptr<Texture> Texture::shared(const Renderer& renderer,
                                         const Surface& surface)
{
  return std::make_shared<Texture>(renderer, surface);
}

CENTURION_DEF
std::shared_ptr<Texture> Texture::shared(const Renderer& renderer,
                                         PixelFormat format,
                                         TextureAccess access,
                                         int width,
                                         int height)
{
  return std::make_shared<Texture>(renderer, format, access, width, height);
}

CENTURION_DEF
void Texture::destroy() noexcept
{
  if (texture) {
    SDL_DestroyTexture(texture);
  }
}

CENTURION_DEF
void Texture::set_alpha(Uint8 alpha) noexcept
{
  SDL_SetTextureAlphaMod(texture, alpha);
}

CENTURION_DEF
void Texture::set_blend_mode(BlendMode mode) noexcept
{
  SDL_SetTextureBlendMode(texture, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF
void Texture::set_color_mod(Color color) noexcept
{
  SDL_SetTextureColorMod(texture, color.red(), color.green(), color.blue());
}

CENTURION_DEF
PixelFormat Texture::get_format() const noexcept
{
  Uint32 format = 0;
  SDL_QueryTexture(texture, &format, nullptr, nullptr, nullptr);
  return static_cast<PixelFormat>(format);
}

CENTURION_DEF
TextureAccess Texture::get_access() const noexcept
{
  int access = 0;
  SDL_QueryTexture(texture, nullptr, &access, nullptr, nullptr);
  return static_cast<TextureAccess>(access);
}

CENTURION_DEF
int Texture::get_width() const noexcept
{
  int width = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, nullptr);
  return width;
}

CENTURION_DEF
int Texture::get_height() const noexcept
{
  int height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &height);
  return height;
}

CENTURION_DEF
bool Texture::is_target() const noexcept
{
  return get_access() == TextureAccess::Target;
}

CENTURION_DEF
bool Texture::is_static() const noexcept
{
  return get_access() == TextureAccess::Static;
}

CENTURION_DEF
bool Texture::is_streaming() const noexcept
{
  return get_access() == TextureAccess::Streaming;
}

CENTURION_DEF
Uint8 Texture::get_alpha() const noexcept
{
  Uint8 alpha;
  SDL_GetTextureAlphaMod(texture, &alpha);
  return alpha;
}

CENTURION_DEF
BlendMode Texture::get_blend_mode() const noexcept
{
  SDL_BlendMode mode;
  SDL_GetTextureBlendMode(texture, &mode);
  return static_cast<BlendMode>(mode);
}

CENTURION_DEF
Color Texture::get_color_mod() const noexcept
{
  Uint8 r = 0, g = 0, b = 0;
  SDL_GetTextureColorMod(texture, &r, &g, &b);
  return {r, g, b, 0xFF};
}

CENTURION_DEF
SDL_Texture* Texture::get_internal() noexcept
{
  return texture;
}

CENTURION_DEF
std::string Texture::to_string() const
{
  const auto address = address_of(this);
  const auto width = std::to_string(get_width());
  const auto height = std::to_string(get_height());
  return "[Texture@" + address + " | Width: " + width + ", Height: " + height +
         "]";
}

CENTURION_DEF
Texture::operator SDL_Texture*() const noexcept
{
  return texture;
}

CENTURION_DEF
bool operator==(TextureAccess a, SDL_TextureAccess b) noexcept
{
  return static_cast<SDL_TextureAccess>(a) == b;
}

CENTURION_DEF
bool operator==(SDL_TextureAccess a, TextureAccess b) noexcept
{
  return a == static_cast<SDL_TextureAccess>(b);
}

CENTURION_DEF
bool operator!=(TextureAccess a, SDL_TextureAccess b) noexcept
{
  return static_cast<SDL_TextureAccess>(a) != b;
}

CENTURION_DEF
bool operator!=(SDL_TextureAccess a, TextureAccess b) noexcept
{
  return a != static_cast<SDL_TextureAccess>(b);
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_IMAGE_SOURCE