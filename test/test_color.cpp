#include <gtest/gtest.h>

#include "RgbColor.h"

using rgb::Color;

namespace {

auto ExpectColorEq(const Color& actual, const Color& expected) -> void {
  EXPECT_FLOAT_EQ(actual.r, expected.r);
  EXPECT_FLOAT_EQ(actual.g, expected.g);
  EXPECT_FLOAT_EQ(actual.b, expected.b);
  EXPECT_FLOAT_EQ(actual.w, expected.w);
}

}

TEST(ColorTest, DefaultConstructorIsAllZero) {
  ExpectColorEq(Color{}, Color{0.f, 0.f, 0.f, 0.f});
}

TEST(ColorTest, SingleFloatConstructorSetsOnlyWhiteChannel) {
  ExpectColorEq(Color{1.0f}, Color{0.f, 0.f, 0.f, 1.0f});
}

TEST(ColorTest, ThreeFloatConstructorDefaultsWhiteToZero) {
  ExpectColorEq(Color{.25f, .5f, .75f}, Color{.25f, .5f, .75f, 0.f});
}

TEST(ColorTest, FourFloatConstructorSetsAllChannels) {
  Color color{.1f, .2f, .3f, .4f};

  EXPECT_FLOAT_EQ(color.r, .1f);
  EXPECT_FLOAT_EQ(color.g, .2f);
  EXPECT_FLOAT_EQ(color.b, .3f);
  EXPECT_FLOAT_EQ(color.w, .4f);
}

TEST(ColorTest, FromBytesConvertsComponentsToNormalizedFloats) {
  ExpectColorEq(Color::FromBytes(255, 128, 0, 64), Color{1.0f, 128.0f / 255.0f, 0.f, 64.0f / 255.0f});
}

TEST(ColorTest, FromBytesDefaultsWhiteChannelToZero) {
  ExpectColorEq(Color::FromBytes(255, 0, 255), Color{1.0f, 0.f, 1.0f, 0.f});
}

TEST(ColorTest, FromBytesPackedValueUnpacksWrgbOrder) {
  ExpectColorEq(Color::FromBytes(0x00FF00FFu), Color{1.0f, 0.f, 1.0f, 0.f});
  ExpectColorEq(Color::FromBytes(0xFF000000u), Color{0.f, 0.f, 0.f, 1.0f});
}

TEST(ColorTest, FromBytesPackedValueMatchesComponentOverload) {
  ExpectColorEq(Color::FromBytes(0x40806040u), Color::FromBytes(0x80, 0x60, 0x40, 0x40));
}

TEST(ColorTest, EqualityComparesAllChannels) {
  EXPECT_EQ(Color{.1f, .2f, .3f, .4f}, Color{.1f, .2f, .3f, .4f});
  EXPECT_NE(Color{.1f, .2f, .3f, .4f}, Color{.1f, .2f, .3f, .5f});
}

TEST(ColorTest, AdditionAndSubtractionAreComponentWise) {
  Color a{.1f, .2f, .3f, .4f};
  Color b{.4f, .3f, .2f, .1f};

  ExpectColorEq(a + b, Color{.5f, .5f, .5f, .5f});
  ExpectColorEq(a - b, Color{-.3f, -.1f, .1f, .3f});
}

TEST(ColorTest, ScalarMultiplyScalesAllChannels) {
  ExpectColorEq(Color{.1f, .2f, .3f, .4f} * 2.0f, Color{.2f, .4f, .6f, .8f});
}

TEST(ColorTest, LerpClampInterpolatesTowardTarget) {
  ExpectColorEq(Color::BLUE().lerpClamp(Color::RED(), .5f), Color{.5f, 0.f, .5f, 0.f});
}
