//
// Created by Brandon on 10/12/25.
//

#ifndef RGBLIB_VEHICLEAPPLICATIONBUILDER2_H
#define RGBLIB_VEHICLEAPPLICATIONBUILDER2_H

#include <vector>
#include <unordered_map>
#include <typeindex>
#include "EventType.h"
#include "Func.h"
#include "Sensor.h"

namespace rgb {

class LEDCircuit;

template<typename EventVariantT = SystemEvent>
struct UserApplicationConfigurer {
  constexpr auto addLEDs(LEDCircuit& circuit) -> UserApplicationConfigurer&;
  constexpr auto addSensor(Sensor& sensor) -> UserApplicationConfigurer&;

  constexpr auto useHeartbeatLED() -> UserApplicationConfigurer&;

  template<typename T>
  constexpr auto on(std::function<void(const T&)> action) -> UserApplicationConfigurer&;

  std::vector<LEDCircuit*> mLeds{};
  std::vector<Sensor*> mSensors{};
  std::unordered_map<uint, std::vector<std::function<void(const EventVariantT&)>>> mEventMap{};
  bool mHeartbeat{};
};

template<typename EventVariantT>
constexpr auto UserApplicationConfigurer<EventVariantT>::useHeartbeatLED() -> UserApplicationConfigurer& {
  mHeartbeat = true;
  return *this;
}

template<typename EventVariantT>
constexpr auto UserApplicationConfigurer<EventVariantT>::addLEDs(rgb::LEDCircuit& circuit) -> UserApplicationConfigurer& {
  mLeds.push_back(&circuit);
  return *this;
}

template<typename EventVariantT>
constexpr auto UserApplicationConfigurer<EventVariantT>::addSensor(Sensor& sensor) -> UserApplicationConfigurer& {
  mSensors.push_back(&sensor);
  return *this;
}

template<typename EventVariantT>
template<typename T>
constexpr auto UserApplicationConfigurer<EventVariantT>::on(std::function<void(const T&)> action) -> UserApplicationConfigurer& {
  auto index = EventIndex_v<T, EventVariantT>;
  mEventMap[index].push_back([action = std::move(action)](auto& e) {
    action(std::get<T>(e));
  });
  return *this;
}

}

#endif //RGBLIB_VEHICLEAPPLICATIONBUILDER_H
