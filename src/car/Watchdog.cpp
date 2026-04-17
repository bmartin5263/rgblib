//
// Created by Brandon on 2/9/26.
//

#include "Monitor.h"
#include "Timer.h"
#include "Effects.h"
#include "Clock.h"
#include "Vehicle.h"


namespace rgb {

auto Monitor::update() -> void {
  auto timers = Timer::ActiveCount();
  auto totalTimers = Timer::TotalCount();
  auto effects = Effects::ActiveCount();
  auto totalEffects = Effects::TotalCount();
  auto fps = Clock::Fps();
  INFO("FPS: %i   Timers: %i / %i (%i)   Effects: %i / %i", fps, timers, totalTimers, effects, totalEffects);
}

}