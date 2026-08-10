//
// Created by Brandon on 2/9/26.
//

#include "Monitor.h"
#include "Timer.h"
#include "Effects.h"
#include "Clock.h"
#include "Vehicle.h"
#include "Wireless.h"


namespace rgb {

auto Monitor::update() -> void {
  INFO("FPS: %i, Timers: %i / %i (peak=%i), Effects: %i / %i (peak=%i), WiFi: %s",
    Clock::Fps(),
    Timer::ActiveCount(), Timer::Capacity(), Timer::PeakCount(),
    Effects::ActiveCount(), Effects::Capacity(), Effects::PeakCount(),
    Wifi::GetAddress().c_str()
  );
}

}