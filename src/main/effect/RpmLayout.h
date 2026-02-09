//
// Created by Brandon on 3/21/25.
//

#ifndef RGBLIB_RPMSTYLE_H
#define RGBLIB_RPMSTYLE_H

#include "Types.h"

class RpmLayout {
public:
  static auto TRADITIONAL() -> const RpmLayout*;
  static auto SPORT() -> const RpmLayout*;

  virtual auto calculateOffset(rgb::u16 ledSize) const -> rgb::u16 = 0;
  virtual auto calculateLevels(rgb::u16 ledSize) const -> rgb::u16 = 0;

  RpmLayout() = default;
  RpmLayout(const RpmLayout& rhs) = default;
  RpmLayout(RpmLayout&& rhs) noexcept = default;
  RpmLayout& operator=(const RpmLayout& rhs) = default;
  RpmLayout& operator=(RpmLayout&& rhs) noexcept = default;
  virtual ~RpmLayout() = default;
};

class TraditionalRpmLayout : public RpmLayout {
public:
  auto calculateOffset(rgb::u16 ledSize) const -> rgb::u16 override;
  auto calculateLevels(rgb::u16 ledSize) const -> rgb::u16 override;

  static auto Instance() -> TraditionalRpmLayout& {
    static TraditionalRpmLayout instance;
    return instance;
  }

private:
  TraditionalRpmLayout() = default;
  TraditionalRpmLayout(const TraditionalRpmLayout& rhs) = default;
  TraditionalRpmLayout(TraditionalRpmLayout&& rhs) noexcept = default;
  TraditionalRpmLayout& operator=(const TraditionalRpmLayout& rhs) = default;
  TraditionalRpmLayout& operator=(TraditionalRpmLayout&& rhs) noexcept = default;
  ~TraditionalRpmLayout() = default;
};

class SportRpmLayout : public RpmLayout {
public:
  auto calculateOffset(rgb::u16 ledSize) const -> rgb::u16 override;
  auto calculateLevels(rgb::u16 ledSize) const -> rgb::u16 override;

  static auto Instance() -> SportRpmLayout& {
    static SportRpmLayout instance;
    return instance;
  }

private:
  SportRpmLayout() = default;
  SportRpmLayout(const SportRpmLayout& rhs) = default;
  SportRpmLayout(SportRpmLayout&& rhs) noexcept = default;
  SportRpmLayout& operator=(const SportRpmLayout& rhs) = default;
  SportRpmLayout& operator=(SportRpmLayout&& rhs) noexcept = default;
  ~SportRpmLayout() = default;
};

#endif //RGBLIB_RPMSTYLE_H
