//
// Created by Brandon on 2/9/26.
//

#include <cstdio>
#include <cstdlib>
#include <atomic>

#include "Monitor.h"
#include "Timer.h"
#include "Effects.h"
#include "Animations.h"
#include "Clock.h"
#include "Wireless.h"

namespace {
std::atomic<size_t> allocations{0};
std::atomic<size_t> liveAllocations{0};
}

void* operator new(size_t size) {
  void* p = std::malloc(size);
  if (!p) {
    // Exceptions are disabled (-fno-exceptions)
    ERROR("operator new failed to allocate %u bytes", static_cast<unsigned>(size));
    std::abort();
  }
  ++allocations;
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
  allocations = 0;
  liveAllocations = 0;
}

auto Monitor::update() -> void {
  auto ip = Wifi::GetAddress();
  INFO("FPS: %i, Timers: %i / %i (peak=%i), Effects: %i / %i (peak=%i), Animations: %i / %i (peak=%i), Allocations: %i Live / %i Total, WiFi: %u.%u.%u.%u",
    Clock::Fps(),
    Timer::ActiveCount(), Timer::Capacity(), Timer::PeakCount(),
    Effects::ActiveCount(), Effects::Capacity(), Effects::PeakCount(),
    Animations::ActiveCount(), Animations::Capacity(), Animations::PeakCount(),
    liveAllocations.load(), allocations.load(),
    // 0, 0,
    ip[0], ip[1], ip[2], ip[3]
  );
}

}