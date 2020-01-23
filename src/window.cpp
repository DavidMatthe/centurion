#include "window.h"
#include <stdexcept>
#include <type_traits>
#include <SDL_image.h>
#include "window_listener.h"
#include "bool_converter.h"

namespace centurion {

static_assert(std::is_final_v<Window>);

static_assert(std::is_nothrow_move_assignable_v<Window>);
static_assert(std::is_nothrow_move_constructible_v<Window>);

static_assert(!std::is_copy_assignable_v<Window>);
static_assert(!std::is_copy_constructible_v<Window>);

static_assert(std::is_convertible_v<Window, SDL_Window*>);
static_assert(std::is_default_constructible_v<Window>);

Window::Window(const std::string& title, int width, int height) {
  if ((width < 1) || (height < 1)) {
    throw std::invalid_argument("Invalid width or height!");
  }

  const auto pos = SDL_WINDOWPOS_CENTERED;
  window = SDL_CreateWindow(title.c_str(), pos, pos, width, height,
                            SDL_WINDOW_HIDDEN);

  SDL_Surface* icon = IMG_Load("centurion_icon.png");
  if (icon) {
    set_icon(icon);
    SDL_FreeSurface(icon);
  }
}

Window::Window(int width, int height) : Window("Centurion window", width, height) {}

Window::Window(const std::string& title) : Window(title, 800, 600) {}

Window::Window() : Window(800, 600) {}

Window::Window(Window&& other) noexcept
    : window{other.window},
      windowListeners{std::move(other.windowListeners)} {
  other.window = nullptr;
}

Window::~Window() {
  if (window) {
    SDL_DestroyWindow(window);
  }
}

Window& Window::operator=(Window&& other) noexcept {
  window = other.window;
  windowListeners = std::move(other.windowListeners);

  other.window = nullptr;

  return *this;
}

std::unique_ptr<Window> Window::unique(const std::string& title, int width, int height) {
  return std::make_unique<Window>(title, width, height);
}

std::unique_ptr<Window> Window::unique(int width, int height) {
  return std::make_unique<Window>(width, height);
}

std::unique_ptr<Window> Window::unique(const std::string& title) {
  return std::make_unique<Window>(title);
}

std::unique_ptr<Window> Window::unique() {
  return std::make_unique<Window>();
}

std::shared_ptr<Window> Window::shared(const std::string& title, int width, int height) {
  return std::make_shared<Window>(title, width, height);
}

std::shared_ptr<Window> Window::shared(int width, int height) {
  return std::make_shared<Window>(width, height);
}

std::shared_ptr<Window> Window::shared(const std::string& title) {
  return std::make_shared<Window>(title);
}

std::shared_ptr<Window> Window::shared() {
  return std::make_shared<Window>();
}

void Window::notify_window_listeners() noexcept {
  const auto& self = *this;
  for (auto* listener : windowListeners) {
    if (listener) {
      listener->window_updated(self);
    }
  }
}

void Window::show() noexcept {
  SDL_ShowWindow(window);
  notify_window_listeners();
}

void Window::hide() noexcept {
  SDL_HideWindow(window);
  notify_window_listeners();
}

void Window::center() noexcept {
  set_position(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
  notify_window_listeners();
}

void Window::raise() noexcept {
  SDL_RaiseWindow(window);
  notify_window_listeners();
}

void Window::add_window_listener(IWindowListener* listener) noexcept {
  if (listener) {
    windowListeners.push_back(listener);
  }
}

void Window::set_fullscreen(bool fullscreen) noexcept {
  const auto flags = (fullscreen) ? (SDL_GetWindowFlags(window) | SDL_WINDOW_FULLSCREEN)
                                  : (SDL_GetWindowFlags(window) & ~SDL_WINDOW_FULLSCREEN);
  SDL_SetWindowFullscreen(window, flags);

  if (!fullscreen) {
    set_gamma(1);
  }

  notify_window_listeners();
}

void Window::set_decorated(bool decorated) noexcept {
  SDL_SetWindowBordered(window, BoolConverter::convert(decorated));
  notify_window_listeners();
}

void Window::set_resizable(bool isResizable) noexcept {
  SDL_SetWindowResizable(window, BoolConverter::convert(isResizable));
  notify_window_listeners();
}

void Window::set_width(int width) {
  if (width < 1) {
    throw std::invalid_argument("Invalid width!");
  } else {
    SDL_SetWindowSize(window, width, get_height());
    notify_window_listeners();
  }
}

void Window::set_height(int height) {
  if (height < 1) {
    throw std::invalid_argument("Invalid height!");
  } else {
    SDL_SetWindowSize(window, get_width(), height);
    notify_window_listeners();
  }
}

void Window::set_icon(gsl::not_null<SDL_Surface*> icon) noexcept {
  SDL_SetWindowIcon(window, icon);
  notify_window_listeners();
}

void Window::set_title(const std::string& title) noexcept {
  SDL_SetWindowTitle(window, title.c_str());
  notify_window_listeners();
}

void Window::set_gamma(float gamma) noexcept {
  if (is_fullscreen()) {
    SDL_SetWindowBrightness(window, gamma);
    notify_window_listeners();
  }
}

void Window::set_opacity(float opacity) noexcept {
  SDL_SetWindowOpacity(window, opacity);
  notify_window_listeners();
}

void Window::set_min_size(int width, int height) noexcept {
  SDL_SetWindowMinimumSize(window, width, height);
  notify_window_listeners();
}

void Window::set_max_size(int width, int height) noexcept {
  SDL_SetWindowMaximumSize(window, width, height);
  notify_window_listeners();
}

void Window::set_position(int x, int y) noexcept {
  SDL_SetWindowPosition(window, x, y);
  notify_window_listeners();
}

void Window::set_grab_mouse(bool grabMouse) noexcept {
  SDL_SetWindowGrab(window, BoolConverter::convert(grabMouse));
  notify_window_listeners();
}

void Window::set_brightness(float brightness) noexcept {
  if (brightness < 0) {
    brightness = 0;
  } else if (brightness > 1) {
    brightness = 1;
  }
  SDL_SetWindowBrightness(window, brightness);
  notify_window_listeners();
}

bool Window::is_decorated() const noexcept {
  int left = 0;
  int right = 0;
  int top = 0;
  int bottom = 0;
  SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right);
  return left || right || top || bottom;
}

bool Window::is_grabbing_mouse() const noexcept {
  return SDL_GetWindowGrab(window);
}

bool Window::is_resizable() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE;
}

bool Window::is_fullscreen() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
}

bool Window::is_visible() const noexcept {
  return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
}

float Window::get_opacity() const noexcept {
  float opacity = 1;
  SDL_GetWindowOpacity(window, &opacity);
  return opacity;
}

float Window::get_brightness() const noexcept {
  return SDL_GetWindowBrightness(window);
}

int Window::get_id() const noexcept {
  return SDL_GetWindowID(window);
}

int Window::get_x() const noexcept {
  int x = 0;
  SDL_GetWindowPosition(window, &x, nullptr);
  return x;
}

int Window::get_y() const noexcept {
  int y = 0;
  SDL_GetWindowPosition(window, nullptr, &y);
  return y;
}

std::pair<int, int> Window::get_position() const noexcept {
  int x = 0;
  int y = 0;
  SDL_GetWindowPosition(window, &x, &y);
  return {x, y};
}

std::pair<int, int> Window::get_min_size() const noexcept {
  int w = 0;
  int h = 0;
  SDL_GetWindowMinimumSize(window, &w, &h);
  return {w, h};
}

std::pair<int, int> Window::get_max_size() const noexcept {
  int w = 0;
  int h = 0;
  SDL_GetWindowMaximumSize(window, &w, &h);
  return {w, h};
}

int Window::get_width() const noexcept {
  int width = 0;
  SDL_GetWindowSize(window, &width, nullptr);

  return width;
}

int Window::get_height() const noexcept {
  int height = 0;
  SDL_GetWindowSize(window, nullptr, &height);

  return height;
}

uint32_t Window::get_pixel_format() const noexcept {
  return SDL_GetWindowPixelFormat(window);
}

std::string Window::get_title() const noexcept {
  return SDL_GetWindowTitle(window);
}

Window::operator SDL_Window*() const noexcept {
  return window;
}

}