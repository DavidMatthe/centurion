#include "music.hpp"

#include <algorithm>

#include "centurion_exception.hpp"
#include "error.hpp"

namespace centurion {

music::music(czstring file)
{
  m_music = Mix_LoadMUS(file);
  if (!m_music) {
    throw detail::mix_error("Failed to create Music instance!");
  }
}

music::music(music&& other) noexcept
{
  move(std::move(other));
}

music::~music() noexcept
{
  destroy();
}

auto music::operator=(music&& other) noexcept -> music&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

void music::destroy() noexcept
{
  if (m_music) {
    Mix_FreeMusic(m_music);
  }
}

void music::move(music&& other) noexcept
{
  destroy();
  m_music = other.m_music;
  other.m_music = nullptr;
}

auto music::unique(czstring file) -> std::unique_ptr<music>
{
  return std::make_unique<music>(file);
}

auto music::shared(czstring file) -> std::shared_ptr<music>
{
  return std::make_shared<music>(file);
}

void music::play(int nLoops) noexcept
{
  if (nLoops < -1) {
    nLoops = -1;
  }
  Mix_PlayMusic(m_music, nLoops);
}

void music::resume() noexcept
{
  Mix_ResumeMusic();
}

void music::pause() noexcept
{
  Mix_PauseMusic();
}

void music::halt() noexcept
{
  Mix_HaltMusic();
}

void music::fade_in(milliseconds<int> ms, int nLoops) noexcept
{
  if (ms.count() < 0) {
    ms = milliseconds<int>{0};
  }

  if (nLoops < -1) {
    nLoops = -1;
  }

  Mix_FadeInMusic(m_music, nLoops, ms.count());
}

void music::fade_out(milliseconds<int> ms) noexcept
{
  if (is_fading()) {
    return;
  }
  if (ms.count() < 0) {
    ms = milliseconds<int>{0};
  }
  Mix_FadeOutMusic(ms.count());
}

void music::set_volume(int volume) noexcept
{
  Mix_VolumeMusic(std::clamp(volume, 0, MIX_MAX_VOLUME));
}

auto music::is_playing() noexcept -> bool
{
  return Mix_PlayingMusic();
}

auto music::is_paused() noexcept -> bool
{
  return Mix_PausedMusic();
}

auto music::is_fading() noexcept -> bool
{
  const auto status = get_fade_status();
  return status == fade_status::in || status == fade_status::out;
}

auto music::volume() noexcept -> int
{
  return Mix_VolumeMusic(-1);
}

auto music::get_fade_status() noexcept -> fade_status
{
  return static_cast<fade_status>(Mix_FadingMusic());
}

auto music::type() const noexcept -> music_type
{
  return static_cast<music_type>(Mix_GetMusicType(m_music));
}

auto music::to_string() const -> std::string
{
  return "[Music@" + detail::address_of(this) + "]";
}

}  // namespace centurion
