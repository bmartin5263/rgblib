//
// Created by Brandon on 10/12/25.
//

#ifndef RGBLIB_USER_APPLICATION_CONFIGURER_H
#define RGBLIB_USER_APPLICATION_CONFIGURER_H

#include <vector>
#include "EventType.h"
#include "Sensor.h"
#include "Func.h"

namespace rgb {

class LEDDevice;

template<typename EventVariantT = SystemEvent>
struct UserApplicationConfigurer {
  constexpr auto addPixels(LEDDevice& circuit) -> UserApplicationConfigurer&;
  constexpr auto addSensor(Sensor& sensor) -> UserApplicationConfigurer&;
  auto addBackgroundTask(Runnable runnable) -> UserApplicationConfigurer&;

  template<typename T>
  constexpr auto on(EventHandler<T> action) -> UserApplicationConfigurer&;

  std::vector<LEDDevice*> mPixels{};
  std::vector<Sensor*> mSensors{};
  std::vector<Runnable> mBackgroundTasks{};
  EventMap<EventVariantT> mEventMap{};
  bool mHeartbeat{};
};

template<typename EventVariantT>
constexpr auto UserApplicationConfigurer<EventVariantT>::addPixels(LEDDevice& circuit) -> UserApplicationConfigurer& {
  mPixels.push_back(&circuit);
  return *this;
}

template<typename EventVariantT>
constexpr auto UserApplicationConfigurer<EventVariantT>::addSensor(Sensor& sensor) -> UserApplicationConfigurer& {
  mSensors.push_back(&sensor);
  return *this;
}

template<typename EventVariantT>
auto UserApplicationConfigurer<EventVariantT>::addBackgroundTask(Runnable runnable) -> UserApplicationConfigurer& {
  mBackgroundTasks.push_back(std::move(runnable));
  return *this;
}

template<typename EventVariantT>
template<typename T>
constexpr auto UserApplicationConfigurer<EventVariantT>::on(EventHandler<T> action) -> UserApplicationConfigurer& {
  auto index = EventIndex_v<T, EventVariantT>;
  mEventMap[index].push_back([action = std::move(action)](auto& e) {
    action(std::get<T>(e));
  });
  return *this;
}



}

#endif //RGBLIB_VEHICLEAPPLICATIONBUILDER_H
