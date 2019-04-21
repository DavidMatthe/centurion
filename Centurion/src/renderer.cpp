#include "renderer.h"
#include <stdexcept>
#include "null_checker.h"

using namespace centurion::geo;
using centurion::tools::NullChecker;

namespace centurion {
namespace visuals {

Renderer::Renderer(SDL_Renderer* renderer) {
  if (renderer == nullptr) {
    throw std::invalid_argument("Null renderer!");
  }
  this->sdlRenderer = renderer;
  SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer() { SDL_DestroyRenderer(sdlRenderer); }

void Renderer::CheckRenderDimensions(int width, int height) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid rendering dimensions!");
  }
}

void Renderer::UpdateColor() {
  SDL_SetRenderDrawColor(sdlRenderer, color.GetRed(), color.GetGreen(),
                         color.GetBlue(), color.GetAlpha());
}

void Renderer::Update() { SDL_RenderPresent(sdlRenderer); }

void Renderer::Clear() { SDL_RenderClear(sdlRenderer); }

void Renderer::Render(Texture& img, int x, int y, int w, int h) {
  CheckRenderDimensions(w, h);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderCopy(sdlRenderer, &img.GetSDLVersion(), NULL, &rect);
}

void Renderer::Render(Texture& img, const Rectangle& rect) { // FIXME no need for reference to the Rectangle
  CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
  SDL_RenderCopy(sdlRenderer, &img.GetSDLVersion(), NULL,
                 &rect.GetSDLVersion());
}

void Renderer::Render(Texture& img, int x, int y) {
  Render(img, x, y, img.GetWidth(), img.GetHeight());
}

void Renderer::RenderFilledRect(int x, int y, int w, int h) {
  CheckRenderDimensions(w, h);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderFillRect(sdlRenderer, &rect);
}

void Renderer::RenderFilledRect(Rectangle rect) {
  CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
  SDL_RenderFillRect(sdlRenderer, &rect.GetSDLVersion());
}

void Renderer::RenderOutlinedRect(int x, int y, int w, int h) {
  CheckRenderDimensions(w, h);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderDrawRect(sdlRenderer, &rect);
}

void Renderer::RenderOutlinedRect(Rectangle rect) {
  CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
  SDL_RenderDrawRect(sdlRenderer, &rect.GetSDLVersion());
}

void Renderer::RenderLine(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(sdlRenderer, x1, y1, x2, y2);
}

void Renderer::RenderLine(Point p1, Point p2) {
  SDL_RenderDrawLine(sdlRenderer, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
}

SDL_Texture* Renderer::CreateSDLTextureFromString(const std::string& str,
                                                  int* width, int* height) {
  if (font == nullptr || width == nullptr || height == nullptr) {
    throw std::invalid_argument("Failed to create texture from string!");
  } else {
    SDL_Surface* surface = TTF_RenderText_Solid(
        font->GetSDLVersion(), str.c_str(), color.GetSDLVersion());
    SDL_Texture* tmp = SDL_CreateTextureFromSurface(GetSDLVersion(), surface);
    *width = surface->w;
    *height = surface->h;
    SDL_FreeSurface(surface);
    return tmp;
  }
}

void Renderer::RenderString(const std::string& text, int x, int y) {
  if (font == nullptr) {
    throw std::invalid_argument("Failed to render text!");
  } else {
    int w, h;
    SDL_Texture* t = CreateSDLTextureFromString(text, &w, &h);
    Texture texture = Texture(t, w, h);
    Render(texture, x, y);
  }
}

void Renderer::SetFont(const std::shared_ptr<Font> font) { this->font = font; }

void Renderer::SetColor(Color color) {
  this->color = color;
  UpdateColor();
}

void Renderer::SetRenderTarget(Texture_sptr texture) {
  if (texture == nullptr) {
    SDL_SetRenderTarget(sdlRenderer, NULL);
  } else {
    SDL_SetRenderTarget(sdlRenderer, &texture->GetSDLVersion());
  }
}

std::shared_ptr<Texture> Renderer::CreateTextureFromString(
    const std::string& str) {
  if (font == nullptr) {
    throw std::invalid_argument("Failed to render text!");
  } else {
    int w, h;
    SDL_Texture* t = CreateSDLTextureFromString(str, &w, &h);
    return std::make_shared<Texture>(t, w, h);
  }
}

Texture_sptr Renderer::CreateSubtexture(Texture_sptr base, Rectangle src,
                                        Rectangle dst, Uint32 pixelFormat) {
  if (!SDL_RenderTargetSupported(sdlRenderer)) {
    throw std::exception("Subtextures are not available!");
  }
  Texture_sptr target = CreateRawTexture(dst.GetWidth(), dst.GetHeight(),
                                         pixelFormat, SDL_TEXTUREACCESS_TARGET);
  SetRenderTarget(target);
  SDL_RenderCopy(sdlRenderer, &base->GetSDLVersion(), &src.GetSDLVersion(),
                 &dst.GetSDLVersion());
  Update();
  SetRenderTarget(nullptr);
  return target;
}

Texture_sptr Renderer::CreateRawTexture(int width, int height,
                                        Uint32 pixelFormat,
                                        SDL_TextureAccess access) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid dimensions for raw texture!");
  } else {
    SDL_Texture* t =
        SDL_CreateTexture(sdlRenderer, pixelFormat, access, width, height);
    SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
    if (t == nullptr) {
      throw std::exception("Failed to create texture!");
    }
    return Texture::CreateShared(t, width, height);
  }
}

Renderer_sptr Renderer::CreateShared(SDL_Renderer* renderer) {
  return std::make_shared<Renderer>(renderer);
}

Renderer_uptr Renderer::CreateUnique(SDL_Renderer* renderer) {
  return std::make_unique<Renderer>(renderer);
}

Renderer_wptr Renderer::CreateWeak(SDL_Renderer* renderer) {
  return CreateShared(renderer);
}

}  // namespace visuals
}  // namespace centurion