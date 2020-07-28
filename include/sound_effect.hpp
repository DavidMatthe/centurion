/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file sound_effect.hpp
 *
 * @brief Provides the `SoundEffect` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

/**
 * @defgroup audio Audio
 *
 * @brief Contains the audio API, for playing as sound effects and music.
 */

#ifndef CENTURION_SOUND_EFFECT_HEADER
#define CENTURION_SOUND_EFFECT_HEADER

#include <SDL_mixer.h>

#include <memory>
#include <ostream>
#include <string>
#include <type_traits>

#include "centurion_api.hpp"
#include "centurion_types.hpp"
#include "centurion_utils.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/// @cond FALSE

namespace detail {

class sound_effect_deleter final {
 public:
  void operator()(Mix_Chunk* chunk) noexcept { Mix_FreeChunk(chunk); }
};

}  // namespace detail

/// @endcond

/**
 * @class sound_effect
 *
 * @ingroup audio
 *
 * @brief Represents a sound effect.
 *
 * @details The supported file formats are the following:
 * <ul>
 *   <li>WAVE/RIFF (.wav)</li>
 *   <li>AIFF (.aiff)</li>
 *   <li>VOC (.voc)</li>
 *   <li>OGG (.ogg)</li>
 *   <li>VOC (.voc)</li>
 * </ul>
 *
 * @par Usage
 * Usage of this class is pretty straightforward and self-explanatory. The
 * fundamental methods are `play()` and `stop()`, with additional support for
 * effects such as fading and looping.
 * @code{.cpp}
 *   #include <centurion_as_ctn.hpp>
 *   #include <sound_effect.hpp>
 *
 *   void demo()
 *   {
 *     // supports .wav, .aiff, .voc, .ogg and .voc files
 *     ctn::sound_effect sfx{"foo.wav"};
 *
 *     // sets the volume (range: [0, sound_effect::max_volume()])
 *     sfx.set_volume(98);
 *
 *     // play sound effect once
 *     sfx.play();
 *
 *     // play sound effect twice
 *     sfx.play(2);
 *
 *     // loop sound effect forever
 *     sfx.play(ctn::sound_effect::loopForever);
 *
 *     // stops playing the sound effect
 *     sfx.stop();
 *
 *     // fades in the sound effect over 500 milliseconds
 *     sfx.fade_in(ctn::milliseconds<int>{500});
 *
 *     if (sfx.is_fading()) {
 *       // ...
 *     }
 *   }
 * @endcode
 *
 * @since 3.0.0
 *
 * @see `Mix_Chunk`
 * @see `music`
 *
 * @headerfile sound_effect.hpp
 */
class sound_effect final {
 public:
  /**
   * @typedef uptr
   *
   * @brief Simple alias for a unique pointer to a sound effect.
   *
   * @since 5.0.0
   */
  using uptr = std::unique_ptr<sound_effect>;

  /**
   * @typedef sptr
   *
   * @brief Simple alias for a shared pointer to a sound effect.
   *
   * @since 5.0.0
   */
  using sptr = std::shared_ptr<sound_effect>;

  /**
   * @typedef wptr
   *
   * @brief Simple alias for a weak pointer to a sound effect.
   *
   * @since 5.0.0
   */
  using wptr = std::weak_ptr<sound_effect>;

  /**
   * @brief Indicates that an audio snippet should be looped indefinitely.
   *
   * @since 4.0.0
   */
  inline static constexpr int loopForever = -1;

  /**
   * @brief Creates a sound effect based on the audio file at the specified
   * location.
   *
   * @param file the file path of the audio file, cannot be null.
   *
   * @throws centurion_exception if the audio file cannot be loaded.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit sound_effect(nn_czstring file);

  /**
   * @copydoc sound_effect(nn_czstring)
   */
  CENTURION_QUERY
  static auto unique(nn_czstring file) -> uptr;

  /**
   * @copydoc sound_effect(nn_czstring)
   */
  CENTURION_QUERY
  static auto shared(nn_czstring file) -> sptr;

  /**
   * @brief Plays the sound effect.
   *
   * @note A negative value indicates that the sound effect should be looped
   * forever.
   *
   * @param nLoops the amount of loops, can be negative.
   *
   * @see `sound_effect::loopForever`
   *
   * @since 3.0.0
   */
  CENTURION_API
  void play(int nLoops = 0) noexcept;

  /**
   * @brief Stops the sound effect from playing.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void stop() noexcept;

  /**
   * @brief Fades in the sound effect.
   *
   * @details This method has no effect if the supplied duration isn't greater
   * than zero or if the sound effect is currently playing.
   *
   * @param ms the duration to fade in, in milliseconds.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void fade_in(milliseconds<int> ms) noexcept;

  /**
   * @brief Fades out the sound effect.
   *
   * @details This method has no effect if the supplied duration isn't greater
   * than zero or if the sound effect isn't currently playing.
   *
   * @param ms the duration to fade in, in milliseconds.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void fade_out(milliseconds<int> ms) noexcept;

  /**
   * @brief Sets the volume of the sound effect.
   *
   * @details This method will adjust input values outside the legal range to
   * the closest legal value.
   *
   * @param volume the volume of the sound effect, in the range [0,
   * `sound_effect::max_volume()`].
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_volume(int volume) noexcept;

  /**
   * @brief Indicates whether or not the sound effect is currently playing.
   *
   * @return `true` if the sound effect is playing; `false` otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto is_playing() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the sound effect is being faded.
   *
   * @note If the sound effect is being faded, it's also playing so
   * `is_playing()` will also return `true`. Keep this in mind if you want to
   * differentiate between the two.
   *
   * @return `true` if the sound effect is being faded; `false` otherwise.
   *
   * @since 5.0.0
   */
  CENTURION_QUERY
  auto is_fading() const noexcept -> bool;

  /**
   * @brief Returns the current volume of the sound effect.
   *
   * @details By default, this property is set to 128.
   *
   * @return the current volume of the sound effect.
   *
   * @since 3.0.0
   */
  [[nodiscard]] auto volume() const noexcept -> int { return m_chunk->volume; }

  /**
   * @brief Returns a pointer to the associated `Mix_Chunk`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it is useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated `Mix_Chunk`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> Mix_Chunk*
  {
    return m_chunk.get();
  }

  /**
   * @brief Converts to `Mix_Chunk*`.
   *
   * @return a pointer to the associated `Mix_Chunk` instance.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator Mix_Chunk*() noexcept
  {
    return m_chunk.get();
  }

  /**
   * @brief Converts to `const Mix_Chunk*`.
   *
   * @return a pointer to the associated `Mix_Chunk` instance.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator const Mix_Chunk*() const noexcept
  {
    return m_chunk.get();
  }

  /**
   * @brief Returns the maximum possible volume value.
   *
   * @return the maximum possible volume value.
   *
   * @since 3.1.0
   */
  [[nodiscard]] static constexpr auto max_volume() noexcept -> int
  {
    return MIX_MAX_VOLUME;
  }

 private:
  std::unique_ptr<Mix_Chunk, detail::sound_effect_deleter> m_chunk;
  int m_channel{undefined_channel()};

  [[nodiscard]] static constexpr auto undefined_channel() noexcept -> int
  {
    return -1;
  }

  /**
   * @brief Activates the sound effect by playing it the specified amount of
   * times.
   *
   * @param nLoops the amount of times to play the sound effect.
   *
   * @since 3.0.0
   */
  void activate(int nLoops) noexcept;
};

/**
 * @brief Returns a textual representation of a sound effect.
 *
 * @ingroup audio
 *
 * @param sound the sound effect that will be converted.
 *
 * @return a string that represents the sound effect.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const sound_effect& sound) -> std::string;

/**
 * @brief Prints a textual representation of a sound effect.
 *
 * @param stream the stream that will be used.
 * @param sound the sound effect that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto operator<<(std::ostream& stream, const sound_effect& sound)
    -> std::ostream&;

static_assert(std::is_final_v<sound_effect>);
static_assert(std::is_nothrow_move_constructible_v<sound_effect>);
static_assert(std::is_nothrow_move_assignable_v<sound_effect>);
static_assert(!std::is_copy_constructible_v<sound_effect>);
static_assert(!std::is_copy_assignable_v<sound_effect>);

}  // namespace centurion

#endif  // CENTURION_SOUND_EFFECT_HEADER