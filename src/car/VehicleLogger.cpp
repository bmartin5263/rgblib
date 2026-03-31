//
// Created by Brandon on 3/29/26.
//

#include "VehicleLogger.h"
#include "Log.h"
#include "Clock.h"
#include <SPI.h>

namespace rgb {

auto VehicleLogger::begin() -> bool {
  auto alreadyStarted = SPI.bus() != nullptr;
  SPI.begin(A1, A3, A2, A0);

  if (!SD.begin(mCsPin.to<u8>())) {
    ERROR("SD card initialization failed");
    if (alreadyStarted) {
      ERROR("SPI was already started");
    }
    return false;
  }


  auto fileNum = openNextFile();
  if (!fileNum) {
    ERROR("Could not create log file");
    return false;
  }

  INFO("SD card vehicle logging initialized with file index '%u'", fileNum);
  mLastFlush = Clock::Now();
  return true;
}

auto VehicleLogger::record(const VehicleData& data) -> void {
  if (!mFile) {
    return;
  }

  if (mCount < BUFFER_CAPACITY) {
    mBuffer[mCount++] = VehicleLogEntry{
      .timestamp = Clock::Now(),
      .data = data,
    };
  }
  else {
    ERROR("Cannot record vehicle log, at max capacity");
  }

  if (shouldFlush()) {
    flush();
  }
}

auto VehicleLogger::flush() -> void {
  if (!mFile || mCount == 0) {
    return;
  }

  INFO("Flushing %i entries", mCount);

  auto dataBuffer = reinterpret_cast<const uint8_t*>(mBuffer.data());
  auto dataSize = sizeof(VehicleLogEntry) * mCount;

  mFile.write(dataBuffer, dataSize);
  mFile.flush();

  mCount = 0;
  mLastFlush = Clock::Now();
}

auto VehicleLogger::end() -> void {
  flush();
  if (mFile) {
    mFile.close();
  }
}

auto VehicleLogger::shouldFlush() const -> bool {
  return mCount >= BUFFER_CAPACITY
    || Clock::Now().timeSince(mLastFlush) >= FLUSH_INTERVAL;
}

auto VehicleLogger::openNextFile() -> uint {
  char filename[32];
  auto mFileIndex = 1;
  while (mFileIndex < MAX_FILE_INDEX) {
    snprintf(filename, sizeof(filename), FILENAME_FORMAT, mFileIndex);
    if (!SD.exists(filename)) {
      mFile = SD.open(filename, FILE_WRITE);
      if (mFile) {
        return mFileIndex;
      }
      ERROR("Failed to open %s", filename);
      return 0;
    }
    ++mFileIndex;
  }
  ERROR("No available log file slots");
  return 0;
}

}
