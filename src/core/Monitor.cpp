//
// Created by Brandon on 2/9/26.
//

#include <atomic>

#include "Monitor.h"

#include "Timer.h"
#include "Effects.h"
#include "Animations.h"
#include "Clock.h"
#if RGB_ARDUINO_ESP32
#include "Wireless.h"
#endif

namespace {
std::atomic setupAllocations{0u};
std::atomic runtimeAllocations{0u};
std::atomic liveAllocations{0u};
std::atomic afterSetup{false};
}

void* operator new(size_t size) {
  void* p = std::malloc(size);
  if (!p) {
    // Exceptions are disabled (-fno-exceptions)
    ERROR("operator new failed to allocate %u bytes", static_cast<unsigned>(size));
    std::abort();
  }
  if (afterSetup) {
    ++runtimeAllocations;
  }
  else {
    ++setupAllocations;
  }
  ++liveAllocations;
  return p;
}

void operator delete(void* p) noexcept {
  if (!p) return;
  --liveAllocations;
  std::free(p);
}

namespace rgb {

auto Monitor::initialize() -> void {
  runtimeAllocations = 0;
  liveAllocations = 0;
  afterSetup = true;
}

auto Monitor::update() -> void {
#if RGB_ARDUINO_ESP32
  auto ip = Wifi::GetAddress();
  INFO("FPS: %i, Timers: %i / %i (peak=%i), Effects: %i / %i (peak=%i), Animations: %i / %i (peak=%i), Allocations: %i Live / %i Setup / %i Runtime, WiFi: %u.%u.%u.%u",
    Clock::Fps(),
    Timer::ActiveCount(), Timer::Capacity(), Timer::PeakCount(),
    Effects::ActiveCount(), Effects::Capacity(), Effects::PeakCount(),
    Animations::ActiveCount(), Animations::Capacity(), Animations::PeakCount(),
    liveAllocations.load(), setupAllocations.load(), runtimeAllocations.load(),
    ip[0], ip[1], ip[2], ip[3]
  );
#elif RGB_NATIVE
  INFO("FPS: %i, Timers: %i / %i (peak=%i), Effects: %i / %i (peak=%i), Animations: %i / %i (peak=%i), Allocations: %i Live / %i Setup / %i Runtime",
    Clock::Fps(),
    Timer::ActiveCount(), Timer::Capacity(), Timer::PeakCount(),
    Effects::ActiveCount(), Effects::Capacity(), Effects::PeakCount(),
    Animations::ActiveCount(), Animations::Capacity(), Animations::PeakCount(),
    liveAllocations.load(), setupAllocations.load(), runtimeAllocations.load()
  );
#endif
}

}