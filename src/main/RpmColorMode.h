//
// Created by Brandon on 3/21/25.
//

#ifndef RGBLIB_COLORMODE_H
#define RGBLIB_COLORMODE_H

#include "Types.h"
#include "rgb/Color.h"
#include "RpmGaugeCalculations.h"

class RpmEffect;
class RpmColorMode {
public:
  static auto PARTITIONED() -> const RpmColorMode*;
  static auto SINGLE() -> const RpmColorMode*;
  static auto BLENDED() -> const RpmColorMode*;

  virtual auto calculateColor(const RpmGaugeCalculations& calculations, const RpmEffect& effect) const -> rgb::Color = 0;

  RpmColorMode() = default;
  RpmColorMode(const RpmColorMode& rhs) = default;
  RpmColorMode(RpmColorMode&& rhs) noexcept = default;
  RpmColorMode& operator=(const RpmColorMode& rhs) = default;
  RpmColorMode& operator=(RpmColorMode&& rhs) noexcept = default;
  virtual ~RpmColorMode() = default;

  friend class RpmEffect;
};

class PartitionedRpmColorMode : public RpmColorMode {
public:
  auto calculateColor(const RpmGaugeCalculations& calculations, const RpmEffect& effect) const -> rgb::Color override;

  static auto Instance() -> PartitionedRpmColorMode& {
    static PartitionedRpmColorMode instance;
    return instance;
  }

private:
  PartitionedRpmColorMode() = default;
  PartitionedRpmColorMode(const PartitionedRpmColorMode& rhs) = default;
  PartitionedRpmColorMode(PartitionedRpmColorMode&& rhs) noexcept = default;
  PartitionedRpmColorMode& operator=(const PartitionedRpmColorMode& rhs) = default;
  PartitionedRpmColorMode& operator=(PartitionedRpmColorMode&& rhs) noexcept = default;
  ~PartitionedRpmColorMode() override = default;
};

class SingleRpmColorMode : public RpmColorMode {
public:
  auto calculateColor(const RpmGaugeCalculations& calculations, const RpmEffect& effect) const -> rgb::Color override;

  static auto Instance() -> SingleRpmColorMode& {
    static SingleRpmColorMode instance;
    return instance;
  }

private:
  SingleRpmColorMode() = default;
  SingleRpmColorMode(const SingleRpmColorMode& rhs) = default;
  SingleRpmColorMode(SingleRpmColorMode&& rhs) noexcept = default;
  SingleRpmColorMode& operator=(const SingleRpmColorMode& rhs) = default;
  SingleRpmColorMode& operator=(SingleRpmColorMode&& rhs) noexcept = default;
  ~SingleRpmColorMode() override = default;
};

class BlendedRpmColorMode : public RpmColorMode {
public:
  auto calculateColor(const RpmGaugeCalculations& calculations, const RpmEffect& effect) const -> rgb::Color override;

  static auto Instance() -> BlendedRpmColorMode& {
    static BlendedRpmColorMode instance;
    return instance;
  }

private:
  BlendedRpmColorMode() = default;
  BlendedRpmColorMode(const BlendedRpmColorMode& rhs) = default;
  BlendedRpmColorMode(BlendedRpmColorMode&& rhs) noexcept = default;
  BlendedRpmColorMode& operator=(const BlendedRpmColorMode& rhs) = default;
  BlendedRpmColorMode& operator=(BlendedRpmColorMode&& rhs) noexcept = default;
  ~BlendedRpmColorMode() override = default;
};

#endif //RGBLIB_COLORMODE_H
