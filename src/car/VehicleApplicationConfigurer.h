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

template<typename ...UserEvents>
struct VehicleApplicationConfigurer {
  constexpr auto addLEDs(LEDCircuit& circuit) -> VehicleApplicationConfigurer&;
  constexpr auto addSensor(Sensor& sensor) -> VehicleApplicationConfigurer&;

  constexpr auto useHeartbeatLED() -> VehicleApplicationConfigurer&;

  template<typename T>
  constexpr auto on(std::function<void(const T&)> action) -> VehicleApplicationConfigurer&;

  std::vector<LEDCircuit*> mLeds{};
  std::vector<Sensor*> mSensors{};
  std::unordered_map<uint, std::vector<std::function<void(const Event<UserEvents...>&)>>> mEventMap{};
  bool mHeartbeat{};
};

template<typename... UserEvents>
constexpr auto VehicleApplicationConfigurer<UserEvents...>::useHeartbeatLED() -> VehicleApplicationConfigurer& {
  mHeartbeat = true;
  return *this;
}

template<typename ...UserEvents>
constexpr auto VehicleApplicationConfigurer<UserEvents...>::addLEDs(rgb::LEDCircuit& circuit) -> VehicleApplicationConfigurer<UserEvents...>& {
  mLeds.push_back(&circuit);
  return *this;
}

template<typename ...UserEvents>
constexpr auto VehicleApplicationConfigurer<UserEvents...>::addSensor(Sensor& sensor) -> VehicleApplicationConfigurer<UserEvents...>& {
  mSensors.push_back(&sensor);
  return *this;
}

template<typename ...UserEvents>
template<typename T>
constexpr auto VehicleApplicationConfigurer<UserEvents...>::on(std::function<void(const T&)> action) -> VehicleApplicationConfigurer<UserEvents...>& {
  auto index = EventIndex_v<T, Event<UserEvents...>>;
  mEventMap[index].push_back([action = std::move(action)](auto& e) {
    action(std::get<T>(e));
  });
  return *this;
}

}

#endif //RGBLIB_VEHICLEAPPLICATIONBUILDER_H
