//
// Created by Brandon on 2/9/26.
//

#include "Monitor.h"
#include "Timer.h"
#include "Effects.h"
#include "Clock.h"
#include "Wireless.h"


namespace rgb {

auto Monitor::update() -> void {
  auto ip = Wifi::GetAddress();
  INFO("FPS: %i, Timers: %i / %i (peak=%i), Effects: %i / %i (peak=%i), WiFi: %u.%u.%u.%u",
    Clock::Fps(),
    Timer::ActiveCount(), Timer::Capacity(), Timer::PeakCount(),
    Effects::ActiveCount(), Effects::Capacity(), Effects::PeakCount(),
    ip[0], ip[1], ip[2], ip[3]
  );
}

}