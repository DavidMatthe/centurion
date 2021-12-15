#ifndef CENTURION_VIDEO_HPP_
#define CENTURION_VIDEO_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "core/exception.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 16)

enum class FlashOp {
  Cancel = SDL_FLASH_CANCEL,             /* Cancel any current flashing. */
  Briefly = SDL_FLASH_BRIEFLY,           /* Briefly flash the window. */
  UntilFocused = SDL_FLASH_UNTIL_FOCUSED /* Flash the window until it's focused. */
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

enum class BlendMode {
  None = SDL_BLENDMODE_NONE,   /* No blending. */
  Blend = SDL_BLENDMODE_BLEND, /* Alpha blending. */
  Add = SDL_BLENDMODE_ADD,     /* Additive blending. */
  Mod = SDL_BLENDMODE_MOD,     /* Color modulation. */

#if SDL_VERSION_ATLEAST(2, 0, 12)

  Mul = SDL_BLENDMODE_MUL, /* Color multiplication. */

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  Invalid = SDL_BLENDMODE_INVALID
};

enum class BlendFactor {
  Zero = SDL_BLENDFACTOR_ZERO,
  One = SDL_BLENDFACTOR_ONE,

  SrcColor = SDL_BLENDFACTOR_SRC_COLOR,
  OneMinusSrcColor = SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,

  SrcAlpha = SDL_BLENDFACTOR_SRC_ALPHA,
  OneMinusSrcAlpha = SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,

  DstColor = SDL_BLENDFACTOR_DST_COLOR,
  OneMinusDstColor = SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,

  DstAlpha = SDL_BLENDFACTOR_DST_ALPHA,
  OneMinusDstAlpha = SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA
};

enum class BlendOp {
  Add = SDL_BLENDOPERATION_ADD,
  Sub = SDL_BLENDOPERATION_SUBTRACT,
  ReverseSub = SDL_BLENDOPERATION_REV_SUBTRACT,
  Min = SDL_BLENDOPERATION_MINIMUM,
  Max = SDL_BLENDOPERATION_MAXIMUM
};

/* Describes how a blend mode factors should be combined. */
struct BlendTask final {
  BlendFactor src;  ///< The blend factor applied to the source pixels.
  BlendFactor dst;  ///< The blend factor applied to the destination pixels.
  BlendOp op;       ///< The operation used to combine the source and destination pixels.
};

[[nodiscard]] inline auto compose_blend_mode(const BlendTask& color,
                                             const BlendTask& alpha) noexcept -> BlendMode
{
  const auto res = SDL_ComposeCustomBlendMode(static_cast<SDL_BlendFactor>(color.src),
                                              static_cast<SDL_BlendFactor>(color.dst),
                                              static_cast<SDL_BlendOperation>(color.op),
                                              static_cast<SDL_BlendFactor>(alpha.src),
                                              static_cast<SDL_BlendFactor>(alpha.dst),
                                              static_cast<SDL_BlendOperation>(alpha.op));
  return static_cast<BlendMode>(res);
}

#if SDL_VERSION_ATLEAST(2, 0, 16)

[[nodiscard]] constexpr auto to_string(const FlashOp op) -> std::string_view
{
  switch (op) {
    case FlashOp::Cancel:
      return "Cancel";

    case FlashOp::Briefly:
      return "Briefly";

    case FlashOp::UntilFocused:
      return "UntilFocused";

    default:
      throw Error{"Did not recognize window flash operation!"};
  }
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

[[nodiscard]] constexpr auto to_string(const BlendMode mode) -> std::string_view
{
  switch (mode) {
    case BlendMode::None:
      return "None";

    case BlendMode::Blend:
      return "Blend";

    case BlendMode::Add:
      return "Add";

    case BlendMode::Mod:
      return "Mod";

    case BlendMode::Invalid:
      return "Invalid";

#if SDL_VERSION_ATLEAST(2, 0, 12)

    case BlendMode::Mul:
      return "Mul";

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    default:
      throw Error{"Did not recognize blend mode!"};
  }
}

[[nodiscard]] constexpr auto to_string(const BlendFactor factor) -> std::string_view
{
  switch (factor) {
    case BlendFactor::Zero:
      return "Zero";

    case BlendFactor::One:
      return "One";

    case BlendFactor::SrcColor:
      return "SrcColor";

    case BlendFactor::OneMinusSrcColor:
      return "OneMinusSrcColor";

    case BlendFactor::SrcAlpha:
      return "SrcAlpha";

    case BlendFactor::OneMinusSrcAlpha:
      return "OneMinusSrcAlpha";

    case BlendFactor::DstColor:
      return "DstColor";

    case BlendFactor::OneMinusDstColor:
      return "OneMinusDstColor";

    case BlendFactor::DstAlpha:
      return "DstAlpha";

    case BlendFactor::OneMinusDstAlpha:
      return "OneMinusDstAlpha";

    default:
      throw Error{"Did not recognize blend factor!"};
  }
}

[[nodiscard]] constexpr auto to_string(const BlendOp op) -> std::string_view
{
  switch (op) {
    case BlendOp::Add:
      return "Add";

    case BlendOp::Sub:
      return "Sub";

    case BlendOp::ReverseSub:
      return "ReverseSub";

    case BlendOp::Min:
      return "Min";

    case BlendOp::Max:
      return "Max";

    default:
      throw Error{"Did not recognize blend operation!"};
  }
}

#if SDL_VERSION_ATLEAST(2, 0, 16)

inline auto operator<<(std::ostream& stream, const FlashOp op) -> std::ostream&
{
  return stream << to_string(op);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

inline auto operator<<(std::ostream& stream, const BlendMode mode) -> std::ostream&
{
  return stream << to_string(mode);
}

inline auto operator<<(std::ostream& stream, const BlendFactor factor) -> std::ostream&
{
  return stream << to_string(factor);
}

inline auto operator<<(std::ostream& stream, const BlendOp op) -> std::ostream&
{
  return stream << to_string(op);
}

}  // namespace cen

#endif  // CENTURION_VIDEO_HPP_
