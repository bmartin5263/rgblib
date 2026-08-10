#include <gtest/gtest.h>

#include "Types.h"
#include "Util.h"

using rgb::Clamp;
using rgb::ClampWrap;
using rgb::Duration;
using rgb::Max;
using rgb::Min;
using rgb::PercentBetween;
using rgb::RunningAverage;
using rgb::Timestamp;

TEST(UtilsTest, ClampWrapKeepsValueBetween0And1) {
  EXPECT_FLOAT_EQ(ClampWrap(-1.5f), 0.0f);
  EXPECT_FLOAT_EQ(ClampWrap(-1.0f), 0.0f);
  EXPECT_FLOAT_EQ(ClampWrap(-0.25f), 0.0f);
  EXPECT_FLOAT_EQ(ClampWrap(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(ClampWrap(0.5f), 0.5f);
  EXPECT_FLOAT_EQ(ClampWrap(1.0f), 1.0f);
  EXPECT_FLOAT_EQ(ClampWrap(1.25f), 0.25f);
  EXPECT_FLOAT_EQ(ClampWrap(2.0f), 0.0f);
  EXPECT_FLOAT_EQ(ClampWrap(3.75f), 0.75f);
}

TEST(UtilsTest, ClampKeepsValueWithinInclusiveBounds) {
  EXPECT_EQ(Clamp(5, 0, 10), 5);
  EXPECT_EQ(Clamp(-5, 0, 10), 0);
  EXPECT_EQ(Clamp(15, 0, 10), 10);
  EXPECT_EQ(Clamp(0, 0, 10), 0);
  EXPECT_EQ(Clamp(10, 0, 10), 10);
}

TEST(UtilsTest, ClampWorksWithCustomDurationType) {
  constexpr auto min = Duration::Milliseconds(100);
  constexpr auto max = Duration::Milliseconds(1000);

  EXPECT_EQ(Clamp(Duration::Milliseconds(500), min, max), Duration::Milliseconds(500));
  EXPECT_EQ(Clamp(Duration::Milliseconds(50), min, max), min);
  EXPECT_EQ(Clamp(Duration::Milliseconds(5000), min, max), max);
  EXPECT_EQ(Clamp(min, min, max), min);
  EXPECT_EQ(Clamp(max, min, max), max);
}

TEST(UtilsTest, PercentBetweenReturnsFractionOfRange) {
  EXPECT_FLOAT_EQ(PercentBetween(5.0f, 0.0f, 10.0f), 0.5f);
  EXPECT_FLOAT_EQ(PercentBetween(0.0f, 0.0f, 10.0f), 0.0f);
  EXPECT_FLOAT_EQ(PercentBetween(10.0f, 0.0f, 10.0f), 1.0f);
}

TEST(UtilsTest, PercentBetweenExtrapolatesOutsideRange) {
  EXPECT_FLOAT_EQ(PercentBetween(-5.0f, 0.0f, 10.0f), -0.5f);
  EXPECT_FLOAT_EQ(PercentBetween(15.0f, 0.0f, 10.0f), 1.5f);
}

TEST(UtilsTest, PercentBetweenReturnsOneWhenRangeIsZero) {
  EXPECT_FLOAT_EQ(PercentBetween(3.0f, 5.0f, 5.0f), 1.0f);
}

TEST(UtilsTest, RunningAverageBlendsValueTowardNextByFactor) {
  EXPECT_FLOAT_EQ(RunningAverage(0.0f, 10.0f, 0.5f), 5.0f);
  EXPECT_FLOAT_EQ(RunningAverage(0.0f, 10.0f, 0.0f), 0.0f);
  EXPECT_FLOAT_EQ(RunningAverage(0.0f, 10.0f, 1.0f), 10.0f);
}

TEST(UtilsTest, RunningAverageTruncatesWhenUsedWithIntegralType) {
  EXPECT_EQ(RunningAverage(0, 3, 0.5f), 1);
}

TEST(UtilsTest, MaxReturnsLargestArgument) {
  EXPECT_EQ(Max(-3, 7, -2), 7);
  EXPECT_FLOAT_EQ(Max(1.5f, -2.5f, -4.0f), 1.5f);
  EXPECT_EQ(Max(1u), 1u);
}

TEST(UtilsTest, MinReturnsSmallestArgument) {
  EXPECT_EQ(Min(-3, 7, -2), -3);
  EXPECT_FLOAT_EQ(Min(1.5f, -2.5f, -4.0f), -4.0f);
  EXPECT_EQ(Min(1u), 1u);
}

TEST(UtilsTest, MaxAndMinWorkWithCustomTimestampType) {
  constexpr auto early = Timestamp::Milliseconds(100);
  constexpr auto mid = Timestamp::Milliseconds(250);
  constexpr auto late = Timestamp::Milliseconds(500);

  EXPECT_EQ(Max(mid, early, late), late);
  EXPECT_EQ(Min(mid, early, late), early);
}

auto main(int argc, char** argv) -> int {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
