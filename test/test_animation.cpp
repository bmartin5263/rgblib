#include <gtest/gtest.h>

#include <array>
#include <vector>

#include "Frames.h"
#include "ArrayAnimation.h"

using rgb::Animation;
using rgb::ArrayAnimation;
using rgb::Duration;
using rgb::Frames;

namespace {
constexpr auto DURATION = Duration::Milliseconds(125);
}

TEST(AnimationTest, ForFrameRunsOncePerIteration) {
  std::vector<int> indices;
  std::vector<float> percents;
  auto animation = ArrayAnimation{std::array{
    Frames::For(DURATION, 4, [&](auto& ctx) {
      indices.push_back(ctx.index());
      percents.push_back(ctx.percentComplete());
    })
  }};

  EXPECT_EQ(animation.update(Duration::Zero()), Animation::UpdateResult::RUNNING);
  EXPECT_EQ(indices, (std::vector{0}));
  EXPECT_EQ(animation.update(DURATION), Animation::UpdateResult::RUNNING);
  EXPECT_EQ(animation.update(Duration::Milliseconds(10)), Animation::UpdateResult::RUNNING);
  EXPECT_EQ(indices, (std::vector{0, 1}));
  EXPECT_EQ(animation.update(DURATION * 2), Animation::UpdateResult::RUNNING);
  EXPECT_EQ(indices, (std::vector{0, 1, 2, 3}));
  ASSERT_EQ(percents.size(), 4u);
  for (int i = 0; i < percents.size(); ++i) {
    EXPECT_FLOAT_EQ(percents[i], static_cast<float>(i) / 3.0f);
  }
  EXPECT_EQ(animation.update(DURATION), Animation::UpdateResult::FINISHED);
  EXPECT_EQ(indices.size(), 4u);
  EXPECT_EQ(percents.size(), 4u);
}

TEST(AnimationTest, ForFrameCatchesUpOnLargeDelta) {
  int calls = 0;
  auto animation = ArrayAnimation{std::array{
    Frames::For(DURATION, 8, [&](auto&) { ++calls; })
  }};

  EXPECT_EQ(animation.update(DURATION * 20), Animation::UpdateResult::FINISHED);
  EXPECT_EQ(calls, 8u);
}

TEST(AnimationTest, ForFrameCarriesLeftoverTimeToNextFrame) {
  bool leftOverTimeWasCarriedOver = false;
  auto animation = ArrayAnimation{std::array{
    Frames::For(DURATION, 2, [](auto&) {}),
    Frames::Wait(DURATION),
    Frames::Once([&](auto&) { leftOverTimeWasCarriedOver = true; })
  }};

  EXPECT_EQ(animation.update(DURATION * 3), Animation::UpdateResult::FINISHED);
  EXPECT_TRUE(leftOverTimeWasCarriedOver);
}

TEST(AnimationTest, WhileFrameRunsUntilConditionFalse) {
  auto active = true;
  auto calls = 0;
  auto lastElapsed = Duration{};
  auto done = false;
  auto animation = ArrayAnimation{std::array{
    Frames::While([&] { return active; }, [&](auto& ctx) {
      ++calls;
      lastElapsed = ctx.elapsed();
    }),
    Frames::Once([&](auto&) { done = true; })
  }};

  EXPECT_EQ(animation.update(DURATION), Animation::UpdateResult::RUNNING);
  EXPECT_EQ(animation.update(DURATION), Animation::UpdateResult::RUNNING);
  EXPECT_EQ(calls, 2u);
  EXPECT_EQ(lastElapsed, DURATION * 2);
  EXPECT_FALSE(done);

  active = false;
  EXPECT_EQ(animation.update(DURATION), Animation::UpdateResult::FINISHED);
  EXPECT_EQ(calls, 2u);
  EXPECT_TRUE(done);
}

TEST(AnimationTest, WhileFrameSkippedWhenConditionInitiallyFalse) {
  auto calls = 0;
  auto animation = ArrayAnimation{std::array{
    Frames::While([] { return false; }, [&](auto&) { ++calls; })
  }};

  EXPECT_EQ(animation.update(DURATION), Animation::UpdateResult::FINISHED);
  EXPECT_EQ(calls, 0u);
}

TEST(AnimationTest, TimedFrameReportsPercentCompleteThroughDuration) {
  auto last = -1.0f;
  auto animation = ArrayAnimation{std::array{
    Frames::Of(Duration::Seconds(1), [&](auto& ctx) { last = ctx.percentComplete; })
  }};

  EXPECT_EQ(animation.update(Duration::Milliseconds(500)), Animation::UpdateResult::RUNNING);
  EXPECT_FLOAT_EQ(last, 0.5f);
  EXPECT_EQ(animation.update(Duration::Milliseconds(500)), Animation::UpdateResult::FINISHED);
  EXPECT_FLOAT_EQ(last, 1.0f);
}

TEST(AnimationTest, ResetRestartsAnimation) {
  int calls = 0;
  auto animation = ArrayAnimation{std::array{
    Frames::For(DURATION, 2, [&](auto&) { ++calls; })
  }};

  EXPECT_EQ(animation.update(DURATION * 2), Animation::UpdateResult::FINISHED);
  animation.reset();
  EXPECT_EQ(animation.update(DURATION * 2), Animation::UpdateResult::FINISHED);
  EXPECT_EQ(calls, 4u);
}
