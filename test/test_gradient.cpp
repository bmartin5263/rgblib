#include <gtest/gtest.h>

#include "ArrayGradient.h"
#include "Gradient.h"
#include "RgbColor.h"

using rgb::ArrayGradient;
using rgb::Color;
using rgb::Gradient;
using rgb::GradientStop;

namespace {

auto ExpectColorEq(const Color& actual, const Color& expected) -> void {
  EXPECT_FLOAT_EQ(actual.r, expected.r);
  EXPECT_FLOAT_EQ(actual.g, expected.g);
  EXPECT_FLOAT_EQ(actual.b, expected.b);
  EXPECT_FLOAT_EQ(actual.w, expected.w);
}

}

TEST(ArrayGradientTest, SampleReturnsExactStopColorsAtStopPositions) {
  ArrayGradient gradient{std::array {
    GradientStop {0.0f, Color::BLUE()},
    GradientStop {.2f, Color::RED()},
    GradientStop {1.0f, Color::GREEN()},
  }};

  ExpectColorEq(gradient.sample(0.0f), Color::BLUE());
  ExpectColorEq(gradient.sample(.2f), Color::RED());
  ExpectColorEq(gradient.sample(1.0f), Color::GREEN());
}

TEST(ArrayGradientTest, SampleInterpolatesBetweenStops) {
  ArrayGradient gradient{std::array {
    GradientStop {0.0f, Color::BLUE()},
    GradientStop {.2f, Color::RED()},
    GradientStop {1.0f, Color::GREEN()},
  }};

  ExpectColorEq(gradient.sample(.1f), Color::BLUE().lerpClamp(Color::RED(), .5f));
  ExpectColorEq(gradient.sample(.6f), Color::RED().lerpClamp(Color::GREEN(), .5f));
}

TEST(ArrayGradientTest, SampleClampsToFirstAndLastStopOutsideRange) {
  ArrayGradient gradient{std::array {
    GradientStop {0.0f, Color::BLUE()},
    GradientStop {.2f, Color::RED()},
    GradientStop {1.0f, Color::GREEN()},
  }};

  ExpectColorEq(gradient.sample(-5.0f), Color::BLUE());
  ExpectColorEq(gradient.sample(5.0f), Color::GREEN());
}

TEST(ArrayGradientTest, LeadingStopPositionDefaultsToZeroWhenOmitted) {
  ArrayGradient withPosition{std::array {
    GradientStop {0.0f, Color::BLUE()},
    GradientStop {.2f, Color::RED()},
    GradientStop {1.0f, Color::GREEN()},
  }};
  ArrayGradient withoutPosition{std::array {
    GradientStop { Color::BLUE() },
    GradientStop {.2f, Color::RED()},
    GradientStop {1.0f, Color::GREEN()},
  }};

  ExpectColorEq(withoutPosition.sample(0.0f), withPosition.sample(0.0f));
  ExpectColorEq(withoutPosition.sample(.1f), withPosition.sample(.1f));
}

TEST(ArrayGradientTest, AllPositionsOmittedAreSpreadEvenlyForThreeStops) {
  ArrayGradient gradient{std::array {
    GradientStop {Color::RED()},
    GradientStop {Color::GREEN()},
    GradientStop {Color::BLUE()},
  }};

  ExpectColorEq(gradient.sample(0.0f), Color::RED());
  ExpectColorEq(gradient.sample(.5f), Color::GREEN());
  ExpectColorEq(gradient.sample(1.0f), Color::BLUE());
}

TEST(ArrayGradientTest, AllPositionsOmittedAreSpreadEvenlyForFourStops) {
  ArrayGradient gradient{std::array {
    GradientStop {Color::RED()},
    GradientStop {Color::GREEN()},
    GradientStop {Color::BLUE()},
    GradientStop {Color::YELLOW()},
  }};

  ExpectColorEq(gradient.sample(0.0f), Color::RED());
  ExpectColorEq(gradient.sample(1.0f / 3.0f), Color::GREEN());
  ExpectColorEq(gradient.sample(2.0f / 3.0f), Color::BLUE());
  ExpectColorEq(gradient.sample(1.0f), Color::YELLOW());
}

TEST(ArrayGradientTest, SingleStopGradientReturnsConstantColor) {
  ArrayGradient gradient{std::array{GradientStop {Color::RED()}}};

  ExpectColorEq(gradient.sample(-1.0f), Color::RED());
  ExpectColorEq(gradient.sample(0.0f), Color::RED());
  ExpectColorEq(gradient.sample(0.5f), Color::RED());
  ExpectColorEq(gradient.sample(2.0f), Color::RED());
}

TEST(ArrayGradientTest, StopCountReturnsNumberOfStops) {
  EXPECT_EQ(ArrayGradient<3>::StopCount(), 3u);
  EXPECT_EQ(ArrayGradient<1>::StopCount(), 1u);
}

TEST(ArrayGradientTest, SampledThroughGradientSourceInterfaceDispatchesToArrayGradient) {
  ArrayGradient gradient{std::array {
    GradientStop {0.0f, Color::BLUE()},
    GradientStop {.2f, Color::RED()},
    GradientStop {1.0f, Color::GREEN()},
  }};

  const Gradient& source = gradient;

  ExpectColorEq(source.sample(0.0f), Color::BLUE());
  ExpectColorEq(source.sample(.2f), Color::RED());
  ExpectColorEq(source.sample(1.0f), Color::GREEN());
}
