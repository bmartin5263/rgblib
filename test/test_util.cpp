#include <gtest/gtest.h>

#include "Types.h"
#include "Util.h"

using rgb::ByteToFloat;
using rgb::Clamp;
using rgb::ClampWrap;
using rgb::CToF;
using rgb::Duration;
using rgb::EaseInOutBounce;
using rgb::EaseInOutCubic;
using rgb::EaseInOutExpo;
using rgb::EaseOutBounce;
using rgb::EaseOutCirc;
using rgb::EaseOutCubic;
using rgb::FloatToByte;
using rgb::Lerp;
using rgb::LerpClamp;
using rgb::LerpWrap;
using rgb::Max;
using rgb::Min;
using rgb::PercentBetween;
using rgb::Pulse;
using rgb::RunningAverage;
using rgb::SinWave;
using rgb::Timestamp;
using rgb::ToKph;
using rgb::ToMph;
using rgb::WrapUnit;

constexpr auto EPSILON = 1e-5f;

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

TEST(UtilsTest, WrapUnitKeepsValueBetween0And1) {
  EXPECT_FLOAT_EQ(WrapUnit(-1.5f), 0.5f);
  EXPECT_FLOAT_EQ(WrapUnit(-1.0f), 0.0f);
  EXPECT_FLOAT_EQ(WrapUnit(-0.25f), 0.75f);
  EXPECT_FLOAT_EQ(WrapUnit(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(WrapUnit(0.5f), 0.5f);
  EXPECT_FLOAT_EQ(WrapUnit(1.0f), 1.0f);
  EXPECT_FLOAT_EQ(WrapUnit(1.25f), 0.25f);
  EXPECT_FLOAT_EQ(WrapUnit(2.0f), 0.0f);
  EXPECT_FLOAT_EQ(WrapUnit(3.75f), 0.75f);
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

TEST(UtilsTest, EaseOutBounceMatchesKnownValues) {
  EXPECT_FLOAT_EQ(EaseOutBounce(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(EaseOutBounce(1.0f), 1.0f);
  EXPECT_FLOAT_EQ(EaseOutBounce(0.2f), 0.3025f);
  EXPECT_FLOAT_EQ(EaseOutBounce(0.5f), 0.765625f);
}

TEST(UtilsTest, EaseInOutBounceMatchesKnownValues) {
  EXPECT_FLOAT_EQ(EaseInOutBounce(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(EaseInOutBounce(1.0f), 1.0f);
  EXPECT_FLOAT_EQ(EaseInOutBounce(0.5f), 0.5f);
  EXPECT_FLOAT_EQ(EaseInOutBounce(0.25f), 0.1171875f);
  EXPECT_FLOAT_EQ(EaseInOutBounce(0.75f), 0.8828125f);
}

TEST(UtilsTest, EaseOutCircMatchesKnownValues) {
  EXPECT_FLOAT_EQ(EaseOutCirc(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(EaseOutCirc(1.0f), 1.0f);
  EXPECT_NEAR(EaseOutCirc(0.5f), 0.8660254f, EPSILON);
}

TEST(UtilsTest, EaseOutCubicMatchesKnownValues) {
  EXPECT_FLOAT_EQ(EaseOutCubic(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(EaseOutCubic(1.0f), 1.0f);
  EXPECT_FLOAT_EQ(EaseOutCubic(0.5f), 0.875f);
}

TEST(UtilsTest, EaseInOutExpoMatchesKnownValues) {
  EXPECT_FLOAT_EQ(EaseInOutExpo(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(EaseInOutExpo(1.0f), 1.0f);
  EXPECT_FLOAT_EQ(EaseInOutExpo(0.5f), 0.5f);
  EXPECT_FLOAT_EQ(EaseInOutExpo(0.25f), 0.015625f);
  EXPECT_FLOAT_EQ(EaseInOutExpo(0.75f), 0.984375f);
}

TEST(UtilsTest, EaseInOutCubicMatchesKnownValues) {
  EXPECT_FLOAT_EQ(EaseInOutCubic(0.0f), 0.0f);
  EXPECT_FLOAT_EQ(EaseInOutCubic(1.0f), 1.0f);
  EXPECT_FLOAT_EQ(EaseInOutCubic(0.25f), 0.0625f);
  EXPECT_FLOAT_EQ(EaseInOutCubic(0.5f), 0.5f);
  EXPECT_FLOAT_EQ(EaseInOutCubic(0.75f), 0.9375f);
}

TEST(UtilsTest, PulseTracksSinWavePhaseWithinPeriod) {
  constexpr auto period = Duration::Milliseconds(1000);

  EXPECT_NEAR(Pulse(Timestamp::Milliseconds(0), period), 0.5f, EPSILON);
  EXPECT_NEAR(Pulse(Timestamp::Milliseconds(250), period), 1.0f, EPSILON);
  EXPECT_NEAR(Pulse(Timestamp::Milliseconds(500), period), 0.5f, EPSILON);
  EXPECT_NEAR(Pulse(Timestamp::Milliseconds(750), period), 0.0f, EPSILON);
}

TEST(UtilsTest, PulseWrapsAroundPeriodBoundary) {
  constexpr auto period = Duration::Milliseconds(1000);

  EXPECT_NEAR(Pulse(Timestamp::Milliseconds(1000), period), 0.5f, EPSILON);
  EXPECT_NEAR(Pulse(Timestamp::Milliseconds(1250), period), 1.0f, EPSILON);
}

TEST(UtilsTest, FloatToByteScalesFractionToByteRange) {
  EXPECT_EQ(FloatToByte(-0.5f), 0);
  EXPECT_EQ(FloatToByte(0.0f), 0);
  EXPECT_EQ(FloatToByte(0.25f), 63);
  EXPECT_EQ(FloatToByte(0.5f), 127);
  EXPECT_EQ(FloatToByte(0.75f), 191);
  EXPECT_EQ(FloatToByte(1.0f), 255);
  EXPECT_EQ(FloatToByte(1.5f), 255);
}

TEST(UtilsTest, ByteToFloatScalesByteToFractionRange) {
  EXPECT_FLOAT_EQ(ByteToFloat(0), 0.0f);
  EXPECT_FLOAT_EQ(ByteToFloat(64), 64.0f / 255.0f);
  EXPECT_FLOAT_EQ(ByteToFloat(128), 128.0f / 255.0f);
  EXPECT_FLOAT_EQ(ByteToFloat(255), 1.0f);
}

TEST(UtilsTest, ToMphConvertsFromKph) {
  EXPECT_EQ(ToMph(0), 0);
  EXPECT_EQ(ToMph(60), 37);
  EXPECT_EQ(ToMph(100), 62);
}

TEST(UtilsTest, ToKphConvertsFromMph) {
  EXPECT_EQ(ToKph(0), 0);
  EXPECT_EQ(ToKph(50), 80);
  EXPECT_EQ(ToKph(100), 160);
}

TEST(UtilsTest, CToFConvertsKnownReferencePoints) {
  EXPECT_FLOAT_EQ(CToF(0.0f), 32.0f);
  EXPECT_FLOAT_EQ(CToF(100.0f), 212.0f);
  EXPECT_FLOAT_EQ(CToF(-40.0f), -40.0f);
}

TEST(UtilsTest, LerpInterpolatesBetweenAAndB) {
  EXPECT_FLOAT_EQ(Lerp(0.0f, 10.0f, 0.0f), 0.0f);
  EXPECT_FLOAT_EQ(Lerp(0.0f, 10.0f, 1.0f), 10.0f);
  EXPECT_FLOAT_EQ(Lerp(0.0f, 10.0f, 0.5f), 5.0f);
  EXPECT_FLOAT_EQ(Lerp(10.0f, 0.0f, 0.25f), 7.5f);
}

TEST(UtilsTest, LerpExtrapolatesOutsideZeroToOneRange) {
  EXPECT_FLOAT_EQ(Lerp(0.0f, 10.0f, 1.5f), 15.0f);
  EXPECT_FLOAT_EQ(Lerp(0.0f, 10.0f, -0.5f), -5.0f);
}

TEST(UtilsTest, LerpWrapKeepsTWithinZeroToOneRange) {
  EXPECT_FLOAT_EQ(LerpWrap(0.0f, 10.0f, 0.5f), 5.0f);
  EXPECT_FLOAT_EQ(LerpWrap(0.0f, 10.0f, 1.0f), 10.0f);
  EXPECT_FLOAT_EQ(LerpWrap(0.0f, 10.0f, 1.25f), 2.5f);
  EXPECT_FLOAT_EQ(LerpWrap(0.0f, 10.0f, -0.25f), 7.5f);
}

TEST(UtilsTest, LerpClampHoldsAtEndpointsOutsideZeroToOneRange) {
  EXPECT_FLOAT_EQ(LerpClamp(0.0f, 10.0f, -0.5f), 0.0f);
  EXPECT_FLOAT_EQ(LerpClamp(0.0f, 10.0f, 0.0f), 0.0f);
  EXPECT_FLOAT_EQ(LerpClamp(0.0f, 10.0f, 1.0f), 10.0f);
  EXPECT_FLOAT_EQ(LerpClamp(0.0f, 10.0f, 1.5f), 10.0f);
  EXPECT_FLOAT_EQ(LerpClamp(0.0f, 10.0f, 0.5f), 5.0f);
}

TEST(UtilsTest, SinWaveMatchesKnownPhasePoints) {
  EXPECT_NEAR(SinWave(0.0f), 0.0f, EPSILON);
  EXPECT_NEAR(SinWave(2.5f), 1.0f, EPSILON);
  EXPECT_NEAR(SinWave(5.0f), 0.0f, EPSILON);
  EXPECT_NEAR(SinWave(7.5f), -1.0f, EPSILON);
}

TEST(UtilsTest, SinWaveUsesProvidedFrequency) {
  EXPECT_NEAR(SinWave(0.0f, 0.25f), 0.0f, EPSILON);
  EXPECT_NEAR(SinWave(1.0f, 0.25f), 1.0f, EPSILON);
  EXPECT_NEAR(SinWave(2.0f, 0.25f), 0.0f, EPSILON);
  EXPECT_NEAR(SinWave(3.0f, 0.25f), -1.0f, EPSILON);

  EXPECT_NEAR(SinWave(0.25f, 1.0f), 1.0f, EPSILON);
  EXPECT_NEAR(SinWave(0.5f, 1.0f), 0.0f, EPSILON);
  EXPECT_NEAR(SinWave(0.75f, 1.0f), -1.0f, EPSILON);
}

auto main(int argc, char** argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
