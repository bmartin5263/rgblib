//
// Created by Brandon on 8/11/26.
//

#ifndef RGBLIB_ARRAYGRADIENT_H
#define RGBLIB_ARRAYGRADIENT_H

#include "Gradient.h"
#include "RgbColor.h"
#include "Types.h"
#include "Util.h"

#include <algorithm>
#include <array>
#include <utility>

namespace rgb {

struct GradientStop {
  constexpr GradientStop(normal position, Color color) : position(position), color(std::move(color)), hasPosition(true) {}
  constexpr GradientStop(Color color) : position(0.0f), color(std::move(color)), hasPosition(false) {}

  normal position;
  Color color;
  bool hasPosition;
};

/**
 * A Gradient backed by a fixed-size array of N Color stops, each starting at a
 * position. Stops must be given in ascending position order. The first stop's position
 * may be omitted, it defaults to 0.0f:
 *
 *   ArrayGradient sunset{std::array {
 *     GradientStop {Color::BLUE()},
 *     GradientStop {.2f, Color::RED()},
 *     GradientStop {1.0f, Color::YELLOW()},
 *   }};
 *
 *   auto color = sunset.sample(.2f); // color == Color::RED()
 *
 * If every stop's position is omitted, they're spread evenly across 0.0f-1.0f instead:
 *
 *   ArrayGradient rainbow{std::array {
 *     GradientStop {Color::RED()},
 *     GradientStop {Color::GREEN()},
 *     GradientStop {Color::BLUE()},
 *   }}; // positions become 0.0f, 0.5f, 1.0f
 */
template<size_t N>
class ArrayGradient : public Gradient {
  static_assert(N >= 1, "ArrayGradient requires at least one stop");

public:
  explicit ArrayGradient(std::array<GradientStop, N> stops) : mStops(std::move(stops)) {
    auto allPositionsOmitted = std::all_of(mStops.begin(), mStops.end(), [](auto& stop) {
      return !stop.hasPosition;
    });
    if (allPositionsOmitted) {
      computePositionsEvenly();
    }
  }

  [[nodiscard]]
  auto sample(normal position) const -> Color override {
    if (position <= mStops.front().position) {
      return mStops.front().color;
    }
    if (position >= mStops.back().position) {
      return mStops.back().color;
    }
    for (size_t i = 1; i < N; ++i) {
      if (position <= mStops[i].position) {
        const auto& from = mStops[i - 1];
        const auto& to = mStops[i];
        return from.color.lerpClamp(to.color, PercentBetween(position, from.position, to.position));
      }
    }
    return mStops.back().color;
  }

  [[nodiscard]]
  static constexpr auto StopCount() -> size_t {
    return N;
  }

private:
  std::array<GradientStop, N> mStops;

  auto computePositionsEvenly() {
    if (N == 1) {
      return;
    }
    for (size_t i = 0; i < N; ++i) {
      mStops[i].position = static_cast<normal>(i) / static_cast<normal>(N - 1);
    }
  }
};

namespace detail {

template<size_t M, size_t... I>
constexpr auto MirrorStops(const std::array<GradientStop, M>& half, std::index_sequence<I...>)
    -> std::array<GradientStop, 2 * M - 1> {
  return {half[I <= M - 1 ? M - 1 - I : I - (M - 1)]...};
}

}

/**
 * Builds a symmetric ArrayGradient from just one "half" of its stops. The first
 * stop is the center of the gradient; the rest fan outward from it. The half is
 * mirrored around the center to produce the full, symmetric gradient, so this:
 *
 *   auto ocean = MirroredGradient(std::array {
 *     GradientStop {Color::CYAN()}, // center
 *     GradientStop {Color::BLUE()},
 *     GradientStop {Color::PURPLE()},
 *     GradientStop {Color::MAGENTA()},
 *   });
 *
 * is equivalent to:
 *
 *   auto ocean = ArrayGradient{std::array {
 *     GradientStop {Color::MAGENTA()},
 *     GradientStop {Color::PURPLE()},
 *     GradientStop {Color::BLUE()},
 *     GradientStop {Color::CYAN()},
 *     GradientStop {Color::BLUE()},
 *     GradientStop {Color::PURPLE()},
 *     GradientStop {Color::MAGENTA()},
 *   }};
 *
 *   This is useful for gradient effects that have wrapping behavior
 */
template<size_t M>
constexpr auto MirroredGradient(std::array<GradientStop, M> half) -> ArrayGradient<2 * M - 1> {
  static_assert(M >= 1, "MirroredGradient requires at least one stop");
  return ArrayGradient<2 * M - 1>{detail::MirrorStops(half, std::make_index_sequence<2 * M - 1>{})};
}

}

#endif //RGBLIB_ARRAYGRADIENT_H
