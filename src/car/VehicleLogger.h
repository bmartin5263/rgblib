//
// Created by Brandon on 3/29/26.
//

#ifndef RGBLIB_VEHICLELOGGER_H
#define RGBLIB_VEHICLELOGGER_H

#include "VehicleData.h"
#include "Clock.h"
#include "Pin.h"
#include <SD.h>
#include <SPI.h>
#include <array>


namespace rgb {

struct VehicleLogEntry {
  Timestamp timestamp{};
  VehicleData data{};
};

class VehicleLogger {
public:
  static constexpr auto FILENAME_FORMAT = "/vlog_%08u.bin"; // / vlog_00000001.bin
  static constexpr auto MAX_FILE_INDEX = 99999999; // arbitrary limit
  static constexpr auto SECONDS_BETWEEN_FLUSHES = 10;
  static constexpr auto UPDATES_PER_SECOND = 10;
  static constexpr auto BUFFER_CAPACITY = SECONDS_BETWEEN_FLUSHES * UPDATES_PER_SECOND;
  static constexpr auto FLUSH_INTERVAL = Duration::Seconds(SECONDS_BETWEEN_FLUSHES);

  explicit VehicleLogger(PinNumber csPin) : mCsPin(csPin) {}

  auto begin() -> bool;
  auto record(const VehicleData& data) -> void;
  auto flush() -> void;
  auto end() -> void;

private:
  auto openNextFile() -> uint;
  auto shouldFlush() const -> bool;

  PinNumber mCsPin;
  std::array<VehicleLogEntry, BUFFER_CAPACITY> mBuffer{};
  size_t mCount{0};
  Timestamp mLastFlush{};
  File mFile{};
};

}

#endif //RGBLIB_VEHICLELOGGER_H
