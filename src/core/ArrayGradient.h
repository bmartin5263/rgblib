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
    auto allPositionsOmitted = std::all_of(mStops.begin(), mStops.end(), [](const GradientStop& stop) {
      return !stop.hasPosition;
    });
    if (allPositionsOmitted) {
      for (size_t i = 0; i < N; ++i) {
        mStops[i].position = N == 1 ? 0.0f : static_cast<normal>(i) / static_cast<normal>(N - 1);
      }
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
};

}

#endif //RGBLIB_ARRAYGRADIENT_H
